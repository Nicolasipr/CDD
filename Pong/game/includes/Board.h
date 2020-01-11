//
// Created by nicolasipr on 14/10/2019.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Game.h"

//#include "Player.h"


class Board : virtual public Game{

private:
    // Board limits
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;

////  Player One and Two Settings
    const char* playerOnePaddle = "123456";
    const char* playerTwoPaddle = "123456";

//  Ball Settings
    char pongBall = 'O';

public:
    Board();
    ~Board();

    // Game itself
    void gameHandler(); // handles data, ball movements and points
    void gameMenu(); // displays menu to show rules and display information about the game and creators
    void showBoard(int, int); // displays board: players, ball, points, and more.

    // BALL
    void setBallPos(int posX, int posY);
    void resetBall();
    void ballHandler(int, int); // bounces the ball and displaces it

};


#endif //GAME_BOARD_H
