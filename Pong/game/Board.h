//
// Created by nicolasipr on 14/10/2019.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H


class Board {

private:
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;
    int playerOneScore = 0;
    int playerTwoScore = 0;
    int ballXPosition = 0;
    int ballYPosition = 0;


public:
    Board();
    ~Board();
    void showBoard();

};


#endif //GAME_BOARD_H
