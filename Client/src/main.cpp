#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1280, 720), "Candyland");

    TcpSocket socket;
    Socket::Status status = socket.connect("localhost", 7777);

    Packet Username;
    Username << "ChezyName";
    socket.send(Username);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}