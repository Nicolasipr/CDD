//
// Created by nicolasipr on 15/10/2019.
//

#include "includes/Player.h"
#include <iostream>
//#include <stdio.h>
#include <cstdio>
#include <fcntl.h>
//#include<stdlib.h>
#include <cstdlib>
//#include <ctype.h>
#include <cctype>
//socket
#include <bits/stdc++.h>
#include <arpa/inet.h>
// #include <sys/socket.h>
#include <netinet/in.h> // socket struct
#include <chrono>
#include <unistd.h>
#include <netdb.h>

static pthread_mutex_t player_mutex; // avoids threads interruption.


#define BUFFER_SIZE 512


using namespace std;

Player::Player() {
//    connection();
}
Player::~Player() {
    closeConnection();
}

int Player::getPlayerSide() {
    return playerSide;
}

/*
 * THREADS
 */
void *Player::listenServerHelper(void *p) {
    Player *a = (Player *)p; // cast p to Player type

    char buffer[BUFFER_SIZE];
//    cout << "\nHello from listen to Server Handler" ;
    while(1){
        pthread_mutex_lock(&player_mutex); //  keeps rcv Message under control
//        a->sendToServer();
        a->listenServer(buffer);
        p=a;
        pthread_mutex_unlock(&player_mutex);
    }

    return NULL;
}
void Player::listenServer(char *buff) {

    unsigned int len = sizeof(server);

    if (recvfrom(socket_fd, (char *)buff, BUFFER_SIZE,
                 MSG_WAITALL, ( struct sockaddr *) &server,
             &len) < 0 ){
        perror("recvfrom");
//        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    else{
        buff[len] = '\0';
        recvHandler(buff);

    }


}
void *Player::sendToServerHelper(void *p){
    Player *a = (Player *)p; // cast p to Player type


    while(1){
//        pthread_mutex_lock(&player_mutex); //  keeps rcv Message under control
        a->sendToServer();
//        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // sends 10 updates/seconds
        p=a;
//        pthread_mutex_unlock(&player_mutex);
    }

    return NULL;
}
void Player::sendToServer(){

    char resp[65];
    createMessage(resp);

    if(sendto(socket_fd, (const char *) resp, strlen(resp) ,
           0, (const struct sockaddr *) &server,
           sizeof(server)) < 0){
        perror("sendto");
//        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    else{
        std::this_thread::sleep_for(std::chrono::milliseconds(166)); // 6pps

    }


}



/*
 *  Utilities
 * createMessage() ->
 * connection() ->
 *
 */
//char* Player::createMessage( char * mes_buff) {
//
//    mes_buff[0] = getPlayerSide() + '0';
//    mes_buff[1] = '+';
//    mes_buff[2] = controlInput();
//
//    for(long unsigned int  i = 3 ; i < 64; i++)
//        mes_buff[i] = getRandomChar();
//
//    mes_buff[64] = '\0';
//
//    return encryption(mes_buff, key);
//}

char* Player::createMessage( char * mes_buff) {

    mes_buff[0] = getPlayerSide() + '0';
    mes_buff[1] = '+';
    cin.sync();
    if(!kbhit()){ // if key is not pressed, sends actual postion of player K
        mes_buff[2] = '.';
        mes_buff[3] = '+';
        if(getPlayerSide() == 1){
            if( getPlayerOneYPos() >= 10) {
                mes_buff[4] = getPlayerOneYPos()/10 + '0';
                mes_buff[5] = getPlayerOneYPos()%10 + '0';
                mes_buff[6] = '\0';
            }
            else{
                mes_buff[4] = getPlayerOneYPos() + '0';
                mes_buff[5] = '+';
                mes_buff[6] = '\0';
            }
        }
        if(getPlayerSide() == 2){
            if( getPlayerTwoYPos() >= 10) {
                mes_buff[4] = getPlayerTwoYPos()/10 + '0';
                mes_buff[5] = getPlayerTwoYPos()%10 + '0';
                mes_buff[6] = '\0';
            }
            else{
                mes_buff[4] = getPlayerTwoYPos() + '0';
                mes_buff[5] = '+';
                mes_buff[6] = '\0';
            }
        }

    }
    else{ // if key is pressed, request current updates current player info
        mes_buff[2] = getchar();
        if(getPlayerSide() == 1){
            if( tolower(mes_buff[2])  == 'w'  )
                setPlayerOnePos(getPlayerOneYPos()+1);
            if( tolower(mes_buff[2])  == 's'  )
                setPlayerOnePos(getPlayerOneYPos()-1);
        }
        if(getPlayerSide() == 2){
            if( tolower(mes_buff[2])  == 'i'  )
                setPlayerTwoPos(getPlayerTwoYPos()+1);
            if( tolower(mes_buff[2])  == 'k'  )
                setPlayerTwoPos(getPlayerTwoYPos()-1);
        }
    }


    fflush(NULL);
    fflush(stdin);
    fflush(stdout);
    for(long unsigned int  i = 7 ; i < 32; i++)
        mes_buff[i] = getRandomChar();

    mes_buff[32] = '\0';
    return encryption(mes_buff, key);
}


