//
// Created by pivov on 25-Dec-16.
//

#include "Game.h"

Game::Game(int id, Player *pl1, Player *pl2)
{
    this->id = id;
    this->PlayerCount = 2;
    this->PlayerNext = -1;
    this->PlayerDisconnected = 0;

    this->Players.push_back(pl1);
    this->Players.push_back(pl2);

    this->Init();
}

Game::Game(int id, Player *pl1, Player *pl2, Player *pl3)
{
    this->id = id;
    this->PlayerCount = 3;
    this->PlayerNext = -1;

    this->Players.push_back(pl1);
    this->Players.push_back(pl2);
    this->Players.push_back(pl3);

    this->Init();
}

Game::Game(int id, Player *pl1, Player *pl2, Player *pl3, Player *pl4)
{
    this->id = id;
    this->PlayerCount = 4;
    this->PlayerNext = -1;

    this->Players.push_back(pl1);
    this->Players.push_back(pl2);
    this->Players.push_back(pl3);
    this->Players.push_back(pl4);

    this->Init();
}

void Game::Init()
{
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->matrix[i][j] = '\0';
        }
    }

    string msg = "GAME:" + to_string(id) + ":";
    for(int i = 0; i < PlayerCount; i++){
        Players[i]->GameID = id;

        msg += to_string(Players[i]->id);
        msg += ",";
        msg += Players[i]->nick;
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
    if(PlayerDisconnected + 1 == PlayerCount || PlayerDisconnected == PlayerCount) return; //pokud je pocet mensi jak 2, nelze hrat

    PlayerNext++;
    if(PlayerNext == PlayerCount) PlayerNext = 0;

    if(Players[PlayerNext]->connected > 0) this->NextTurn();

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

    this->NextTurn();
}

void Game::SendTurn(string msg)
{
    msg = "TURNP:" + to_string(Players[PlayerNext]->id) + ":" + msg + "\n";

    for(int i = 0; i < PlayerCount; i ++){
        if(i == PlayerNext) continue;
        if(Players[i]->connected > 0) continue;
        Players[i]->SendToPlayer(msg);
    }
}


void Game::Reconnect(int id)
{
    string msg = "GAMER:" + to_string(id) + ":";
    for(int i = 0; i < PlayerCount; i++){
        msg += to_string(Players[i]->id);
        msg += ",";
        msg += Players[i]->nick;
        msg += ",";
        msg += to_string(Players[i]->score);
        msg += ";";
    }
    msg = msg.substr(0, msg.length() - 1);
    msg += ":";
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(matrix[i][j] != '\0'){
                msg += to_string(i) + "," + to_string(j) + "," + to_string(matrix[i][j]);
                msg += ";";
            }
        }
    }
    msg = msg.substr(0, msg.length() - 1);

    for(int i = 0; i < PlayerCount; i ++) {
        if (Players[i]->id == id) {
            Players[i]->SendToPlayer(msg);
            break;
        }
    }

    this->PlayerDisconnected--;
    this->NextTurn();
}