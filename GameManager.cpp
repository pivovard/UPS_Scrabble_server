//
// Created by pivov on 01-Jan-17.
//

#include "GameManager.h"

int GameManager::game_count = 0;
int GameManager::player_count = 0;
list<Game> GameManager::GameList;
list<Player> GameManager::PlayerList;


void GameManager::Start2Game()
{
    Game *game = new Game(game_count);
    GameList.push_back(*game);
    game_count++;
    cout << "Game " << game_count << " created." << endl;
}

Player* GameManager::PlayerConnect(char *nick, char *ip, int socket)
{
    Player *pl = new Player(nick, ip, socket);
    PlayerList.push_back(*pl);
    player_count++;

    return pl;
}