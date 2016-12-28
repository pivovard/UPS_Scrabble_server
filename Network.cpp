//
// Created by pivov on 23-Dec-16.
//

#include "Network.h"
#include "App.h"


int Network::socket_desc , Network::client_sock , Network::c;
struct sockaddr_in Network::server , Network::client;

//constructor
void Network::Start()
{
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created.");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("Bind failed. Error");
        return;
    }
    puts("Bind done.");

    //Listen
    if( listen(socket_desc , 3) < 0 )
    {
        //print the error message
        perror("Listen failed. Error");
        return;
    }

    //Accept and incoming connection
    puts("Server ready!");
}

//public methods

void Network::Listen()
{
    c = sizeof(struct sockaddr_in);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");

        char *nick = (char *)malloc(64);
        recv(client_sock, nick, 64, 0);

        char *ip = inet_ntoa(client.sin_addr);

        Player *pl = App::PlayerConnect(nick, ip, client_sock);

        std::thread thread_pl(Network::PlayerListen, pl);
        thread_pl.detach();
    }

    if (client_sock < 0)
    {
        perror("Accept failed.");
    }
}

void Network::Exit()
{
    cout << "Socket closed" << endl;
    close(socket_desc);
}


void Network::PlayerListen(Player *pl)
{
    int size;

    cout << pl->nick << endl << pl->ip << endl;
    while( (size = recv(pl->socket , pl->message_in , msg_length , 0)) > 0){
        //react on message
        write(pl->socket , pl->message_in , msg_length);
    }

    if(size == 0)
    {
        puts("Client disconnected");
        //fflush(stdout);
    }
    else if(size == -1)
    {
        puts("Client disconnected");
        perror("recv failed");
    }
}







//private methods

void Network::SendMessage(int socket, string *message)
{
    write(socket , message , (*message).length());
}

void Network::RecvMessage(int socket, string *message)
{
    recv(socket, message, 1024, 0);
}