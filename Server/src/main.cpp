#include <SFML/Network.hpp>
#include <iostream>

using namespace std;


int main()
{
    std::vector<sf::TcpSocket*> clients;

    sf::TcpListener listener;

    if (listener.listen(7777) != sf::Socket::Done)
    {
        printf("Error\n");
    }

    printf("Waiting for first connection...\n");

    while (clients.size() < 2)
    {
        sf::TcpSocket *socket = new sf::TcpSocket;
        if (listener.accept(*socket) != sf::Socket::Done)
        {
            printf("Error\n");
        }

        clients.push_back(socket);

        // OK, that one would be printed twice!!!
        printf("Waiting for second connection...\n");
    }
}