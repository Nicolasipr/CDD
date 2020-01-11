//
// Created by nicolasipr on 14/10/2019.
//

#include "includes/Board.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <cstdio>
#include <cstdlib>
//#include <stdio.h>
//#include<stdlib.h>

using namespace std;

// directions;
int north = -1,
    south = 1,
    east = 1,
    west = -1,
    straight = 0;

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
    setBallXPos(posX);
    setBallYPos(posY);
}


void Board::resetBall() {
    int xMid = width/2,
        yMid = (height + scoreBoard)/2 ;
    setBallPos( xMid, yMid);
}

/*
 *  Player HANDLERS AND FUNCTIONS
 *
 *  showBoard() -> displays data, players and ball onto the board.
 *  ballHandler() ->
 *  gameHandler() ->
 *
 * */


/*
 *  GAME HANDLERS AND FUNCTIONS
 *
 *  showBoard() -> displays data, players and ball onto the board.
 *  ballHandler() ->
 *  gameHandler() ->
 *
 * */




void Board::ballHandler(int p1_pos, int p2_pos) {

    int board = height + scoreBoard,
        x = getBallXPos(),
        y = getBallYPos(),

        yDir  = getBallYDir(),
        xDir  = getBallXDir();

        setPlayerOnePos(p1_pos);
        setPlayerTwoPos(p2_pos);

    //      WALLS
    // upper wall
    if( y == scoreBoard + 1){
        if( (y + yDir) == scoreBoard){
            setBallYDir(south);
        }
    }
    // bottom wall
    if( y == scoreBoard + height - 1){
        if( (y + yDir) == board){
            setBallYDir(north);
        }
    }
    //      PLAYERS PADS

    // Player One
    if( x + xDir == 4) {
        if( getPlayerOneYPos() == y  || getPlayerOneYPos() + 1 == y ){ // first to paddles
            setBallXDir(east);
            setBallYDir(north);

        }
        else if ( getPlayerOneYPos() + 2 == y  || getPlayerOneYPos() + 3 == y){ // middle segment
            setBallXDir(east);
            setBallYDir(straight);

            }
        else if ( getPlayerOneYPos() + 4 == y  || getPlayerOneYPos() + 5 == y){ // last segment paddles
            setBallXDir(east);
            setBallYDir(south);

        }
    }
    // Player Two
    if( x + xDir == width - 4) {
        if( getPlayerTwoYPos() == y  || getPlayerTwoYPos() + 1 == y ){ // first to paddles
            setBallXDir(west);
            setBallYDir(north);

        }
        else if ( getPlayerTwoYPos() + 2 == y  || getPlayerTwoYPos() + 3 == y){ // middle segment
            setBallXDir(west);
            setBallYDir(straight);

        }
        else if ( getPlayerTwoYPos() + 4 == y  || getPlayerTwoYPos() + 5 == y){ // last segment paddles
            setBallXDir(west);
            setBallYDir(south);

        }
    }


    //      SCORING POINTS
    // P1
    if( x == (width - 1) ){
        setPlayerOneScore( getPlayerOneScore() + 1);
        resetBall();
        setBallXDir(west);

    }
    // P2
    if( x == 1 ){
        setPlayerTwoScore( getPlayerTwoScore() + 1 );
        resetBall();
        setBallXDir(east);

    }

    //          MOVING BALL
    int nextX = getBallXPos() + getBallXDir(),
        nextY = getBallYPos() + getBallYDir();
    setBallPos(nextX, nextY);
}
void Board::showBoard(int p1_pos, int p2_pos) {

    system("clear");
    fflush(stdin);
    int k1 = 0,
        k2 = 0;

    for (int i = 0; i <= (height + scoreBoard); i++){
        if ( i == scoreBoard/2) {
            cout << "#\tPlayer 1 Score: "<< getPlayerOneScore() <<"  \t\t" << "  #\tPlayer 2 Score : " << getPlayerTwoScore() <<"\t\t  ";
        }

        for ( int j = 0; j <= (width); j++){
            // Printing ball
            if( i == getBallYPos() && j == getBallXPos()) {
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
                if(  i >= p1_pos && (p1_pos + 6) <= (height + scoreBoard) && i > scoreBoard){
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
                if(  i >= p2_pos && (p2_pos + 6) <= (height + scoreBoard) && i > scoreBoard){
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
    std::cout.flush();
    fflush(stdin);

}
void Board::gameHandler() {
    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(getFPS()));

    }while( getPlayerTwoScore() < 3 || getPlayerOneScore() < 3);
}
