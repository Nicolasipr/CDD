//
// Created by nicolasipr on 15/10/2019.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


//#include "Board.h"
class Game;
#include "Game.h"

class Player : public Game {

private:
    char name[32] = "192.168.0.1";
    int playerScore = 0;
    int playerSide = 1; // 1 or 2
    char paddle[7] = "123456";
    int paddleYPos = 0; // centering players paddle.
    int paddleXPos  = 0;

public:
    Player(int newSide);
    ~Player();

    void connection();

    int getPaddleYPos();
    void setPaddleYPos();

    int getPaddleXPos();
    int getPlayerSide();

    char * getPaddle();
    void sendPosY();



};


#endif //GAME_PLAYER_H
