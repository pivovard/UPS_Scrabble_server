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

    static Player* PlayerConnect(string nick, char *ip, int socket, int n);
    static int CheckNick(string nick, int n);

    static void ResolveTurn(string msg);

private:
    static int game_count;
    static int player_count2;
    static int player_count3;
    static int player_count4;

    static vector<Game*> GameList;
    static vector<Player*> PlayerList2;
    static vector<Player*> PlayerList3;
    static vector<Player*> PlayerList4;

    static void Start2Game();
    static void Start3Game();
    static void Start4Game();
};

#endif //UPS_SCRABBLE_SERVER_GAMEMANAGER_H
