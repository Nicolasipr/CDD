//
// Created by nicolasipr on 14/10/2019.
//

#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "Board.h"
#include "Player.h"
#include "Ball.h"

using namespace std;

int main(){

    Board Game;
    Player P1(1), P2(2);
    int x = Game.getXPos(),
    y = Game.getYPos();

    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Game.showBoard();
        Game.setBallPos(x++, y++);
    }while(true);
    Game.showBoard();

//    Game.onKey();

    return 0;
}