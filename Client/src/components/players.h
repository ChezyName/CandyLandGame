#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Players
{
    string player1;
    Texture player1t;
    Sprite player1s;

    string player2;
    Texture player2t;
    Sprite player2s;

    string player3;
    Texture player3t;
    Sprite player3s;

    string player4;
    Texture player4t;
    Sprite player4s;

    string player5;
    Texture player5t;
    Sprite player5s;

    string player6;
    Texture player6t;
    Sprite player6s;
};

void getUsernamesForConsole(Players& p){
    printf("==============================\n");
    cout << p.player1 << endl;
    cout << p.player2 << endl;
    cout << p.player3 << endl;
    cout << p.player4 << endl;
    cout << p.player5 << endl;
    cout << p.player6 << endl;
    printf("==============================\n");
}

void getUsernamesFromPacket(Players& p,Packet packet){
    string packetName;
    packet >> packetName >> p.player1 >> p.player2 >> p.player3 >> p.player4 >> p.player5 >> p.player6;
}

void ShowPlayerNames(Players& p,RenderWindow* win,Font font,string myName){
    Text plrs;
    string playerText = "Players:\n";

    cout << "Loading Player Text" << endl;
    
    plrs.setFont(font);
    plrs.setCharacterSize(24);
    plrs.setString("Username:");
    plrs.setFillColor(Color::White);
    plrs.setStyle(Text::Bold);
    plrs.setPosition(Vector2f(15,15));

    if(p.player1 == myName) playerText += "ME > " + p.player1 + "\n"; else playerText += p.player1 + "\n";
    if(p.player2 == myName) playerText += "ME > " + p.player2 + "\n"; else playerText += p.player2 + "\n";
    if(p.player3 == myName) playerText += "ME > " + p.player3 + "\n"; else playerText += p.player3 + "\n";
    if(p.player4 == myName) playerText += "ME > " + p.player4 + "\n"; else playerText += p.player4 + "\n";
    if(p.player5 == myName) playerText += "ME > " + p.player5 + "\n"; else playerText += p.player5 + "\n";
    if(p.player6 == myName) playerText += "ME > " + p.player6 + "\n"; else playerText += p.player6 + "\n";

    cout << playerText << endl;

    plrs.setString(playerText);
    win->draw(plrs);
}

sf::Packet& operator <<(sf::Packet& packet, const Players& p)
{
    return packet << p.player1 << p.player2 << p.player3 << p.player4 << p.player5 << p.player6;
}

sf::Packet& operator >>(sf::Packet& packet, Players& p)
{
    return packet >> p.player1 >> p.player2 >> p.player3 >> p.player4 >> p.player5 >> p.player6;
}