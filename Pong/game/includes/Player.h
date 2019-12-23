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
//    char paddle[7] = "123456";
    int paddleYPos = 0; // centering players paddle.
    int paddleXPos  = 0;

    char key[31] = "@PoNg_CdD_iN_C++_HaVe_FuN!@";
    int socket_fd;
    struct sockaddr_in server;

public:
    Player();
    ~Player();

    void joinGame(); // Players request to enter the game to default side.
    void connection(); // Stablish Connection with Server and it stays connetected while client is running
    void closeConnection(); // closes socket
    void recvHandler(char *); // It Handles data received from Server

    void playerInput();
    char* createMessage(char * msg); // Creates a message to send whenever a key is pressed to update players condition.
    void sendMessage();
    void control();

//    int getPaddleYPos();
//    void setPaddleYPos();

    int getPaddleXPos();
    int getPlayerSide();

    char * getPaddle();
    void sendPosY();



};


#endif //GAME_PLAYER_H
