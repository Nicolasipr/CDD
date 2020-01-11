//
// Created by nicolasipr on 03/11/2019.
//

#include "includes/Game.h"

#include <iostream>
#include <chrono>
#include <thread>
#include "pthread.h"

//kbhit
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <random>
// Server side implementation of UDP client-server model
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT	 7777
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 2
#define esc 27

//static pthread_mutex_t mutex; // avoids threads interruption.

using namespace std;

Game::Game() {

//    cout << "\n\n\n\t\tLoading...";
    system("clear");
}

Game::~Game() {
    system("clear");
    cout << "\nnThanks for playing!";
}
int Game::getFPS() {
    return FPS;
}
void Game::setFPS(int n_fps) {
    FPS = n_fps;
}

bool Game::getServerStatus() {
    return serverStatus;
}

void Game::setServerStatus( bool n_status) {
    serverStatus = n_status;
}
int Game::getPort(){
    return  serverPort;
}
void Game::setPort(int n_port) {
    serverPort = n_port;
}

char * Game::getAddress() {
    return (char *) serverAddress;
}
void Game::setAddress(char *n_address) {
    strcpy(serverAddress, n_address);
//    serverAddress = n_address;
}

/*
 *  PLAYERS
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
void Game::setPlayerOnePos(int n_pos) {
    playerOnePos = n_pos;
}

void Game::setPlayerTwoPos(int n_pos) {
    playerTwoPos = n_pos;
}

void Game::setPlayerOneScore(int n_score) {
    playerOneScore = n_score;
}
void Game::setPlayerTwoScore(int n_score){
    playerTwoScore = n_score;
}
int Game::getPlayer1XPos() {
    return scoreBoard;
}
int Game::getPlayer2XPos() {
    return (width - 4 );
}
/*
 *  BALL
 */

int Game::getBallXPos(){
    return ballXPosition;
}
void Game::setBallXPos(int n_pos){
    ballXPosition = n_pos;
}

int Game::getBallYPos(){
    return ballYPosition;
}
void Game::setBallYPos(int n_pos){
    ballYPosition = n_pos;
}

int Game::getBallXDir(){
    return ballXDirection;
}
void Game::setBallXDir(int n_xDir){
    ballXDirection = n_xDir;
}

int Game::getBallYDir(){
    return ballYDirection;
}
void Game::setBallYDir(int n_yDir){
    ballYDirection = n_yDir;
}


/*
 *  TOOLS
 *  control Input -> It handles unbuffered pressed keyboard from terminal.
 *  encryption  -> Basic message encryption. Avoids easy cheating on game
 *  decryption  -> Basic decrypts message given
 */

//           P1 HANDLING MESSAGE
void *Game::rcvMessageHelper(void *p){
    Game *a = (Game *)p; // cast *p to Game Class type

    char buffer[BUFFER_SIZE],
            resp[128];

    while( a->getPlayerOneScore() < 3 && a->getPlayerTwoScore() < 3){

        a->rcvMessage(buffer, resp);
        a->sendMessageTo(a->p1Sock, a->p1Client, resp);
//        a->sendMessageTo(a->p2Sock, a->p2Client, resp);
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p=a;

    }
//    cout << "\nHello From Server Receiver Handler Ending ";

    return NULL;
}

char* Game::rcvMessage(char * buffer, char * resp) {
//    pthread_mutex_lock(&mutex); //  keeps rcv Message under control

    unsigned int len = sizeof(servaddr);

    if ( recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                  0, ( struct sockaddr *) &p1Client,
                  &len) < 0 ) {
        perror("recvfrom");
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else{
        buffer[len] = '\0';

        cout << "\n\n Message from Client Address: " << inet_ntoa(p1Client.sin_addr);
        cout << "\nand sent from port: " << ntohs(p1Client.sin_port);
        printf("\nClient : %s", buffer);
        printf("\nClient decrypted : %s\n", decrypt(buffer, key) );
        fflush(stdin);
        cout << "Handled message :" << handlingMessage(buffer, resp);
        cout << "\n Server :" << resp;
        fflush(stdin);
        cout << "\nServer decrypted :  " << decrypt(resp, key) << endl;
        std::cout.flush();
    }

//    pthread_mutex_unlock(&mutex);
    return encryption(resp, key);
}


