//
// Created by nicolasipr on 03/11/2019.
//

#include "includes/Game.h"

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <termios.h>

#include <random>
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
#define MAX_CLIENTS 2


using namespace std;

Game::Game() {

    cout << "\n\n\n\t\tLoading...";
    system("clear");
}

Game::~Game() {
    cout << "Thanks for playing!";
}
int Game::getFPS() {
    return FPS;
}

bool Game::getServerStatus() {
    return serverStatus;
}

void Game::setServerStatus( bool n_status) {
    serverStatus = n_status;
}

/*
 *  Players
 */
int Game::getPlayers() {
    return players_count;
}

void Game::setPlayers() {
    players_count++;
}
int Game::getPlayerOneYPos() {
    return playerOnePos;
}
int Game::getPlayerTwoYPos() {
    return playerTwoPos;
}
int Game::getPlayerOneScore() {
    return playerOneScore;
}
int Game::getPlayerTwoScore(){
    return playerTwoScore;
}


void Game::setPlayerOneScore(int n_score) {
    playerOneScore = n_score;
}
void Game::setPlayerTwoScore(int n_score){
    playerTwoScore = n_score;
}


/*
 *  TOOLS
 *  control Input -> It handles unbuffered pressed keyboard from terminal.
 *  encryption  -> Basic message encryption. Avoids easy cheating on game
 *  decryption  -> Basic decrypts message given
 */
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

char * Game::encryption(char* msg,  char* key) {

    if (!strlen(key))
        return msg;

    for(long unsigned int i = 0; i < strlen(msg); i++){
        msg[i] ^= key[i % strlen(key)]; // bitwise XOR operation
    }
    return msg;
}
char * Game::decrypt(char *msg, char* key) {
    return encryption(msg, key); // reversed process
}
char Game::getRandomChar(){

    std::default_random_engine generator(1234);
    std::uniform_int_distribution<int> distribution(31,120);

    srand(time(NULL));
    char c = static_cast<unsigned char>( distribution(generator) );
    return c;
}
char* Game::handlingMessage(char * msg, char * resp) {
    cout << "\nmsg 1 :" << msg;
        cout << "\nRESP 1 :" << resp;

    if( msg[0] == '?' || msg[1] == '?') {
        setPlayers(); // updates total of players
        resp[0] = '?';
        resp[1] = getPlayers() + '0';
        resp[2] = '+';
        resp[3] = gameMode + '0';
        resp[4] = '\0';
        cout << "\nRESP 1.1 :" << resp;
        return encryption(resp, key);
    }
    else if (msg[0] == '1' || msg[0] == '2'){
        if(msg[0] == '1'){
            if(p1UpKey == msg[2] ) {
                if(playerOnePos >= scoreBoard + 2)
                    playerOnePos--;
            }
            if(p2DownKey == msg[2])
                if(playerOnePos <= height + scoreBoard - 7)
                    playerOnePos++;
        }
        else {
            if(p2UpKey == msg[2] ) {
                if(playerTwoPos >= scoreBoard + 2)
                    playerTwoPos--;
            }
            if(p2DownKey == msg[2])
                if(playerTwoPos <= height + scoreBoard - 7)
                    playerTwoPos++;
        }
        resp[0] = '+';
        if(playerOnePos >= 10){
            resp[1] = playerOnePos/10 + '0';
            resp[2] = playerOnePos%10 + '0';
            resp[3] = '+';
            if(playerTwoPos >= 10){
                resp[4] = playerOnePos/10 + '0';
                resp[5] = playerOnePos%10 + '0';
            }
            else
                resp[4] = playerTwoPos + '0';
        }
        else
            resp[1] = playerOnePos + '0';
        cout << "resp : " << resp;
    }
    else
        return encryption(msg, key);
    cout << "\nRESP 2 :" << resp;
    return encryption(resp, key);

}
/*
 *
 */
int Game::getPort(){
    return  serverPort;
}
char * Game::getAddress() {
    return (char *) serverAddress;
}
void Game::setServer() {
        int sockfd;

        struct sockaddr_in servaddr, cliaddr;
//                *cliaddr[MAX_CLIENTS];

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

//        for(int i = 0; i < MAX_CLIENTS; i++){
//            cliaddr[i] = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
//            memset(&cliaddr[i], 0, sizeof(cliaddr[i]));
//        }


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

        len = sizeof(cliaddr); //len is value/resuslt
        serverStatus = true;

        system("clear");
        char buffer[BUFFER_SIZE],
            resp[BUFFER_SIZE];

        cout << "Server is running on: "
              << "\n\tAddress : " << getAddress()
              << "\n\t\t: " << ip_address
              << "\n\tPort    : " << getPort()
              << "\n\tSpeed   :" << getFPS()
              << "\nLogs here: \n\n";



        while(1){

            recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                     MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                     &len);

            buffer[len] = '\0';

//
            printf("Client : %s\n", buffer);
            printf("Client decrypted : %s\n", decrypt(buffer, key) );
            cout << "\nHandled message :" << handlingMessage(buffer, resp);
            printf("\nServer : %s\n", resp);
            printf("\nServer decrypted : %s\n", decrypt(resp, key) );
                encryption(resp, key);

            sendto(sockfd, (const char *)resp, strlen(resp),
                   MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                   len);

        }
//            for (int i = 0; i < MAX_CLIENTS; ++i) {
//                len = sizeof(cliaddr[i]); //len is value/resuslt
//                recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
//                         MSG_WAITALL, ( struct sockaddr *) cliaddr[i],
//                         &len);
//                buffer[len] = '\0';
//                printf("Client : %s\n", buffer);
//                printf("Client decrypted : %s\n", decrypt(buffer, key) );
//                printf("Client : %s\n", buffer);
//
//
//                printf("Server : %s\n", encryption(resp, key));
//                printf("Server decrypted : %s\n", decrypt(resp, key) );
//                encryption(resp, key);
//                for (int j = 0; j < MAX_CLIENTS;  ++j) {
//                    len = sizeof(cliaddr[j]);
//                    cout << "hola\n";
//                    sendto(sockfd, (const char *)resp, strlen(resp),
//                           MSG_CONFIRM, (const struct sockaddr *) cliaddr[j],
//                           len);
//                }

//            }
//
//
//
//        }



}