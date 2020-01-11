//
// Created by nicolasipr on 22/12/2019.
//

#include "includes/Core.h"
#include "includes/Menu.h"

#include <chrono>
#include <thread>
#include <pthread.h>
#include <iostream>

using namespace std;

Core::Core() {

}

Core::~Core() {

}
void Core::serverHandler() {
    Game Server;
    Server.setServerUDP();

    // threads init
    pthread_t recv_thread,
            recvP2_thread,
            send_thread;
//            sendP2_thread;
    pthread_create(&recv_thread, NULL, Server.rcvMessageHelper,&Server);
    pthread_create(&recvP2_thread, NULL, Server.rcvMessageHelperP2,&Server);
//    pthread_create(&send_thread, NULL, Server.sendMessageHelper,&Server);
    // threads for recv and sending data
    int i = 0;
    while(getPlayerOneScore() < 3 && getPlayerTwoScore() < 3) {
//        cout << "\n Iteration Number > " << i++;

        ballHandler( Server.getPlayerOneYPos(), Server.getPlayerTwoYPos() );
        Server.setBallXPos( getBallXPos() );
        Server.setBallYPos( getBallYPos() );
        std::this_thread::sleep_for(std::chrono::milliseconds(getFPS()));
    }

    // join threads
    pthread_join(recv_thread, NULL);
    pthread_join(recvP2_thread, NULL);
//    pthread_join(send_thread, NULL);


}

void Core::playerHandler() {
    Player Client;
    Client.connectionUDP();
    Client.joinGame();

    auto maxTime = 15; // seconds
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); // counter starts for 15 seconds

    while(!Client.getServerStatus()){
        system("clear");
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << "\nElapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]";
        cout << "\nWaiting for more connections..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        Client.sendMessage(); // asks and updates

        if(maxTime == std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()){
            system("clear");
            cout << "\n\n\n\t\tCongratulations YOU have won!... "
                << "\n\t\tSadly because nobody joined the game..."
                << "\n\nGoing Back to Main Menu" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            Client.~Player();
            initGame();
        }
        fflush(NULL);
    }
    pthread_t listen_thread,
              p1Send_thread;

    pthread_create(&listen_thread, NULL, Client.listenServerHelper,&Client);
    pthread_create(&p1Send_thread, NULL, Client.sendToServerHelper,&Client);
//    int i = 0;
    while(getPlayerOneScore() < 3 && getPlayerTwoScore() < 3) {

        fflush(NULL);
        fflush(stdin);
        fflush(stdout);
        setBallYPos(Client.getBallYPos());
        setBallXPos(Client.getBallXPos());
        ballHandler( Client.getPlayerOneYPos(), Client.getPlayerTwoYPos() );

        showBoard( Client.getPlayerOneYPos(), Client.getPlayerTwoYPos() );

        std::cout.flush();
//        std::this_thread::sleep_for(std::chrono::milliseconds(getFPS()));

        fflush(NULL);
    }
    // join threads
    pthread_join(listen_thread, NULL);
    pthread_join(p1Send_thread, NULL);
    // closes socket connection;
    Client.~Player();
    initGame();

}