//
// Created by nicolasipr on 22/12/2019.
//

#include "includes/Core.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

Core::Core() {

}

Core::~Core() {

}

void Core::playerHandler() {
    Player Client;
    Client.connection();
    Client.joinGame();

    while(getPlayerOneScore() < 3 || getPlayerTwoScore() < 3) {

        std::this_thread::sleep_for(std::chrono::milliseconds(getFPS()));
        ballHandler( Client.getPlayerOneYPos(), Client.getPlayerTwoYPos() );
        showBoard( Client.getPlayerOneYPos(), Client.getPlayerTwoYPos() );
        Client.sendMessage();
    }
    closeConnection();

}