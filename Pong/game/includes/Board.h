//
// Created by nicolasipr on 14/10/2019.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Game.h"
//#include "Player.h"

class Game;
//class Player;

class Board : virtual public Game{ // hybrid inheritance (?

private:
    // Board limits
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;

////  Player One Settings
    const char* playerOnePaddle = "123456";

    const char* playerTwoPaddle = "123456";


//  Ball Settings
    char pongBall = 'O';
    int ballXPosition = width/2;
    int ballYPosition = (height + scoreBoard)/2;
    int ballXDirection = 1; // 1: left && -1: right
    int ballYDirection = 1; // 1: down && -1: up

public:
    Board();
    ~Board();

    // Game itself
    void gameHandler(); // handles data, ball movements and points
    void gameMenu(); // displays menu to show rules and display information about the game and creators
    void showBoard(); // displays board: players, ball, points, and more.

    // BALL
    void setBallPos(int posX, int posY);
    void resetBall();
    void ballHandler(); // bounces the ball and displaces it
    int getYPos();
    int getXPos();
    int getBallXDirection();
    int getBallYDirection();

//    // PLAYERS

};


#endif //GAME_BOARD_H
