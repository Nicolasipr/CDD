//
// Created by nicolasipr on 14/10/2019.
//

#include "includes/Board.h"

#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

// CONSTRUCTOR
Board::Board() {
}

// DESTRUCTOR
Board::~Board() {
}

/*
 *  BALL SETTINGS AND HANDLERS
 *
 *  setBallPos() -> modifies the current ball position.
 *  getXPos() -> Gets the current X position of the ball on the board
 *  getYPos() ->  gets the current Y position of the ball on the board
 *  getBallXDirection() ->
 *  getBallYDirection() ->
 *  resetBall() ->  resets  ball position to initial values
 * */
void Board::setBallPos(int posX, int posY) {
    ballXPosition = posX;
    ballYPosition = posY;
}

int Board::getXPos(){
    return ballXPosition;
}

int Board::getYPos(){
    return ballYPosition;
}
int Board::getBallXDirection(){
    return ballXDirection;
}

int Board::getBallYDirection(){
    return ballYDirection;
}

void Board::resetBall() {
    ballXPosition = width/2;
    ballYPosition = (height + scoreBoard)/2;
}

/*
 *  Player HANDLERS AND FUNCTIONS
 *
 *  showBoard() -> displays data, players and ball onto the board.
 *  ballHandler() ->
 *  gameHandler() ->
 *
 * */

//int Board::getPlayerOneYPos() {
//    return playerOnePos;
//}
//int Board::getPlayerTwoYPos() {
//    return playerTwoPos;
//}

/*
 *  GAME HANDLERS AND FUNCTIONS
 *
 *  showBoard() -> displays data, players and ball onto the board.
 *  ballHandler() ->
 *  gameHandler() ->
 *
 * */




void Board::ballHandler() {

    int board = height + scoreBoard,
        x = getXPos(),
        y = getYPos(),
        yDir  = getBallYDirection(),
        xDir  = getBallXDirection();

    //      WALLS
    // upper wall
    if( y == scoreBoard + 1){
        if( (y + yDir) == scoreBoard){
             ballYDirection = 1; // down
        }
    }
    // bottom wall
    if( y == scoreBoard + height - 1){
        if( (y + yDir) == board){
            ballYDirection = -1; // up
        }
    }
    //      PLAYERS PADS

    // Player One
    if( x + xDir == 4) {
        if( getPlayerOneYPos() == y  || getPlayerOneYPos() + 1 == y ){ // first to paddles
            ballYDirection = -1;
            ballXDirection = 1;
        }
        else if ( getPlayerOneYPos() + 2 == y  || getPlayerOneYPos() + 3 == y){ // middle segment
                ballYDirection = 0;
                ballXDirection = 1;
            }
        else if ( getPlayerOneYPos() + 4 == y  || getPlayerOneYPos() + 5 == y){ // last segment paddles
            ballYDirection = 1;
            ballXDirection = 1;
        }
    }
    // Player Two
    if( x + xDir == width - 4) {
        if( getPlayerTwoYPos() == y  || getPlayerTwoYPos() + 1 == y ){ // first to paddles
            ballYDirection = -1;
            ballXDirection = -1;
        }
        else if ( getPlayerTwoYPos() + 2 == y  || getPlayerTwoYPos() + 3 == y){ // middle segment
            ballYDirection = 0;
            ballXDirection = -1;
        }
        else if ( getPlayerTwoYPos() + 4 == y  || getPlayerTwoYPos() + 5 == y){ // last segment paddles
            ballYDirection = 1;
            ballXDirection = -1;
        }
    }


    //      SCORING POINTS
    // P1
    if( x == (width - 1) ){
        setPlayerOneScore( getPlayerOneScore() + 1);
        resetBall();
        ballXDirection = -1; // left
    }
    // P2
    if( x == 1 ){
        setPlayerTwoScore( getPlayerTwoScore() + 1 );
        resetBall();
        ballXDirection = 1; // right
    }
    //          MOVING BALL
    int nextX = getXPos() + ballXDirection,
        nextY = getYPos() + ballYDirection;
    setBallPos(nextX, nextY);
}
void Board::showBoard() {

    system("clear");
    int k1 = 0,
        k2 = 0;

    for (int i = 0; i <= (height + scoreBoard); i++){
        if ( i == scoreBoard/2) {
            cout << "#\tPlayer 1 Score: "<< getPlayerOneScore() <<"  \t\t" << "  #\tPlayer 2 Score : " << getPlayerTwoScore() <<"\t\t";
        }

        for ( int j = 0; j <= (width); j++){
            // Printing ball
            if( i == ballYPosition && j == ballXPosition) {
                cout << pongBall;
                continue;
            }
            // printing board
            if(i == 0 || i == (height + scoreBoard) || i == scoreBoard ){
                if(i == scoreBoard/2) {
                    continue;
                }
                else {
                    cout << "#";
                }

            }
            else if ( j == 0 || j == (width) || (j == width/2 && i <= scoreBoard) ){

                cout << "#";
            }
            else if ( i == scoreBoard/2 ) {
                continue;
            }

            // printing middle line
            else if ( j == width/2 && i > scoreBoard){
                cout << "|";
            }

             // players
           else if( j == 4){
                if(  i >= getPlayerOneYPos() && (getPlayerOneYPos() + 6) <= (height + scoreBoard - 1 ) && i > scoreBoard){
                    if( k1 < 6) {
                        cout << playerOnePaddle[k1];
                        k1++;
                    }
                    else{
                        cout << " ";
                    }
                }
                else{
                    cout << " ";
                }
           }

          else if( (width - j) == 4){
                if(  i >= getPlayerTwoYPos() && (getPlayerTwoYPos() + 6) <= (height + scoreBoard - 1 ) && i > scoreBoard){
                    if( k2 < 6) {
                        cout << playerTwoPaddle[k2];
                        k2++;
                    }
                    else{
                        cout << " ";
                    }
                }
                else{
                    cout << " ";
                }
           }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

}
void Board::gameHandler() {
    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(getFPS()));
        ballHandler();
        showBoard();

    }while( getPlayerTwoScore() < 3 || getPlayerOneScore() < 3);
}
