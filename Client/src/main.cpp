#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Candyland");

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", 7777);

    while (window.isOpen())
    {
        sf::Event event;
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