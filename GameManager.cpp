//
// Created by pivov on 01-Jan-17.
//

#include "GameManager.h"

int GameManager::game_count = 0;
int GameManager::player_count = 0;
vector<Game*> GameManager::GameList;
vector<Player*> GameManager::PlayerList;


Player* GameManager::PlayerConnect(char *nick, char *ip, int socket)
{
    Player *pl = new Player(nick, ip, socket, player_count);
    PlayerList.push_back(pl);
    player_count++;

    if((player_count % 2) == 0){
        GameManager::Start2Game();
    }

    return pl;
}

void GameManager::Start2Game()
{
    Game *game = new Game(game_count, PlayerList.at(player_count - 2), PlayerList.at(player_count - 1));
    GameList.push_back(game);
    game_count++;
}

void GameManager::ResolveTurn(string msg)
{
    size_t i = msg.find(':', 0);

    int id = stoi(msg.substr(0, i));
    msg = msg.substr(i + 1);

    GameList[id]->RecvTurn(msg);
}