//      P2 HANDLING MESSAGE
char* Game::rcvMessageP2(char * buffer, char * resp) {
//    pthread_mutex_lock(&mutex); //  keeps rcv Message under control

    unsigned int len = sizeof(servaddr);

    if ( recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                  0, ( struct sockaddr *) &p2Client,
             &len) < 0 ) {
        perror("recvfrom");
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    else{
        buffer[len] = '\0';

        cout << "\n\n Message from Client Address: " << inet_ntoa(p2Client.sin_addr);
        cout << "\nand sent from port: " << ntohs(p2Client.sin_port);
        printf("\nClient : %s", buffer);
        printf("\nClient decrypted : %s\n", decrypt(buffer, key) );
        fflush(stdin);
        cout << "Handled message :" << handlingMessage(buffer, resp);
        cout << "\n Server :" << resp;
        fflush(stdin);
        cout << "\nServer decrypted :  " << decrypt(resp, key) << endl;
        std::cout.flush();
    }

//    pthread_mutex_unlock(&mutex);
    return encryption(resp, key);
}
void *Game::rcvMessageHelperP2(void *p){
    Game *a = (Game *)p; // cast *p to Game Class type

    char buffer[BUFFER_SIZE],
            resp[128];

    while( a->getPlayerOneScore() < 3 && a->getPlayerTwoScore() < 3){

        a->rcvMessageP2(buffer, resp);
//        a->sendMessageTo(a->p1Sock, a->p1Client, resp);
        a->sendMessageTo(a->p2Sock, a->p2Client, resp);
//        std::this_thread::sleep_for(std::chrono::milliseconds(166));
        p=a;

    }
//    cout << "\nHello From Server Receiver Handler Ending ";

    return NULL;
}


void *Game::sendMessageHelper(void *p){

    Game *a = (Game *)p; // cast *p to Game Class type

    char buffer[BUFFER_SIZE],
            resp[128];

    while(a->getPlayerOneScore() < 3 && a->getPlayerTwoScore() < 3){

        a->handlingMessage(buffer, resp);
        a->sendMessageTo(a->p1Sock, a->p1Client, resp);
        p=a;
    }
    return NULL;
}
void Game::sendMessageTo(int id_socket, struct sockaddr_in client, char * resp) {

    if (  sendto(sockfd, (const char *)resp, strlen(resp),
                 MSG_DONTWAIT, (const struct sockaddr *) &client,
                    id_socket)< 0){
        perror("sendto");

    }
    else{
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 6 ppm
    }
}
int Game::kbhit(void){
    fflush(stdin);
    fflush(stdout);
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);;
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
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

