//
// Created by nicolasipr on 14/10/2019.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Game.h"
//#include "Player.h"

class Game;
//class Player;

class Board : public Game{ // hybrid inheritance

private:
    // Board limits
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;

//  Player One Settings

    char player1Name = ' ';
    int playerOneScore = 0;
    const char* playerOnePaddle = "123456";
    int playerOnePos = (height + scoreBoard)/2 - 2;
    char p1UpKey = 'w';
    char p1DownKey = 's';

//    Player Two Settings

    char player2Name = ' ';
    int playerTwoScore = 0;
    const char* playerTwoPaddle = "123456";
    int playerTwoPos = (height + scoreBoard)/2 - 2;
    char p2UpKey = 'i';
    char p2DownKey = 'k';

//  Ball Settings
    char pongBall = 'O';
    int ballXPosition = width/2;
    int ballYPosition = (height + scoreBoard)/2;
    int ballXDirection = 1; // 1: left && -1: right
    int ballYDirection = 1; // 1: down && -1: up

public:
    Board();
    Board(char newName);
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

    // PLAYERS
    void playerHandler();
    int getPlayerOneYPos();
    int getPlayerTwoYPos();
    int getPlayerXPos(); //

};


#endif //GAME_BOARD_H
