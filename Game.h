//
// Created by pivov on 25-Dec-16.
//

#ifndef UPS_SCRABBLE_SERVER_GAME_H
#define UPS_SCRABBLE_SERVER_GAME_H

#include "stdafx.h"

#include "Player.h"


class Game
{

public:
    int id;
    char matrix[15][15];

    int PlayerCount;
    int PlayerNext;

    //pole 2...pri rozsireni na 4
    Player *Players[2];

    Game(int id);
    Game(int id, Player *pl1, Player *pl2);

    void RecvTurn(string msg);

private:

    void NextTurn();
    void SendTurn(string msg);
};

#endif //UPS_SCRABBLE_SERVER_GAME_H
