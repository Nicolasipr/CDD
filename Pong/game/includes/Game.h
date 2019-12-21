//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H


class Board;

class Game {

private:
    int    FPS = 30;
    const char * serverAddress = "localhost";
    int serverPort = 7777;
    bool serverStatus = false;

public:
    Game();
    ~Game();

    // Tools
    void update(); // updates data from players
    char controlInput(); // handles keyboard input without terminal buffer
    char* encryption( char* msg, char* key);
    char* decrypt( char* msg, char* key);
    char getRandomChar();

    // Server side
    char * getAddress();
    void setAddress(const char * n_address);

    int getPort();
    void setPort(int n_port);

    void setServer(); // sets withs defaults options



};


#endif //PONG_GAME_H
