//
// Created by pivov on 25-Dec-16.
//

#include "Game.h"

Game::Game(int id)
{
    this->id = id;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->matrix[i][j] = '*';
        }
    }
}

Game::Game(int id, Player *pl1, Player *pl2)
{
    this->id = id;
    this->PlayerCount = 2;
    this->PlayerNext = 0;


    this->Players[0] = pl1;
    Players[0]->GameID = id;

    this->Players[1] = pl2;
    Players[1]->GameID = id;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->matrix[i][j] = '*';
        }
    }

    Players[0]->SendToPlayer("GAME:" + string(Players[1]->nick) + "\n");
    Players[1]->SendToPlayer("GAME:" + string(Players[0]->nick) + "\n");

    this->NextTurn();
}

void Game::NextTurn()
{
    //Players[PlayerNext].message_out = "TURN#";
    //Network::SendToPlayer(&Players[PlayerNext]);
    Players[PlayerNext]->SendToPlayer("TURN\n");

    PlayerNext++;
    if(PlayerNext = PlayerCount) PlayerNext = 0;
}
