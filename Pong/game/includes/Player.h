//
// Created by nicolasipr on 15/10/2019.
//
//#include "Board.cpp"
#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Board.h"

class Player: public Board {

private:
    int playerScore = 0;
    int playerSide = 1; // 1 or two
    char paddle[7] = "######";


public:
    Player(int newSide);
    ~Player();
};


#endif //GAME_PLAYER_H
