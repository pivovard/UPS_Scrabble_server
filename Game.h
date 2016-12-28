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

    Player *player1;
    Player *player2;
    Player *player3;
    Player *player4;

    Game(int id);
};

#endif //UPS_SCRABBLE_SERVER_GAME_H
