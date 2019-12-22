//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H


class Board;

class Game {

private:
    int    FPS = 20;
    int gameMode = 1; // 1: easy(200). 2: Medium (50) , 3: Hard (20), 4: Progressive
    const char * serverAddress = "localhost";
    int serverPort = 7777;
    bool serverStatus = false;

    char key[31] = "@PoNg_CdD_iN_C++_HaVe_FuN!@";

public:
    Game();
    ~Game();

     int getFPS();
     void setFPS(int n_fps);
    // Tools
    void update(); // updates data from players
    char controlInput(); // handles keyboard input without terminal buffer
    char* encryption( char* msg, char* key);
    char* decrypt( char* msg, char* key);
    char getRandomChar();

    // Server side
    char * getAddress();
    void setAddress(const char * n_address);
    void handlingMessage();

    int getPort();
    void setPort(int n_port);

    void setServer(); // sets withs defaults options



};


#endif //PONG_GAME_H
