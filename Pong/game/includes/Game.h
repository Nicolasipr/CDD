//
// Created by nicolasipr on 03/11/2019.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H
#include <netinet/in.h> // socket struct


//class Board;

class Game {

private:
    // general settings
    int    FPS = 50;
    int gameMode = 1; // 1: easy(200). 2: Medium (50) , 3: Hard (20), 4: Progressive

    // server information.
    const char * serverAddress = "localhost";
    int serverPort = 7777;
    bool serverStatus = false;
    unsigned int players_count = 0;
    int sockfd,
        p1Sock,
        p2Sock;
    struct sockaddr_in servaddr,
                        cliaddr,
                        p1Client,
                        p2Client;


    // board information.
    const int width = 84;
    const int height = 20;
    const int scoreBoard = 4;

//  Player One Settings

    char player1Name = ' ';
    int playerOneScore = 0;
    int playerOnePos = (height + scoreBoard)/2 - 2;
    char p1UpKey = 'w';
    char p1DownKey = 's';

//    Player Two Settings

    char player2Name = ' ';
    int playerTwoScore = 0;
    int playerTwoPos = (height + scoreBoard)/2 - 2;
    char p2UpKey = 'i';
    char p2DownKey = 'k';

    // Ball information
    int ballXPosition = width/2;
    int ballYPosition = (height + scoreBoard)/2;
    int ballXDirection = 1; // 1: left && -1: right
    int ballYDirection = 1; // 1: down && -1: up

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

    int getPlayerOneYPos();
    void setPlayerOnePos(int);

    int getPlayerTwoYPos();
    void setPlayerTwoPos(int);

    int getPlayerXPos(); //

    // BALL
    int getBallXPos();
    void setBallXPos(int);

    int getBallYPos();
    void setBallYPos(int );

    int getBallXDir();
    void setBallXDir(int );

    int getBallYDir();
    void setBallYDir(int);


    // TOOLS
    void update(); // updates data from players
    char controlInput(); // handles keyboard input without terminal buffer
    int kbhit(void);
    char* encryption( char* msg, char* key);
    char* decrypt( char* msg, char* key);
    char getRandomChar();
    void setDifficulty(int n_difficulty);

    // Server side
    char * getAddress();
    bool getServerStatus();
    void setServerStatus(bool n_status);
    void setAddress(const char * n_address);
    char * handlingMessage(char * msg, char * resp);

    // Threads
    static void *rcvMessageHelper(void *);
    char * rcvMessage(char * msg, char * resp);
    static void *rcvMessageHelperP2(void *);
    char * rcvMessageP2(char * msg, char * resp);
    char * rcvMessageFrom(int id_socket, struct sockaddr_in client, char * msg);
    static void *sendMessageHelper(void *);
    void sendMessageTo(int id_socket, struct sockaddr_in client, char * msg);

    int getPort();
    void setPort(int n_port);

    void setServerTCP(); // sets withs defaults options
    void setServerUDP(); // sets withs defaults options




};


#endif //PONG_GAME_H
