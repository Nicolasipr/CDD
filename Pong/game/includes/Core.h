//
// Created by nicolasipr on 22/12/2019.
//

#ifndef PONG_CORE_H
#define PONG_CORE_H

#include "Player.h"
#include "Board.h"


class Core : public Board, public Player {

private:

public:
    Core();
    ~Core();

    void playerHandler();

};


#endif //PONG_CORE_H
