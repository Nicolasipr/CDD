//
// Created by nicolasipr on 14/10/2019.
//

#include "Board.h"
#include <iostream>
using namespace std;


Board::Board() {
    cout << "Board has been created\n";
}
Board::~Board() {
    cout << "Board has been destroyed\n ";

}
void Board::showBoard() {
    system("clear");
    for (int i = 0; i <= (height + scoreBoard); i++){
        if ( i == scoreBoard/2) {
            cout << "#\tPlayer 1 Score: "<< playerOneScore <<"  \t\t" << "  #\tPlayer 2 Score : " << playerTwoScore <<"\t\t";
        }

        for ( int j = 0; j <= (width); j++){

            if( i == ballYPosition && j == ballXPosition) {
                cout << "O";
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