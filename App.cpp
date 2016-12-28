//
// Created by pivov on 25-Dec-16.
//

#include "App.h"

int App::game_count = 0;
int App::player_count = 0;
list<Game> App::GameList;
list<Player> App::PlayerList;

App::App()
{
    std::thread thread_command(App::Command);

    Network::Start();
    //std::thread thread_listen = new std::thread(Network::Listen);
    std::thread thread_listen(Network::Listen);
    thread_listen.detach();


    Game *game = new Game(game_count);
    GameList.push_back(*game);
    game_count++;
    cout << "Game " << game_count << " created." << endl;

    thread_command.join();
}

Player* App::PlayerConnect(char *nick, char *ip, int socket)
{
    Player *pl = new Player(nick, ip, socket);
    PlayerList.push_back(*pl);
    player_count++;

    return pl;
}

void App::Command()
{
    while(true)
    {
        string out;
        cin >> out;
        if(out.compare("exit") == 0)
        {
            cout << "Server shutting down!" << endl;
            Network::Exit();
            break;
        }
    }
}