char * Game::encryption(char* msg,  char* key) {

    if (!strlen(key))
        return msg;
    if (!strlen(msg))
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


void Game::setDifficulty(int n_difficulty) {
    switch(n_difficulty){
        case 1:
            setFPS(200); // easy
            break;
        case 2:
            setFPS(50); // Medium
            break;
        case 3:
            setFPS(20); // Hard
            break;
        case 4:
            setFPS(5); // Progressive(?
            break;
    }
}

char* Game::handlingMessage(char * msg, char * resp) {

    if( msg[0] == '?' || msg[1] == '?') {
        setPlayers(); // updates total of players
        resp[0] = '?';
        resp[1] = getPlayers() + '0';
        resp[2] = '+';
        resp[3] = gameMode + '0';
        resp[4] = '\0';
        if(getPlayers() == 1){
            memset(&p1Client, 0, sizeof(p1Client));
            p1Client.sin_family = cliaddr.sin_family;
            p1Client.sin_addr.s_addr = cliaddr.sin_addr.s_addr;
            p1Client.sin_port = cliaddr.sin_port;
            p1Sock = sizeof(p1Client);
        }
        if( getPlayers() == 2){
            memset(&p2Client, 0, sizeof(p2Client));
            p2Client.sin_family = cliaddr.sin_family;
            p2Client.sin_addr.s_addr = cliaddr.sin_addr.s_addr;
            p2Client.sin_port = cliaddr.sin_port;
            p2Sock = sizeof(p2Client);
        }

        return encryption(resp, key);
    }
    else if (msg[0] == '1' || msg[0] == '2'){
        if(msg[0] == '1'){
            if(p1UpKey == msg[2] ) {
                if(playerOnePos >= scoreBoard + 2)
                    playerOnePos--;
            }
            if(p1DownKey == msg[2])
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
    }
        resp[0] = '!';
        if(playerOnePos >= 10){
            resp[1] = getPlayerOneYPos()/10 + '0';
            resp[2] = getPlayerOneYPos()%10 + '0';
            resp[3] = '+';

            if(playerTwoPos >= 10){
                resp[4] =  getPlayerTwoYPos()/10 + '0';
                resp[5] =  getPlayerTwoYPos()%10 + '0';
                resp[6] = '+';

                if( ballXPosition >= 10){
                    resp[7] = getBallXPos()/10 + '0';
                    resp[8] = getBallXPos()%10 + '0';
                    resp[9] = '+';
                    if(ballYPosition >= 10) {
                        resp[10] = getBallYPos()/10 + '0';
                        resp[11] = getBallYPos()%10 + '0';
                        resp[12] = '+';
                        resp[13] = '\0';

                    }
                    else{
                        resp[10] = getBallYPos() + '0';
                        resp[11] = '+';
                        resp[12] = '\0';


                    }

                    return encryption(resp, key);
                }
                else{
                    resp[7] = getBallXPos() + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';


                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';
                    }

                    return encryption(resp, key);
                }
            }
            else{
                resp[4] =  getPlayerTwoYPos() + '0';
                resp[5] = '+';

                if( ballXPosition >= 10){
                    resp[6] = getBallXPos()/10 + '0';
                    resp[7] = getBallXPos()%10 + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';


                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';

                    }

                    return encryption(resp, key);
                }
                else{
                    resp[7] = getBallXPos() + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';
                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';
                    }

                    return encryption(resp, key);
                }
            }
        }
        else {
            resp[1] = getPlayerOneYPos() + '0';
            resp[2] = '+';
            if(playerTwoPos >= 10){
                resp[3] =  getPlayerTwoYPos()/10 + '0';
                resp[4] =  getPlayerTwoYPos()%10 + '0';
                resp[5] = '+';

                if( ballXPosition >= 10){
                    resp[6] = getBallXPos()/10 + '0';
                    resp[7] = getBallXPos()%10 + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';

                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';

                    }

                    return encryption(resp, key);
                }
                else{
                    resp[6] = getBallXPos() + '0';
                    resp[7] = '+';
                    if(ballYPosition >= 10) {
                        resp[8] = getBallYPos()/10 + '0';
                        resp[9] = getBallYPos()%10 + '0';
                        resp[10] = '+';
                        resp[11] = '\0';

                    }
                    else{
                        resp[8] = getBallYPos() + '0';
                        resp[9] = '+';
                        resp[10] = '\0';
                    }

                    return encryption(resp, key);
                }
            }
            else{
                resp[4] =  getPlayerTwoYPos() + '0';
                resp[5] = '+';

                if( ballXPosition >= 10){
                    resp[6] = getBallXPos()/10 + '0';
                    resp[7] = getBallXPos()%10 + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';

                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';

                    }

                    return encryption(resp, key);
                }
                else{
                    resp[7] = getBallXPos() + '0';
                    resp[8] = '+';
                    if(ballYPosition >= 10) {
                        resp[9] = getBallYPos()/10 + '0';
                        resp[10] = getBallYPos()%10 + '0';
                        resp[11] = '+';
                        resp[12] = '\0';

                    }
                    else{
                        resp[9] = getBallYPos() + '0';
                        resp[10] = '+';
                        resp[11] = '\0';
                    }

                    return encryption(resp, key);
                }
            }
        }
}
/*
 *
 */

