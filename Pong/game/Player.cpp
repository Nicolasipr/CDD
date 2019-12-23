//
// Created by nicolasipr on 15/10/2019.
//

#include "includes/Player.h"
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
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
    closeConnection();
}

int Player::getPlayerSide() {
    return playerSide;
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

    system("clear");
    fflush(stdin);

    encryption(msg, key);

    /*
     *  recv msg format
     *  While Connection Request > "token, side, Game Speed"
     *  While Playing > "Player1: Player 1 Y pos,  Player 2: Player 2 Y Pos"
     *
     */
    // Connection request Handler
    fflush(stdin);

    if(msg != NULL){

        if( msg[0] == '?') {

            setPlayers(); // updates total of players
            playerSide = msg[1] - '0'; // gives player k its number side

        }
        // Playing data Handler
        if( msg[0] == '!'){

            int i = 1,
                temp = 0;
            char * aux = msg;
            while( aux[i] != '\0'){
                if (aux[i] != '+' && temp < 100) {
                    if( aux[i] - '0' >= 0 && aux[i] - '0' <= 9 ){
                        temp *= 10;
                        temp += aux[i] - '0';
                    }

                }
                else{
                    setPlayerOnePos(temp);
                    temp = 0;

                }
                i++;
            }
            setPlayerTwoPos(temp);
        }

    }
    else{
        encryption(msg, key);
        return;
    }

}
void Player::sendMessage() {

    char rcv_buf[BUFFER_SIZE], // buffer to receive;
         msg_buff[65]; // buffer message to send;

    createMessage(msg_buff);


    sendto(socket_fd, (const char *) msg_buff, strlen(msg_buff) ,
                   MSG_CONFIRM, (const struct sockaddr *) &server,
                   sizeof(server));

    unsigned int len;
    fflush(stdin);
    if ( recvfrom(socket_fd, (char *) rcv_buf, BUFFER_SIZE,
                     0, (struct sockaddr *) &server,
                     &len) < 0 ) {
        len = 1;
    }

    rcv_buf[len] = '\0';

    recvHandler(rcv_buf);

}

void Player::joinGame() {

    cout << "Joining Game ...";

    char join[BUFFER_SIZE],
            join_request[10] = {'?','R','e','q','u','e','s','t','\0'};

    encryption(join_request, key);

    sendto(socket_fd, (const char *) join_request, strlen(join_request) ,
           0 , (const struct sockaddr *) &server,
           sizeof(server));

    unsigned int join_size;

    recvfrom(socket_fd, (char *) join, BUFFER_SIZE,
             MSG_DONTWAIT, (struct sockaddr *) &server,
             &join_size);

    fflush(stdin);
    join[join_size] = '\0';

    if (join != NULL){
        setServerStatus(true);
    }
    recvHandler(join);
}
void Player::closeConnection() {
    close(socket_fd);
}


void Player::connection(){

    // Figures out if connection is valid or not
    hostent * record = gethostbyname(getAddress());

    if(record == NULL){
        cout <<"\n" <<  getAddress() <<" is unavailable";
        exit(1);
    }

    in_addr * addressHost = (in_addr * )record->h_addr;
    char* ip_address = inet_ntoa(* addressHost);

    int port = getPort();

    cout << "\nServer Name Address: " << getAddress() << endl
         << "IPv4 Address: " << ip_address << endl
         << "Port: " << port << endl;

    // sets up UDP connection

    //  Socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0); // 0 means default, AF_NET = IPV4 & SOCK_STREAM = TCP

    if(socket_fd < 0){
        cout << "Error while opening socket";
        exit(1);
    }
    // Free and sets server address  information
    memset(&server, '\0', sizeof (server));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    inet_pton(AF_INET, ip_address, &server.sin_addr);

}
