//
// Created by pivov on 25-Dec-16.
//

#include "Game.h"

Game::Game(int id)
{
    this->id = id;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->matrix[i][j] = '\0';
        }
    }

    cout << "Game " << id << " created." << endl;
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
            this->matrix[i][j] = '\0';
        }
    }

    string msg = "GAME:" + to_string(id) + ":";
    for(int i = 0; i < PlayerCount; i++){
        msg += to_string(Players[i]->id);
        msg += ",";
        msg += string(Players[i]->nick);
        msg += ";";
    }
    msg = msg.substr(0, msg.length() - 1);
    msg += "\n";

    for(int i = 0; i < PlayerCount; i++){
        Players[i]->SendToPlayer(msg);
    }

    cout << "Game " << id << " created." << endl;

    this->NextTurn();
}

void Game::NextTurn()
{
    //Players[PlayerNext].message_out = "TURN#";
    //Network::SendToPlayer(&Players[PlayerNext]);
    Players[PlayerNext]->SendToPlayer("TURN\n");
}

void Game::RecvTurn(string msg)
{
    this->SendTurn(msg);

    //score
    size_t i = msg.find(';');
    Players[PlayerNext]->score += stoi(msg.substr(0, i));

    int x;
    int y;
    char c;
    size_t  j;
    size_t  k;
    msg = msg.substr(i + 1);

    //doubles of numbers
    while((i = msg.find(';')) != string::npos){
        j = msg.find(',');
        k = msg.find(',', j);

        x = stoi(msg.substr(0, j));
        y = stoi(msg.substr(j + 1, k - j -1));
        c = msg.at(k+1);

        matrix[x][y] = c;

        msg = msg.substr(i + 1);
        cout << c << endl;
        cout << msg << endl;
    }


    PlayerNext++;
    if(PlayerNext == PlayerCount) PlayerNext = 0;
    this->NextTurn();
}

void Game::SendTurn(string msg)
{
    msg = "TURNP:" + to_string(Players[PlayerNext]->id) + ":" + msg + "\n";

    for(int i = 0; i < PlayerCount; i ++){
        if(i == PlayerNext) continue;
        Players[i]->SendToPlayer(msg);
    }
}


