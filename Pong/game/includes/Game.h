//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H


//class Board;

class Game {

private:
    int    FPS = 20;
    int gameMode = 1; // 1: easy(200). 2: Medium (50) , 3: Hard (20), 4: Progressive
    const char * serverAddress = "localhost";
    int serverPort = 7777;
    bool serverStatus = false;
    unsigned int players_count = 0;
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;

//  Player One Settings

    char player1Name = ' ';
    int playerOneScore = 0;
//    const char* playerOnePaddle = "123456";
    int playerOnePos = (height + scoreBoard)/2 - 2;
    char p1UpKey = 'w';
    char p1DownKey = 's';

//    Player Two Settings

    char player2Name = ' ';
    int playerTwoScore = 0;
//    const char* playerTwoPaddle = "123456";
    int playerTwoPos = (height + scoreBoard)/2 - 2;
    char p2UpKey = 'i';
    char p2DownKey = 'k';

    char key[31] = "@PoNg_CdD_iN_C++_HaVe_FuN!@";

public:
    Game();
    ~Game();

     int getFPS();
     void setFPS(int n_fps);


    // PLAYERS
    int getPlayers();
    void setPlayers();
    int getPlayerOneScore();
    void setPlayerOneScore(int);
    int getPlayerTwoScore();
    void setPlayerTwoScore(int);



    void playerHandler();
    int getPlayerOneYPos();
    int getPlayerTwoYPos();
    int getPlayerXPos(); //

    // Tools
    void update(); // updates data from players
    char controlInput(); // handles keyboard input without terminal buffer
    char* encryption( char* msg, char* key);
    char* decrypt( char* msg, char* key);
    char getRandomChar();

    // Server side
    char * getAddress();
    bool getServerStatus();
    void setServerStatus(bool n_status);
    void setAddress(const char * n_address);
    char * handlingMessage(char * msg, char * resp);

    int getPort();
    void setPort(int n_port);

    void setServer(); // sets withs defaults options



};


#endif //PONG_GAME_H
