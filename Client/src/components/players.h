#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Font cf;

struct Players
{
    string player1;
    Texture player1t;
    Sprite player1s;
    Sprite player1c;
    Text player1text;

    string player2;
    Texture player2t;
    Sprite player2s;
    Sprite player2c;
    Text player2text;

    string player3;
    Texture player3t;
    Sprite player3s;
    Sprite player3c;
    Text player3text;

    string player4;
    Texture player4t;
    Sprite player4s;
    Sprite player4c;
    Text player4text;

    string player5;
    Texture player5t;
    Sprite player5s;
    Sprite player5c;
    Text player5text;

    string player6;
    Texture player6t;
    Sprite player6s;
    Sprite player6c;
    Text player6text;
};

void createPlayerTextObjs(Players& p){
    cf.loadFromFile("Arial.ttf");
    
    p.player1text.setFont(cf);
    p.player1text.setCharacterSize(20);
    p.player1text.setFillColor(Color::White);
    p.player1text.setStyle(Text::Bold);
    p.player1text.setOrigin(0, p.player1text.getLocalBounds().height/2);
    p.player1text.setString(p.player1);


    p.player2text.setFont(cf);
    p.player2text.setCharacterSize(20);
    p.player2text.setFillColor(Color::White);
    p.player2text.setStyle(Text::Bold);
    p.player2text.setOrigin(0, p.player2text.getLocalBounds().height/2);
    p.player2text.setString(p.player2);

    p.player3text.setFont(cf);
    p.player3text.setCharacterSize(20);
    p.player3text.setFillColor(Color::White);
    p.player3text.setStyle(Text::Bold);
    p.player3text.setOrigin(0, p.player3text.getLocalBounds().height/2);
    p.player3text.setString(p.player3);

    p.player4text.setFont(cf);
    p.player4text.setCharacterSize(20);
    p.player4text.setFillColor(Color::White);
    p.player4text.setStyle(Text::Bold);
    p.player4text.setOrigin(0, p.player4text.getLocalBounds().height/2);
    p.player4text.setString(p.player4);

    p.player5text.setFont(cf);
    p.player5text.setCharacterSize(20);
    p.player5text.setFillColor(Color::White);
    p.player5text.setStyle(Text::Bold);
    p.player5text.setOrigin(0, p.player5text.getLocalBounds().height/2);
    p.player5text.setString(p.player5);

    p.player6text.setFont(cf);
    p.player6text.setCharacterSize(20);
    p.player6text.setFillColor(Color::White);
    p.player6text.setStyle(Text::Bold);
    p.player6text.setOrigin(0, p.player6text.getLocalBounds().height/2);
    p.player6text.setString(p.player6);
}

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

void DisplayPlayersText(Players& p,RenderWindow* win){
    //cout << "Drawing Player Text @ " << p.player1text.getPosition().x << "," << p.player1text.getPosition().y << endl;

    if(!p.player1.empty()) win->draw(p.player1text);
    if(!p.player2.empty()) win->draw(p.player2text);
    if(!p.player3.empty()) win->draw(p.player3text);
    if(!p.player4.empty()) win->draw(p.player4text);
    if(!p.player5.empty()) win->draw(p.player5text);
    if(!p.player6.empty()) win->draw(p.player6text);
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