void Game::setServerTCP() {


    int sockfd, ret;


    int newSocket;
    struct sockaddr_in cliaddr;


    char buffer[BUFFER_SIZE],
            resp[32];

    pid_t childpid;
    hostent * record = gethostbyname(getAddress());

    if(record == NULL){
        cout <<"\n" << getAddress() <<" is unavailable";
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Server Socket is created.\n");

    int option = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    memcpy(&servaddr.sin_addr, record->h_addr_list[0], record->h_length);
//    servaddr.sin_addr.s_addr = inet_addr(getAddress());

    ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0){
        printf("[-]Error in binding.\n");
        exit(1);
    }
    printf("[+]Bind to port %d\n", PORT);

    if(listen(sockfd, 10) == 0){
        printf("[+]Listening....\n");
    }else{
        printf("[-]Error in binding.\n");
    }

    socklen_t addr_size = sizeof(cliaddr);
    while(!getServerStatus()){
        while(getPlayers() < 2){
            newSocket = accept(sockfd, (struct sockaddr*)&cliaddr, &addr_size);
            if(newSocket < 0){
                exit(1);
            }
            else{
                setPlayers();
                if(getPlayers() == 1){
                    memset(&p1Client, 0, sizeof(p1Client));
                    p1Client.sin_family = cliaddr.sin_family;
                    p1Client.sin_addr.s_addr = cliaddr.sin_addr.s_addr;
                    p1Client.sin_port = cliaddr.sin_port;
                    p1Sock = newSocket;
                }
                if( getPlayers() == 2){
                    memset(&p2Client, 0, sizeof(p2Client));
                    p2Client.sin_family = cliaddr.sin_family;
                    p2Client.sin_addr.s_addr = cliaddr.sin_addr.s_addr;
                    p2Client.sin_port = cliaddr.sin_port;
                    p2Sock = newSocket;
                }

            }
        }


        printf("Connection accepted from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        if((childpid = fork()) == 0){
            close(sockfd);

            while(getPlayerOneScore() < 3 && getPlayerTwoScore() < 3){
                recv(newSocket, buffer, BUFFER_SIZE, 0);
                if(strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    break;
                }else{
                    cout << "\n\nMessage sent from socket: " << cliaddr.sin_port;
                    cout << "\n and from Client Address: " << cliaddr.sin_addr.s_addr;
                    cout << "\n through: " << cliaddr.sin_family;
                    printf("\nClient : %s", buffer);
                    printf("\nClient decrypted : %s", decrypt(buffer, key) );
                    fflush(stdin);
                    cout << "\nHandled message :" << handlingMessage(buffer, resp);
                    cout << "\nServer :" << resp;
                    fflush(stdin);
                    printf("\nServer decrypted : %s", decrypt(resp, key) );
                    encryption(resp, key);

                    send(p1Sock, resp, strlen(resp), 0);
                    send(p2Sock, resp, strlen(resp), 0);
                    bzero(buffer, sizeof(buffer));
                    bzero(resp, sizeof(resp));
                }
            }
        }

    }

    close(newSocket);
    return ;
}
void Game::setServerUDP() {


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
//            perror("socket creation failed");
            perror("sendto");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        // Filling server information
        servaddr.sin_family = AF_INET; // IPv4
        memcpy(&servaddr.sin_addr, record->h_addr_list[0], record->h_length);
//        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(PORT);

        // Bind the socket with the server address
        if ( bind(sockfd, (const struct sockaddr *)&servaddr,
                  sizeof(servaddr)) < 0  ){
//            perror("bind failed");
            perror("bind");
            exit(EXIT_FAILURE);
        }

        unsigned int len;
        len = sizeof(servaddr);


        system("clear");

        char buffer[BUFFER_SIZE],
            resp[32];
        int n;
        unsigned int  m = sizeof(n);
        getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(void *)&n, &m);
        cout << "\nSocket size = " << n << endl;

    cout << "Server is running on: "
         << "\n\tAddress : " << getAddress()
         << "\n\t\t: " << ip_address
         << "\n\t\t: " << inet_ntoa(servaddr.sin_addr)
         << "\n\tPort    : " << getPort()
         << "\n\tPort    : " << ntohs(servaddr.sin_port)
         << "\n\tSpeed   : " << getFPS()
         << "\nLogs here: \n\n";

    int lennn, trysize, gotsize, err;
    lennn = sizeof(int);
    trysize = 1048576+32768;
    do {
        trysize -= 32768;
        setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(char*)&trysize,lennn);
        err = getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(char*)&gotsize,(socklen_t*)&lennn);
        if (err < 0) { perror("getsockopt"); break; }
    } while (gotsize < trysize);
    printf("Size set to %d\n",gotsize);

    trysize = 1048576+32768;
    gotsize = 0;
    do {
        trysize -= 32768;
        setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(char*)&trysize,lennn);
        err = getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(char*)&gotsize,(socklen_t*)&lennn);
        if (err < 0) { perror("getsockopt"); break; }
    } while (gotsize < trysize);
    printf("Size set to %d\n",gotsize);

        while(getPlayers() < 2){
            cout << "\n\n Waiting for Players, Total in server: " << getPlayers();

            if( (recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                    0, ( struct sockaddr *) &cliaddr,
                    &len) ) < 0 ){
                perror("recvfrom");
            }

            buffer[len] = '\0';
            cout << "\n\nMessage sent from socket: " << ntohs(cliaddr.sin_port);
            cout << "\n and from Client Address: " << inet_ntoa(cliaddr.sin_addr);
            printf("\nClient : %s", buffer);
            printf("\nClient decrypted : %s\n", decrypt(buffer, key) );
            fflush(stdin);
            cout << "Handled message :" << handlingMessage(buffer, resp);
            cout << "\nServer :" << resp;
            fflush(stdin);
            printf("\nServer : %s", resp);
            fflush(stdin);
            printf("\nServer decrypted : %s", decrypt(resp, key) );
            encryption(resp, key);

            fflush(stdin);
            if( (sendto(sockfd, (const char *)resp, strlen(resp),
                   0, (const struct sockaddr *) &cliaddr,
                   len) ) < 0 ){
                perror("sendto");
            }
        }

        if(getPlayers() == 2){
            char ready[16] = {']', 's','t','a','r','t', '\0'};
            encryption(ready, key);
            cout << "\n\nServer :" << ready;
            fflush(stdin);
            printf("\nServer : %s", ready);
            fflush(stdin);
            printf("\nServer decrypted : %s", decrypt(ready, key) );
            encryption(ready, key);

            sendto(sockfd, (const char *)ready, strlen(ready),
                   0, (const struct sockaddr *) &p1Client,
                   p1Sock);
            sendto(sockfd, (const char *)ready, strlen(ready),
                   0, (const struct sockaddr *) &p2Client,
                   p2Sock);
        }