void Player::recvHandler(char * msg) {

//    system("clear");
//    fflush(stdin);

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
        if( msg[0] == ']'){
            setServerStatus(true);
        }
        // Playing data Handler
        if( msg[0] == '!'){

            int i = 1,
                temp = 0,
                cont = 1;
            char * aux = msg;
            while( aux[i] != '\0'){
                if(aux[i] == '+'){
                    if (cont == 1){
                        setPlayerOnePos(temp);
                        temp = 0;
                    }
                    if(cont == 2){
                        setPlayerTwoPos(temp);
                        temp = 0;
                    }
                    if(cont == 3){
                        setBallXPos(temp);
                        temp=0;
                    }
                    if(cont == 4){
                        setBallYPos(temp);
                        temp=0;
                    }
                    if(cont == 5){
                        setPlayerOneScore(temp);
                        temp=0;
                    }
                    if(cont == 6){
                        setPlayerTwoScore(temp);
                        temp=0;
                    }

                    cont++;
                    i++;
                    continue;

                }

                if (aux[i] != '+' && temp < 100) {
                    if( aux[i] - '0' >= 0 && aux[i] - '0' <= 9 ){
                        temp *= 10;
                        temp += aux[i] - '0';
                    }

                }

                i++;
            }

        }

    }
    else{
        encryption(msg, key);
        return;
    }

}
void Player::sendMessage() {

    char rcv_buf[BUFFER_SIZE], // buffer to receive;
         msg_buff[33]; // buffer message to send;

    createMessage(msg_buff);
//    if (  strcmp(createMessage(msg_buff), "false") == 0   ) {
        sendto(socket_fd, (const char *) msg_buff, strlen(msg_buff) ,
               0, (const struct sockaddr *) &server,
               sizeof(server));
//    }


    unsigned int len;
    fflush(stdin);
    if ( recvfrom(socket_fd, (char *) rcv_buf, BUFFER_SIZE,
                  MSG_DONTWAIT, (struct sockaddr *) &server,
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
             0, (struct sockaddr *) &server,
             &join_size);

    fflush(stdin);
    join[join_size] = '\0';

//    if (join != NULL){
//        setServerStatus(true);
//    }
    recvHandler(join);
}
void Player::closeConnection() {
    close(socket_fd);
}

void Player::connectionTCP() {

    int valread;

    // Figures out if connection is valid or not
    hostent * record = gethostbyname(getAddress());

    if(record == NULL){
        cout <<"\n" <<  getAddress() <<" is unavailable";
        exit(1);
    }

    in_addr * addressHost = (in_addr * )record->h_addr;
    char* ip_address = inet_ntoa(* addressHost);
    const char *hello = "Hello from client";

    char buffer[BUFFER_SIZE] = {0};

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( socket_fd < 0){
        printf("\n Socket creation error \n");
        return ;
    }
    memset(&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(getPort());
    memcpy(&server.sin_addr, record->h_addr_list[0], record->h_length);
//    server.sin_addr.s_addr = inet_addr(getAddress());


    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip_address, &server.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return ;
    }
    cout << "\nServer Name Address: " << getAddress() << endl
            << "IPv4 Address: " << ip_address << endl
         << "IPv4 Address: " << server.sin_addr.s_addr << endl
         << "Port: " << server.sin_port << endl;

    if (connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0){
        perror("connect");
        printf("\nConnection Failed \n");
        return ;
    }
    while(1){
        send(socket_fd , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
        valread = read( socket_fd , buffer, BUFFER_SIZE);
        printf("%s\n",buffer );
    }

    return ;
}
void Player::connectionUDP(){

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
