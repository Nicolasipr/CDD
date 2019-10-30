//
// Created by nicolasipr on 14/10/2019.
//

#include <iostream>
#include <ncurses.h>
#include "Board.h"
#include "Player.h"
#include "Ball.h"

using namespace std;

int main(){

    Board Game;
    Player P1(1), P2(2);


    Game.gameHandler();

    return 0;
}