//    while(1){
//            fflush(NULL);
//            fflush(stdin);
//            fflush(stdout);
////            std::thread receiving (rcvMessage, buffer, len);
////            receiving.join();
////            rcvMessage(buffer, len);
//
////            recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
////                     MSG_DONTWAIT, ( struct sockaddr *) &cliaddr,
////                     &len);
//
//            buffer[len] = '\0';
//
//            cout << "\n\n Message from Client Address: " << inet_ntoa(cliaddr.sin_addr);
//            cout << "\nand sent from port: " << ntohs(cliaddr.sin_port);
//            printf("\nClient : %s", buffer);
//            printf("\nClient decrypted : %s\n", decrypt(buffer, key) );
//            fflush(stdin);
//            cout << "Handled message :" << handlingMessage(buffer, resp);
//            cout << "\n Server :" << resp;
//            fflush(stdin);
//            printf("\nServer decrypted : %s", decrypt(resp, key) );
//                encryption(resp, key);
//
//            fflush(NULL);
//            fflush(stdin);
//            fflush(stdout);
////            std::this_thread::sleep_for(std::chrono::milliseconds(200));
////            std::thread th1 (sendMessageTo, p1Sock, &p1Client, resp);
////            th1.join();
//
//            sendto(sockfd, (const char *)resp, strlen(resp),
//                   0, (const struct sockaddr *) &p1Client,
//                   p1Sock);
//            fflush(NULL);
//            fflush(stdin);
//            fflush(stdout);
//            sendto(sockfd, (const char *)resp, strlen(resp),
//               0, (const struct sockaddr *) &p2Client,
//               p2Sock);
////            sendMessageTo(p2Sock, &p2Client, resp);
////            std::thread th2 (sendMessageTo, p2Sock, &p2Client, resp);
////            th2.join();
//        }

}