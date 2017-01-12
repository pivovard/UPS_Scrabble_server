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

            if((PlayerList2.size() % 2) == 0){
                GameManager::Start2Game();
            }
            break;
        case 3:
            pl = new Player(nick, ip, socket, player_count3);
            PlayerList3.push_back(pl);
            player_count3++;

            if((PlayerList3.size() % 3) == 0){
                GameManager::Start3Game();
            }
            break;
        case 4:
            pl = new Player(nick, ip, socket, player_count4);
            PlayerList4.push_back(pl);
            player_count4++;

            if((PlayerList4.size() % 4) == 0){
                GameManager::Start4Game();
            }
            break;
    }

    return pl;
}

void GameManager::ResolveTurn(string msg)
{
    size_t i = msg.find(':', 0);

    int id = stoi(msg.substr(0, i));
    msg = msg.substr(i + 1);

    for(int i = 0; i < GameList.size(); i++){
        if(GameList[i]->id == id){
            GameList[i]->RecvTurn(msg);
            break;
        }
    }
}

Player* GameManager::GetPlayer(string nick, int n)
{
    switch(n)
    {
        case 2:
            for(int i = 0; i < PlayerList2.size(); i++){
                if(nick == PlayerList2[i]->nick && PlayerList2[i]->connected < 2){
                    return PlayerList2[i];
                }
            }
            break;
        case 3:
            for(int i = 0; i < PlayerList3.size(); i++){
                if(nick == PlayerList3[i]->nick && PlayerList2[i]->connected < 2) {
                    return PlayerList3[i];
                }
            }
            break;
        case 4:
            for(int i = 0; i < PlayerList4.size(); i++){
                if(nick == PlayerList4[i]->nick && PlayerList2[i]->connected < 2) {
                    return PlayerList4[i];
                }
            }
            break;
    }

    return 0;
}

int GameManager::CheckNick(string nick, int n)
{
    switch(n)
    {
        case 2:
            for(int i = 0; i < PlayerList2.size(); i++){
                if(nick == PlayerList2[i]->nick){
                    if(PlayerList2[i]->connected == 0) return 2; //pripojen hrajici, nick neni k dispozici
                    if(PlayerList2[i]->connected == 1) return 1; //znovu pripojeni do hry
                    break;
                }
            }
            break;
        case 3:
            for(int i = 0; i < PlayerList3.size(); i++){
                if(nick == PlayerList3[i]->nick) {
                    if(PlayerList3[i]->connected == 0) return 2; //pripojen hrajici, nick neni k dispozici
                    if(PlayerList3[i]->connected == 1) return 1; //znovu pripojeni do hry
                    break;
                }
            }
            break;
        case 4:
            for(int i = 0; i < PlayerList4.size(); i++){
                if(nick == PlayerList4[i]->nick) {
                    if(PlayerList4[i]->connected == 0) return 2; //pripojen hrajici, nick neni k dispozici
                    if(PlayerList4[i]->connected == 1) return 1; //znovu pripojeni do hry
                    break;
                }
            }
            break;
    }

    return 0; // nick je volny
}

void GameManager::PlayerReconnect(string nick, int n)
{
    cout << "Player " << nick << " Reconnected!" << endl;

    Player *pl = GameManager::GetPlayer(nick, n);
    pl->connected = 0;

    for(int i = 0; i < GameList.size(); i++){
        if(GameList[i]->id == pl->GameID){
            GameList[i]->Reconnect(pl->id);
            break;
        }
    }
}

void GameManager::PlayerDisconnect(Player *pl)
{
    if(pl->GameID == -1){
        cout << "Player " << pl->nick << " destroyed!" << endl;
        pl->connected = 2;
        delete(pl);
        return;
    }

    pl->connected ++;

    for(int i = 0; i < GameList.size(); i++){
        if(GameList[i]->id == pl->GameID){
            GameList[i]->Disconnect(pl->id);
            if(GameList[i]->PlayerCount == GameList[i]->PlayerDisconnected){
                GameManager::DestroyGame(GameList[i]);
            }
            break;
        }
    }
}

void GameManager::DestroyGame(Game *g)
{
    cout << "Game " << g->id << " destroyed!" << endl;

    for(int i = 0; i < g->PlayerCount; i++){
        cout << "Player " << g->Players[i]->nick << " destroyed!" << endl;
        delete(g->Players[i]);
    }

    delete(g);
}

void GameManager::Start2Game()
{
    Game *game = new Game(game_count, PlayerList2.at(PlayerList2.size() - 2), PlayerList2.at(PlayerList2.size() - 1));
    GameList.push_back(game);
    game_count++;
}

void GameManager::Start3Game()
{
    Game *game = new Game(game_count, PlayerList3.at(PlayerList3.size() - 3), PlayerList3.at(PlayerList3.size() - 2), PlayerList3.at(PlayerList3.size() - 1));
    GameList.push_back(game);
    game_count++;
}

void GameManager::Start4Game()
{
    Game *game = new Game(game_count, PlayerList4.at(PlayerList4.size() - 4), PlayerList4.at(PlayerList4.size() - 3), PlayerList4.at(PlayerList4.size() - 2), PlayerList4.at(PlayerList4.size() - 1));
    GameList.push_back(game);
    game_count++;
}



void GameManager::Remove(Player *pl)
{
    for(int i = 0; i < PlayerList2.size(); i++){
        if(PlayerList2[i]->id == pl->id){
            PlayerList2.erase(PlayerList2.begin() + i);
            delete(pl);
            return;
        }
    }

    for(int i = 0; i < PlayerList3.size(); i++){
        if(PlayerList3[i]->id == pl->id){
            PlayerList3.erase(PlayerList3.begin() + i);
            delete(pl);
            return;
        }
    }

    for(int i = 0; i < PlayerList4.size(); i++){
        if(PlayerList4[i]->id == pl->id){
            PlayerList4.erase(PlayerList4.begin() + i);
            delete(pl);
            return;
        }
    }
}