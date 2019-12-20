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
#include <unistd.h>
#include <netdb.h>

#define BUFFER_SIZE 1024


using namespace std;

Player::Player(int newSide) {
    playerSide = newSide;
    connection();
}
Player::~Player() {
    cout << "Player " << playerSide << " Has ben  destroyed!";
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

void Player::sendPosY(){


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
    char c = controlInput();
    const char * message = reinterpret_cast<const char(*)>(&c);

    cout << "\nServer Name Address: " << getAddress() << endl
         << "IPv4 Address: " << ip_address << endl
         << "Port: " << port << endl
         << "Message: " << message << endl;


    struct sockaddr_in server; //IPV4
    char buf[BUFFER_SIZE];

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


    sendto(sock, message, strlen(message) ,
           MSG_CONFIRM, (const struct sockaddr *) &server,
           sizeof(server));
    cout << "message sent" << endl;

    recvfrom(sock, (char *) buf, BUFFER_SIZE,
                 MSG_WAITALL, (struct sockaddr *) &server,
                 &len);

    buf[len] = '\0';

    printf("Server: %s\n", buf);

    close(sock);
}
