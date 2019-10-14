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

    for (int i = 0; i <= (height + scoreBoard); i++){
        if ( i == scoreBoard/2) {
            cout << "#\tUsername 1 Score: 99   \t\t" << "  #\tUsername 2 Score: 99\t\t";
        }

        for ( int j = 0; j <= (width); j++){

            if(i == 0 || i == (height + scoreBoard) || i == scoreBoard ){
                cout << "#";
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