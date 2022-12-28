#include <SFML/Network.hpp>
#include <iostream>
#include "components/player.h"

using namespace std;
using namespace sf;

int main()
{
    std::vector<Player*> Clients;

    TcpListener listener;

    if (listener.listen(7777) != Socket::Done)
    {
        printf("Error\n");
    }

    cout << "Server started on port 7777\n" << endl;

    while (true)
    {
        //Gameplay Loop
        TcpSocket *socket = new TcpSocket;
        if (listener.accept(*socket) != Socket::Done)
        {
            printf("Error\n");
        }

        Packet Username;
        socket->receive(Username);
        std::string UsernamePacket;

        if (Username.getDataSize() > 0)
        {
            Username >> UsernamePacket;
            Username.clear();
        }

        cout << UsernamePacket + " joined from " + socket->getRemoteAddress().toString() << endl;

        Player* newClient = new Player(socket,UsernamePacket);
        Clients.push_back(newClient);
    }
}