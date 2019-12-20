//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "./includes/Board.h"
#include "./includes/Player.h"
#include "./includes/Ball.h"
#include "./includes/Menu.h"


class Game {
public:
    Game();
    ~Game();
    void update();
    void controlInput();

private:
    auto    FPS = 30;
    Board   boardGrid;
    Player  Player1,
            Player2;
    Ball    ball;
};


#endif //PONG_GAME_H
