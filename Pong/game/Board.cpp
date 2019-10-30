//
// Created by nicolasipr on 14/10/2019.
//

#include "Board.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

using namespace std;

// CONSTRUCTOR
Board::Board() {
    cout << "Board has been created\n";
}

// DESTRUCTOR
Board::~Board() {
    cout << "Board has been destroyed\n ";

}
// NOT WORKING
void Board::onKey(){
    initscr();
    int k;
    do {
        k = getch();

    } while ( k != 27);
    endwin();
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
        yDir  = getBallYDirection();

    //      WALLS
    // upper wall
    if( y == scoreBoard + 1){
        if( (y + yDir) == scoreBoard){
             ballYDirection = 1;
        }
    }
    // bottom wall
    if( y == scoreBoard + height - 1){
        if( (y + yDir) == board){
            ballYDirection = -1;
        }
    }
    //      PLAYERS PADS

    //      SCORING POINTS
    // P1
    if( x == (width - 1) ){
        playerOneScore += 1;
        resetBall();
        ballXDirection = -1; // left
    }
    // P2
    if( x == 1 ){
        playerTwoScore += 1;
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
    for (int i = 0; i <= (height + scoreBoard); i++){
        if ( i == scoreBoard/2) {
            cout << "#\tPlayer 1 Score: "<< playerOneScore <<"  \t\t" << "  #\tPlayer 2 Score : " << playerTwoScore <<"\t\t";
        }

        for ( int j = 0; j <= (width); j++){

            if( i == ballYPosition && j == ballXPosition) {
                cout << pongBall;
                continue;
            }
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
            else if ( j == width/2 && i > scoreBoard){
                cout << "|";
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ballHandler();
        showBoard();
    }while(true);
}