//
// Created by nicolasipr on 14/10/2019.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H


class Board {

private:
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 5;
    int playerOneScore = 0;
    int playerTwoScore = 0;

public:
    Board();
    ~Board();


};


#endif //GAME_BOARD_H
