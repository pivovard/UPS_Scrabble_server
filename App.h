//
// Created by pivov on 25-Dec-16.
//

#ifndef UPS_SCRABBLE_SERVER_APP_H
#define UPS_SCRABBLE_SERVER_APP_H

#include "stdafx.h"

#include "Network.h"
#include "Game.h"
#include "Player.h"

class App
{

public:
    App();

    static Player* PlayerConnect(char *nick, char *ip, int socket);
    static void Command();

private:
    static int game_count;
    static int player_count;
    static list<Game> GameList;
    static list<Player> PlayerList;

    Network *network;

};

#endif //UPS_SCRABBLE_SERVER_APP_H
