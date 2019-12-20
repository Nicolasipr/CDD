//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

class Player;
class Board;
class Ball;

//#include "Board.h"
//#include "Player.h"
//#include "Ball.h"
//#include "Menu.h"

//typedef class Player Player;
class Game {

private:
    int    FPS = 30;
    const char * serverAddress = "localhost";
    int serverPort = 7777;
    bool serverStatus = false;
//    Board   boardGrid;
////    Player  *Player1,
////            *Player2;
//    Ball    *ball();

public:
    Game();
    ~Game();

    // Tools
    void update(); // updates data from players
    char controlInput(); // handles keyboard input without terminal buffer

    // Server side
    char * getAddress();
    void setAddress(const char * n_address);

    int getPort();
    void setPort(int n_port);

    void setServer(); // sets withs defaults options



};


#endif //PONG_GAME_H
