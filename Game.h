//
// Created by pivov on 25-Dec-16.
//

#ifndef UPS_SCRABBLE_SERVER_GAME_H
#define UPS_SCRABBLE_SERVER_GAME_H

#include "stdafx.h"

#include "Player.h"
//#include "Network.h"


class Game
{

public:
    int id;
    char matrix[15][15];

    int PlayerCount;
    int PlayerNext = 0;

    Player Players[];

    Game(int id);
    Game(int id, Player *pl1, Player *pl2);

private:

    void NextTurn();
};

#endif //UPS_SCRABBLE_SERVER_GAME_H
