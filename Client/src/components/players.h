#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Players
{
    string player1;
    string player2;
    string player3;
    string player4;
    string player5;
    string player6;
};

void getUsernamesForConsole(Players& p){
    printf("==============================");
    cout << p.player1 << endl;
    cout << p.player2 << endl;
    cout << p.player3 << endl;
    cout << p.player4 << endl;
    cout << p.player5 << endl;
    cout << p.player6 << endl;
    printf("==============================");
}

sf::Packet& operator <<(sf::Packet& packet, const Players& p)
{
    return packet << p.player1 << p.player2 << p.player3 << p.player4 << p.player5 << p.player6;
}

sf::Packet& operator >>(sf::Packet& packet, Players& p)
{
    return packet >> p.player1 >> p.player2 >> p.player3 >> p.player4 >> p.player5 >> p.player6;
}