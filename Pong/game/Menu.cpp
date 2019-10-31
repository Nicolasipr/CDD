//
// Created by nicolasipr on 30/10/2019.
//

#include "includes/Menu.h"
#include "includes/Board.h"
#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>

using namespace std;

void displayName(){
    system("clear");
    clear();
    cout << "\n\n"
        << "\n\t\t    ____                    "
        << "\n\t\t   / __ \\____  ____  ____ _ "
        << "\n\t\t  / /_/ / __ \\/ __ \\/ __ `/ "
        << "\n\t\t / ____/ /_/ / / / / /_/ /  "
        << "\n\t\t/_/    \\____/_/ /_/\\__, /   "
        << "\n\t\t                  /____/    "
        << "\n\n\n";
    this_thread::sleep_for(chrono::milliseconds(3000));
    clear();
}
void displayMenu(){
    system("clear");
//        clear();
    cout << "\n\n\n"
         << "\n\t\t    __  ___                 "
         << "\n\t\t   /  |/  /__  ____  __  __"
         << "\n\t\t  / /|_/ / _ \\/ __ \\/ / / /"
         << "\n\t\t / /  / /  __/ / / / /_/ / "
         << "\n\t\t/_/  /_/\\___/_/ /_/\\__,_/  "
         << "\n\t\t  "
         << "\n\t\t  "
         << "\n\t\t  (1) PLAY!"
         << "\n\t\t  (2) OPTIONS"
         << "\n\t\t  (3) ABOUT"
         << "\n\t\t  (q) EXIT"
         << "\n\n\n";
    this_thread::sleep_for(chrono::milliseconds(500));
}
void displayOptions(){

    char key;
    do{
        system("clear");
        cout << "\n\n\n"
             << "\n\t\t   ____        __  _                 "
             << "\n\t\t  / __ \\____  / /_(_)___  ____  _____"
             << "\n\t\t / / / / __ \\/ __/ / __ \\/ __ \\/ ___/"
             << "\n\t\t/ /_/ / /_/ / /_/ / /_/ / / / (__  ) "
             << "\n\t\t\\____/ .___/\\__/_/\\____/_/ /_/____/  "
             << "\n\t\t    /_/                              "
             << "\n\t\t "
             << "\n\t\t "
             << "\n\t\t  (1) SERVER  "
             << "\n\t\t  (2) PLAYER 1"
             << "\n\t\t  (3) PLAYER 2"
             << "\n\t\t  (4) SPEED   "
             << "\n\t\t  (q) EXIT\n\n";

        this_thread::sleep_for(chrono::milliseconds(500));
        key = getchar();
        switch(key){
            case ERR:
                break;
            case '1':
                cout << "Setting up Server";
                break;
            case '2':
                cout << "Setting up Player 1";
                break;
            case('3'):
                cout << "Setting up Player 2";
                break;
            case('4'):
                cout << "Setting up Speed game";
                break;
            case('q'):
                key ='q';
                break;
            default:
                break;
        }
    }while( key != 'q');

}

void displayAbout(){
    char key;
    do{
        system("clear");
        cout << "\n\n\n"
             << "\n\t\t    ___    __                __"
             << "\n\t\t   /   |  / /_  ____  __  __/ /_"
             << "\n\t\t  / /| | / __ \\/ __ \\/ / / / __/"
             << "\n\t\t / ___ |/ /_/ / /_/ / /_/ / /_"
             << "\n\t\t/_/  |_/_.___/\\____/\\__,_/\\__/"
             << "\n\t\t "
             << "\n\t\t "
             << "\n\t  This Game was developed by Nicolas Perez Roa"
             << "\n\t  as an assignment for Data Communication"
             << "\n\t  at Metropolitan University of Technology."
             << "\n\t  This Pong is an UDP client to server multi-player"
             << "\n\t  online game, where clients sends its X & Y position"
             << "\n\t  for the game to process."
             << "\n\n\n\n Press \"q\" to Exit to main Menu ...\n\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        key = getchar();
        switch(key){
            case ERR:
                break;
            case('q'):
                key ='q';
                break;
            default:
                break;
        }
    }while( key != 'q');
}

void initGame(){

    displayName();
    Board Game;
    char key;
    do{
        displayMenu();
        this_thread::sleep_for(chrono::milliseconds(500));
        key = getchar();
        switch(key){
            case ERR:
                break;
            case '1':
                cout << "Entering into the game";
//                endwin();
                Game.gameHandler();
                break;
            case '2':
                displayOptions();
                cout << "Entering into Options";
                break;
            case('3'):
                cout << "Entering About";
                displayAbout();
                break;
            case('q'):
                key ='q';
                break;
            default:
                break;
        }
    }while( key != 'q');
//    endwin();
}