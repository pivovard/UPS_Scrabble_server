//
// Created by pivov on 01-Jan-17.
//

#ifndef UPS_SCRABBLE_SERVER_GAMEMANAGER_H
#define UPS_SCRABBLE_SERVER_GAMEMANAGER_H

#include "stdafx.h"

#include "Network.h"
#include "Game.h"
#include "Player.h"

class GameManager
{

public:

    static Player* PlayerConnect(char *nick, char *ip, int socket);

private:
    static int game_count;
    static int player_count;
    static vector<Game*> GameList;
    static vector<Player*> PlayerList;

    static void Start2Game();

    static void Run2Game();
};

#endif //UPS_SCRABBLE_SERVER_GAMEMANAGER_H
