//
// Created by nicolasipr on 15/10/2019.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


//#include "Board.h"
//class Board;
//class Game;
#include "Game.h"
#include <netinet/in.h> // socket struct

//#include "Board.h"

class Player : public virtual Game { //hybrid

private:
    char name[32] = "192.168.0.1";
    int playerScore = 0;
    int playerSide = getPlayers(); // 1 or 2

    char key[31] = "@PoNg_CdD_iN_C++_HaVe_FuN!@";
    int socket_fd;
    struct sockaddr_in server;

public:
    Player();
    ~Player();

    /*
     * Player connection Handles
     */
    void joinGame(); // Players request to enter the game to default side.
    void connectionUDP(); // Stablish Connection with Server and it stays connetected while client is running
    void connectionTCP();
    void closeConnection(); // closes socket
    void recvHandler(char *); // It Handles data received from Server

    char* createMessage(char * msg); // Creates a message to send whenever a key is pressed to update players condition.
    void sendMessage();

    /*
     * Players Pladdle and Position
     */
    int getPaddleXPos();
    int getPlayerSide();
    char * getPaddle();
    void sendPosY();

    /*
     * PLAYER THREADS HANDLERS
     */
    static void *listenServerHelper(void *);
    void listenServer(char* buff);
    static void *sendToServerHelper(void *);
    void sendToServer();
    
};


#endif //GAME_PLAYER_H
