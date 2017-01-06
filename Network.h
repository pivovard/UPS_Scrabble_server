//
// Created by pivov on 23-Dec-16.
//

#ifndef UPS_SCRABBLE_SERVER_NETWORK_H
#define UPS_SCRABBLE_SERVER_NETWORK_H

#include "stdafx.h"

#include "GameManager.h"
#include "Player.h"


#define PORT 1993

class Network
{

public:

    static void Start();
    static void Listen();
    static void Exit();

    //static void SendToPlayer(Player *pl);

private:
    static int socket_desc , client_sock , c;
    static struct sockaddr_in server , client;

    static void PlayerListen(Player *pl);

    static string CropMsg(char *in, int size);
    static char* CropChar(char *in, int size);

    void SendMessage(int socket, string *message);
    void RecvMessage(int socket, string *message);

};

#endif //UPS_SCRABBLE_SERVER_NETWORK_H
