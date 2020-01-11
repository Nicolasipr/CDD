//
// Created by nicolasipr on 30/10/2019.
//

#include "includes/Menu.h"
#include "includes/Board.h"
#include "includes/Game.h"
#include "includes/Player.h"
#include "includes/Core.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cstring>


using namespace std;

Game Pong;
Core core;

void showControls(){
    system("clear");
    cout << "\n\n\t\t Players Controls " << endl
        << "\t  PLayer 1  \t|\t  Player 2" << endl
        << "\tUP KEY   = w\t|\t UP KEY   = i" << endl
        << "\tDOWN KEY = s\t|\t DOWN KEY = k" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}
void setAddressHelper(){
    cout << "Input your new Address : " ;
    string new_address;
    cin >> new_address;
    char *cstr = &new_address[0];
    core.setAddress( cstr );

}

void setPortHelper(){
    cout << "Input your new Port : " ;
    int port;
    cin >> port;
    if(port >= 1024 && port < 65535){
        core.setPort(port);
    }
    else
        cout << "\nPort given is not in range of [1024, 65535[ usable ports" << endl;
}

void displayName(){
    system("clear");
    cout << "\n\n"
        << "\n\t\t    ____                    "
        << "\n\t\t   / __ \\____  ____  ____ _ "
        << "\n\t\t  / /_/ / __ \\/ __ \\/ __ `/ "
        << "\n\t\t / ____/ /_/ / / / / /_/ /  "
        << "\n\t\t/_/    \\____/_/ /_/\\__, /   "
        << "\n\t\t                  /____/    "
        << "\n\n\n";
    this_thread::sleep_for(chrono::milliseconds(3000));

}
void displayMenu(){
    system("clear");
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
    this_thread::sleep_for(chrono::milliseconds(200));
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

        this_thread::sleep_for(chrono::milliseconds(200));
        key = Pong.controlInput();
        switch(key = Pong.controlInput() ){

            case '1':
               serverOptions();
                cin.sync();
                break;

            case '2':
                playerOptions();
                cin.sync();
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
    }while( (key = Pong.controlInput() ) != 'q');

}

void serverOptions(){
    char key;
    do{
        system("clear");
        cout << "\n\n\t\t Current Server Options " << endl
             << "\n\tAddress: " << core.getAddress() << endl
             << "\tPort : " << core.getPort() << endl
             << "\tGame Mode: " << core.getFPS() << endl
             << "\n\n Are you sure to continue with current setting?" << endl
             << "\n\t\t Y | N " << endl;

        if( tolower( Pong.controlInput() ) == 'y'){
            system("clear");
            cout << "Setting up Server...\n" << endl;
            core.serverHandler();
        }
        else {
            system("clear");
            cout << "\n\n\t\tSetting up Server...\n" << endl
                 << "(1) Change Address" << endl
                 << "(2) Change Port" << endl
                 << "(3) Change Game Mode" << endl
                 << "(q) Change Address" << endl;

        }
        this_thread::sleep_for(chrono::milliseconds(200));
        key = Pong.controlInput();

        switch(key = Pong.controlInput() ){
            case '1':
                setAddressHelper();
                break;
            case '2':
               setPortHelper();
                break;
            case '3':
                break;
            case 'q':
                break;

        }

    } while( (key = Pong.controlInput() ) != 'q');

}

void playerOptions(){
    cout << "\n\n\t\t Current Server Options " << endl
         << "\n\tAddress: " << core.getAddress() << endl
         << "\tPort : " << core.getPort() << endl
         << "\tGame Mode: " << core.getFPS() << endl
         << "\n\n Are you sure to continue with current setting?" << endl
         << "\n\t\t Y | N " << endl;

    if( tolower( Pong.controlInput() ) == 'y'){
        system("clear");
        cout << "Setting up Player 1";
        core.playerHandler();
    }
    cin.sync();

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
             << "\n\t  online game, where clients sends its Y position"
             << "\n\t  for the game to process."
             << "\n\n\n\n Press \"q\" to Exit to main Menu ...\n\n";
        this_thread::sleep_for(chrono::milliseconds(200));
        key = Pong.controlInput();
        switch(key){

            case('q'):
                key ='q';
                break;
            default:
                break;
        }
    }while( (key = Pong.controlInput() ) != 'q');
}

void initGame(){

    displayName();
//    Board Court;
//    Game Pong;
    char key;
    do{
        displayMenu();
        this_thread::sleep_for(chrono::milliseconds(200));
        switch( key = Pong.controlInput() ){

            case '1':

                if(1){
                    system("clear");
                    cout << "Entering into the game";
                    showControls();
                    core.playerHandler();
                }
                else{
                }

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
    }while( (key = Pong.controlInput() ) != 'q');

}