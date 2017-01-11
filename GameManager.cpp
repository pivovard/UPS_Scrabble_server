//
// Created by pivov on 01-Jan-17.
//

#include "GameManager.h"

int GameManager::game_count = 0;
int GameManager::player_count2 = 0;
int GameManager::player_count3 = 0;
int GameManager::player_count4 = 0;

vector<Game*> GameManager::GameList;
vector<Player*> GameManager::PlayerList2;
vector<Player*> GameManager::PlayerList3;
vector<Player*> GameManager::PlayerList4;


Player* GameManager::PlayerConnect(string nick, char *ip, int socket, int n)
{
    Player *pl;
    switch(n)
    {
        case 2:
            pl = new Player(nick, ip, socket, player_count2);
            PlayerList2.push_back(pl);
            player_count2++;

            if((player_count2 % 2) == 0){
                GameManager::Start2Game();
            }
            break;
        case 3:
            pl = new Player(nick, ip, socket, player_count3);
            PlayerList3.push_back(pl);
            player_count3++;

            if((player_count3 % 3) == 0){
                GameManager::Start3Game();
            }
            break;
        case 4:
            pl = new Player(nick, ip, socket, player_count4);
            PlayerList4.push_back(pl);
            player_count4++;

            if((player_count4 % 4) == 0){
                GameManager::Start4Game();
            }
            break;
    }

    return pl;
}

int GameManager::CheckNick(string nick, int n)
{
    switch(n)
    {
        case 2:
            for(int i = 0; i < player_count2; i++){
                if(nick == PlayerList2[i]->nick) return 1;
            }
            break;
        case 3:
            for(int i = 0; i < player_count3; i++){
                if(nick == PlayerList3[i]->nick) return 1;
            }
            break;
        case 4:
            for(int i = 0; i < player_count4; i++){
                if(nick == PlayerList4[i]->nick) return 1;
            }
            break;
    }

    return 0;
}

void GameManager::Start2Game()
{
    Game *game = new Game(game_count, PlayerList2.at(player_count2 - 2), PlayerList2.at(player_count2 - 1));
    GameList.push_back(game);
    game_count++;
}

void GameManager::Start3Game()
{
    Game *game = new Game(game_count, PlayerList3.at(player_count3 - 3), PlayerList3.at(player_count3 - 2), PlayerList3.at(player_count3 - 1));
    GameList.push_back(game);
    game_count++;
}

void GameManager::Start4Game()
{
    Game *game = new Game(game_count, PlayerList4.at(player_count4 - 4), PlayerList4.at(player_count4 - 3), PlayerList4.at(player_count4 - 2), PlayerList4.at(player_count4 - 1));
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