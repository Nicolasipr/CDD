//
// Created by nicolasipr on 03/11/2019.
//

#include "Game.h"

Game::Game() {
    cout << "\n\n\n\t\tLoading...";
}

Game::~Game() {
    cout << "Thanks for playing!";
}
void Game::controlInput() {
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    // do {
    c=getchar();
    //  printf("%c ",c);
    // } while(c!='q');

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    return c;
}