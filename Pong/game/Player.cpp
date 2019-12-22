//
// Created by nicolasipr on 15/10/2019.
//

#include "includes/Player.h"
#include <iostream>
//socket
#include <bits/stdc++.h>
#include <arpa/inet.h>
// #include <sys/socket.h>
#include <netinet/in.h> // socket struct
#include <chrono>
#include <unistd.h>
#include <netdb.h>

#define BUFFER_SIZE 1024


using namespace std;

Player::Player() {
    connection();
}
Player::~Player() {
//    cout << "Player " << playerSide << " Has ben  destroyed!";
//    closeConnection();
}
int Player::getPaddleYPos() {
    return paddleYPos;
}
int Player::getPaddleXPos() {
    return paddleXPos;
}
int Player::getPlayerSide(){
    return playerSide;
}
char * Player::getPaddle() {
    return paddle;
}

/*
 *  Utilities
 * createMessage() ->
 * connection() ->
 *
 */
char* Player::createMessage( char * mes_buff) {


    mes_buff[0] = getPlayerSide() + '0';
    mes_buff[1] = '+';
    mes_buff[2] = controlInput();

    for(long unsigned int  i = 3 ; i < 64; i++)
        mes_buff[i] = getRandomChar();

    mes_buff[64] = '\0';

    return encryption(mes_buff, key);
}

void Player::recvHandler(char * msg) {


    cout << "\nHandling msg Decrypt : " << msg;
    /*
     *  recv msg format
     *  While Connection Request > "token, side, Game Speed"
     *  While Playing > "Player1: Player 1 Y pos,  Player 2: Player 2 Y Pos"
     *
     */
    // Connection request Handler
    if(msg != NULL){
        decrypt(msg, key);
        if( msg[0] == '?') {

            setPlayers(); // updates total of players
            playerSide = msg[1] - '0'; // gives player k its number side

        }
        // Playing data Handler
        if( msg[0] == getPlayerSide() - '0') {

        }
    }
    else
        return ;



}
void Player::connection(){

    hostent * record = gethostbyname(getAddress());

    if(record == NULL){
        cout <<"\n" <<  getAddress() <<" is unavailable";
        exit(1);
    }

    in_addr * addressHost = (in_addr * )record->h_addr;
    char* ip_address = inet_ntoa(* addressHost);

    int port = getPort();

    char    rcv_buf[BUFFER_SIZE], // buffer to receive;
            msg_buff[65]; // buffer message to send;

    cout << "\nServer Name Address: " << getAddress() << endl
         << "IPv4 Address: " << ip_address << endl
         << "Port: " << port << endl;

    struct sockaddr_in server; //IPV4


    // udp connection

    //  Socket

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // 0 means default, AF_NET = IPV4 & SOCK_DGRAM = TCP


    if(sock < 0){
        cout << "Error while opening socket";
        exit(1);
    }
    // connection

    memset(&server, 0, sizeof (server));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, ip_address, &server.sin_addr);

    unsigned int len;

    // Joining game
    cout << "Joining Game ...";
    char join[BUFFER_SIZE],
         join_request[10] = {'?','R','e','q','u','e','s','t','\0'};
    encryption(join_request, key);

    sendto(sock, (const char *) join_request, strlen(join_request) ,
           MSG_CONFIRM, (const struct sockaddr *) &server,
           sizeof(server));

    unsigned int join_size;

    recvfrom(sock, (char *) join, BUFFER_SIZE,
             MSG_WAITALL, (struct sockaddr *) &server,
             &join_size);

    join[join_size] = '\0';

    if (join != NULL){
        setServerStatus(true);
    }
    recvHandler(join);
    cout << "\n\nJOIN :" << join ;
    auto start = chrono::steady_clock::now();
    auto max_time = 5;

    while( 1){

        auto current = chrono::steady_clock::now();
        system("clear");
        cout << "\nWaiting for other players..." << endl;

        recvfrom(sock, (char *) join, BUFFER_SIZE,
                 MSG_DONTWAIT, (struct sockaddr *) &server,
                 &len);

        cout << "\n Elapsed time: " << chrono::duration_cast<chrono::seconds>(current - start).count() << " [s]" << endl;


        if ( chrono::duration_cast<chrono::seconds>(current - start).count() >= max_time ){
            cout << "You've won!" << endl
                 << "Sadly, because nobody wants to play with you :(" << endl;
            break;
        }
            recvHandler(join);

        while( getPlayers() >=2 ){
            cout << "\nEntering the Game..." << endl;
            createMessage(msg_buff);
            cout << "Client " << getPlayerSide() << " : " << decrypt(msg_buff,key); encryption(msg_buff, key);


            sendto(sock, (const char *) msg_buff, strlen(msg_buff) ,
                   MSG_CONFIRM, (const struct sockaddr *) &server,
                   sizeof(server));

            recvfrom(sock, (char *) rcv_buf, BUFFER_SIZE,
                     MSG_WAITALL, (struct sockaddr *) &server,
                     &len);

            // Handling rcv_buff
            rcv_buf[len] = '\0';
            printf("\nServer: %s\n", decrypt(rcv_buf, key));

        }

    }



    close(sock);
}
