//
// Created by pivov on 25-Dec-16.
//

#include "Player.h"

Player::Player(char *nick, char *ip, int socket)
{
    this->nick = nick;
    this->ip = ip;
    this->socket = socket;

    this->message_in = (char *) malloc(msg_length);
    this->message_out = (char *) malloc(msg_length);
}