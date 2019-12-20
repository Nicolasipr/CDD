//
// Created by nicolasipr on 03/11/2019.
//

#include "includes/Game.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

// Server side implementation of UDP client-server model
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT	 7777
#define BUFFER_SIZE 1024


using namespace std;

Game::Game() {

    cout << "\n\n\n\t\tLoading...";
    system("clear");
}

Game::~Game() {
    cout << "Thanks for playing!";
}

char Game::controlInput() {
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    c=getchar();
    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

    return c;
}
int Game::getPort(){
    return  serverPort;
}
char * Game::getAddress() {
    return (char *) serverAddress;
}
void Game::setServer() {
        int sockfd;
        char buffer[BUFFER_SIZE];
        struct sockaddr_in servaddr, cliaddr;

        // checks address ip
        hostent * record = gethostbyname(getAddress());
        if(record == NULL){
            cout <<"\n" << getAddress() <<" is unavailable";
            exit(1);
        }
        in_addr * addressHost = (in_addr * )record->h_addr;
        char* ip_address = inet_ntoa(* addressHost);

    // Creating socket file descriptor
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORT);

        // Bind the socket with the server address
        if ( bind(sockfd, (const struct sockaddr *)&servaddr,
                  sizeof(servaddr)) < 0 )
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        unsigned int len;
        int  n;

        len = sizeof(cliaddr); //len is value/resuslt
        serverStatus = true;
        system("clear");

        cout << "Server is running on: "
              << "\n\tAddress : " << getAddress()
              << "\n\t\t: " << ip_address
              << "\n\tPort: " << getPort()
              << "\nLogs here: \n\n";

        while(1){
            n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                         MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                         &len);

            buffer[n] = '\0';

            printf("Client : %s\n", buffer);
            sendto(sockfd, (const char *)buffer, strlen(buffer),
                   MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                   len);

        }



}