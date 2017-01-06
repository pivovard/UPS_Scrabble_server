//
// Created by pivov on 25-Dec-16.
//

#ifndef UPS_SCRABBLE_SERVER_PLAYER_H
#define UPS_SCRABBLE_SERVER_PLAYER_H

#include "stdafx.h"

class Player
{
public:
    char *nick;
    char *ip;
    int socket;

    int GameID;
    int score = 0;
    bool ready = false;

    char *message_in;
    char *message_out;

    Player(char *nick, char *ip, int socket);

    void SendToPlayer(string msg);
};

#endif //UPS_SCRABBLE_SERVER_PLAYER_H
