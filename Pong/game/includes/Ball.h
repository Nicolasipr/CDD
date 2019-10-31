//
// Created by nicolasipr on 15/10/2019.
//
//#include "Board.cpp"
#ifndef GAME_BALL_H
#define GAME_BALL_H

#include "Board.h"


class Ball: public Board {

private:
    int xPosition = 0;
    int yPosition = 0;
    int xDirection = 0;
    int yDirection = 0;
    char pongBall = 'O';
public:
    Ball();
    ~Ball();
    int getPosX();
    int getPosY();
    int getBall();
};


#endif //GAME_BALL_H
