//
// Created by pivov on 01-Jan-17.
//

#include "GameManager.h"

int GameManager::game_count = 0;
static int player_count[3] = {0, 0, 0};
int GameManager::player_count2 = 0;
int GameManager::player_count3 = 0;
int GameManager::player_count4 = 0;

vector<Game*> GameManager::GameList;
static vector<Player*> PlayerList[3] = {vector<Player*>(), vector<Player*>(), vector<Player*>()};
vector<Player*> GameManager::PlayerList2;
vector<Player*> GameManager::PlayerList3;
vector<Player*> GameManager::PlayerList4;


Player* GameManager::PlayerConnect(string nick, char *ip, int socket, int n)
{
    Player *pl;
    /*switch(n)
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
    }*/

    pl = new Player(nick, ip, socket, PlayerList[n-2].size());
    PlayerList[n-2].push_back(pl);
    player_count[n-2]++;

    //if((PlayerList[n-2].size() % 2) == 0){
    if((player_count[n-2] % n) == 0){
        GameManager::StartGame(n);
    }

    cout << PlayerList[n-2].size() << endl;
    cout << PlayerList[n-1].size() << endl;
    cout << PlayerList[n].size() << endl;

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
    /*switch(n)
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
    }*/

    for(int i = 0; i < PlayerList[n-2].size(); i++){
        if(nick == PlayerList[n-2][i]->nick && PlayerList[n-2][i]->connected < 2){
            return PlayerList[n-2][i];
        }
    }

    return nullptr;
}

int GameManager::CheckNick(string nick, int n)
{
    /*switch(n)
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
    }*/

    for(int i = 0; i < PlayerList[n-2].size(); i++){
        if(nick == PlayerList[n-2][i]->nick) {
            if(PlayerList[n-2][i]->connected == 0) return 2; //pripojen hrajici, nick neni k dispozici
            if(PlayerList[n-2][i]->connected == 1) return 1; //znovu pripojeni do hry
        }
    }

    return 0 ; // nick je volny
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
    pl->connected ++;

    if(pl->GameID == -1){
        cout << "Player " << pl->nick << " destroyed!" << endl;

        if(pl->connected == 1) player_count[pl->n-2]--;

        pl->connected = 2;
        delete(pl);
        return;
    }

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

void GameManager::StartGame(int n)
{
    Game *game;

    switch (n){
        case 2: game = new Game(game_count, PlayerList[n-2].at(PlayerList[n-2].size() - 2), PlayerList[n-2].at(PlayerList[n-2].size() - 1)); break;
        case 3: game = new Game(game_count, PlayerList[n-2].at(PlayerList[n-2].size() - 3), PlayerList[n-2].at(PlayerList[n-2].size() - 2), PlayerList[n-2].at(PlayerList[n-2].size() - 1)); break;
        case 4: game = new Game(game_count, PlayerList[n-2].at(PlayerList[n-2].size() - 4), PlayerList[n-2].at(PlayerList[n-2].size() - 3), PlayerList[n-2].at(PlayerList[n-2].size() - 2), PlayerList[n-2].at(PlayerList[n-2].size() - 1)); break;
    }

    GameList.push_back(game);
    game_count++;
}



void GameManager::Remove(Player *pl)
{
    int n = pl->n;

    for(int i = 0; i < PlayerList[n-2].size(); i++){
        if(PlayerList[n-2][i]->id == pl->id){
            PlayerList[n-2].erase(PlayerList[n-2].begin() + i);
            delete(pl);
            return;
        }
    }
}