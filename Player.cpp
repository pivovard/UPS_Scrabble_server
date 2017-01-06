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

void Player::SendToPlayer(string msg)
{
    cout << "Send to " << this->nick << ": " << msg << endl;

    //this->message_out = msg.c_str();
    int size = write(this->socket , msg.c_str() , msg_length);
    //send(this->socket , msg.c_str() , msg_length, 0);
    cout << size << endl;
}