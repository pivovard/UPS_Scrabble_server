//
// Created by pivov on 25-Dec-16.
//

#include "Player.h"

Player::Player(string nick, int n, char *ip, int socket, int id)
{
    this->nick = nick;
    this->n = n;
    this->ip = ip;
    this->socket = socket;
    this->id = id;

    this->message_in = new char[msg_length];
    this->message_out = new char[msg_length];
}

void Player::SendToPlayer(string msg)
{
    cout << "Send to " << this->nick << ": " << msg << endl;

    ssize_t size = 0;
    while(size < msg.length()){
        //size = write(this->socket , msg.c_str() , msg_length);
        size = send(this->socket , msg.c_str() , msg_length, 0);
    }
}