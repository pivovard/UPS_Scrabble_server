//
// Created by pivov on 23-Dec-16.
//

#include "Network.h"


int Network::socket_desc , Network::client_sock , Network::c;
struct sockaddr_in Network::server , Network::client;

void Network::Start()
{
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
        return;
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


void Network::Listen()
{
    int size;
    char *nick_in = new char[64];

    c = sizeof(struct sockaddr_in);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted.");

        size = recv(client_sock, nick_in, 64, 0);
        char *nick = CropChar(nick_in, size);

        char *ip = inet_ntoa(client.sin_addr);

        Player *pl = GameManager::PlayerConnect(nick, ip, client_sock);

        std::thread thread_pl(Network::PlayerListen, pl);
        thread_pl.detach();
    }

    if (client_sock < 0)
    {
        perror("Accept failed.");
    }
}

void Network::PlayerListen(Player *pl)
{
    int size;
    string msg;

    cout << "Listenning player: " << pl->nick << "   " << pl->ip << endl;
    while( (size = recv(pl->socket , pl->message_in , msg_length , 0)) > 0){
        //react on message
        //cout << "Recv from " << pl->nick << ": " << pl->message_in << endl;

        msg = CropMsg(pl->message_in, size);
        cout << "Recv from " << pl->nick << ": " << msg << endl;

        pl->SendToPlayer(msg);
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

void Network::Exit()
{
    cout << "Socket closed." << endl;
    close(socket_desc);
}




string Network::CropMsg(char *in, int size)
{
    string msg = "";

    for(int i = 0; i < size; i++){
        msg += in[i];
    }

    return msg;
}

//nefunguje, je treba spravit
char* Network::CropChar(char *in, int size)
{
    char *out = new char[size];

    for(int i = 0; i < size; i++){
        if(in[i] == '\n') break;
        out[i] = in[i];
    }

    return out;
}





void Network::SendMessage(int socket, string *message)
{
    write(socket , message , (*message).length());
}

void Network::RecvMessage(int socket, string *message)
{
    recv(socket, message, 1024, 0);
}