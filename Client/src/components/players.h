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
    Sprite player1c;

    string player2;
    Texture player2t;
    Sprite player2s;
    Sprite player2c;

    string player3;
    Texture player3t;
    Sprite player3s;
    Sprite player3c;

    string player4;
    Texture player4t;
    Sprite player4s;
    Sprite player4c;

    string player5;
    Texture player5t;
    Sprite player5s;
    Sprite player5c;

    string player6;
    Texture player6t;
    Sprite player6s;
    Sprite player6c;
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

void DisplayPlayerIcons(Players& p,RenderWindow* win){
    if(!p.player1.empty()) win->draw(p.player1c);
    if(!p.player2.empty()) win->draw(p.player2c);
    if(!p.player3.empty()) win->draw(p.player3c);
    if(!p.player4.empty()) win->draw(p.player4c);
    if(!p.player5.empty()) win->draw(p.player5c);
    if(!p.player6.empty()) win->draw(p.player6c);
}

void DisplayPlayers(Players& p,RenderWindow* win){
    if(!p.player1.empty()) win->draw(p.player1s);
    if(!p.player2.empty()) win->draw(p.player2s);
    if(!p.player3.empty()) win->draw(p.player3s);
    if(!p.player4.empty()) win->draw(p.player4s);
    if(!p.player5.empty()) win->draw(p.player5s);
    if(!p.player6.empty()) win->draw(p.player6s);
}

int GetPlayerCount(Players& p){
    if(!p.player6.empty()) return 6;
    if(!p.player5.empty()) return 5;
    if(!p.player4.empty()) return 4;
    if(!p.player3.empty()) return 3;
    if(!p.player2.empty()) return 2;
    if(!p.player1.empty()) return 1;
    return 0;
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