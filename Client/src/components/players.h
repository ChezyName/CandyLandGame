#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace sf;

Font cf;

struct Players
{
    string ME;
    string personTurn = "";

    string player1;
    Texture player1t;
    Sprite player1s;
    Sprite player1c;
    Text player1text;
    Vector2f player1p;

    string player2;
    Texture player2t;
    Sprite player2s;
    Sprite player2c;
    Text player2text;
    Vector2f player2p;

    string player3;
    Texture player3t;
    Sprite player3s;
    Sprite player3c;
    Text player3text;
    Vector2f player3p;

    string player4;
    Texture player4t;
    Sprite player4s;
    Sprite player4c;
    Text player4text;
    Vector2f player4p;

    string player5;
    Texture player5t;
    Sprite player5s;
    Sprite player5c;
    Text player5text;
    Vector2f player5p;

    string player6;
    Texture player6t;
    Sprite player6s;
    Sprite player6c;
    Text player6text;
    Vector2f player6p;
};

bool isHoveringSprite(Sprite s,Vector2i Mouse){
    int maxX = ((s.getGlobalBounds().width/2) + s.getPosition().x);
    int minX = (s.getPosition().x-(s.getGlobalBounds().width/2));
    int maxY = ((s.getGlobalBounds().height/2) + s.getPosition().y);
    int minY = (s.getPosition().y-(s.getGlobalBounds().height/2));

    return (maxX >= Mouse.x && minX <= Mouse.x && maxY >= Mouse.y && minY <= Mouse.y);
}

void glowOnHover(bool Hover,Sprite& s){
    if(Hover){
        s.setColor(Color(120,120,120,255));
    }
    else{
        s.setColor(Color::White);
    }
}

int getPlayerClicked(Players& p,Vector2i Mouse){
    if(isHoveringSprite(p.player1s,Mouse)) return 1;
    if(isHoveringSprite(p.player2s,Mouse)) return 2;
    if(isHoveringSprite(p.player3s,Mouse)) return 3;
    if(isHoveringSprite(p.player4s,Mouse)) return 4;
    if(isHoveringSprite(p.player5s,Mouse)) return 5;
    if(isHoveringSprite(p.player6s,Mouse)) return 6;
    return -1;
}

int getMyNumber(Players& p){
    if(p.ME == p.player1) return 1;
    if(p.ME == p.player2) return 2;
    if(p.ME == p.player3) return 3;
    if(p.ME == p.player4) return 4;
    if(p.ME == p.player5) return 5;
    if(p.ME == p.player6) return 6;
    return -1;
}

void glowSpritesOnHover(Players& p,bool canGlow,Vector2i Mouse){
    glowOnHover(canGlow && isHoveringSprite(p.player1s,Mouse),p.player1s);
    glowOnHover(canGlow && isHoveringSprite(p.player2s,Mouse),p.player2s);
    glowOnHover(canGlow && isHoveringSprite(p.player3s,Mouse),p.player3s);
    glowOnHover(canGlow && isHoveringSprite(p.player4s,Mouse),p.player4s);
    glowOnHover(canGlow && isHoveringSprite(p.player5s,Mouse),p.player5s);
    glowOnHover(canGlow && isHoveringSprite(p.player6s,Mouse),p.player6s);
}

void createPlayerTextObjs(Players& p){
    cf.loadFromFile("Arial.ttf");
    int textSize = 28;
    Color textColor = Color::White;

    p.player1text.setFont(cf);
    p.player1text.setCharacterSize(textSize);
    p.player1text.setFillColor(textColor);
    p.player1text.setStyle(Text::Bold);
    p.player1text.setString(p.player1 == p.ME ? "[YOU]" : "" + p.player1);


    p.player2text.setFont(cf);
    p.player2text.setCharacterSize(textSize);
    p.player2text.setFillColor(textColor);
    p.player2text.setStyle(Text::Bold);
    p.player2text.setString(p.player2 == p.ME ? "[YOU]" : "" + p.player2);

    p.player3text.setFont(cf);
    p.player3text.setCharacterSize(textSize);
    p.player3text.setFillColor(textColor);
    p.player3text.setStyle(Text::Bold);
    p.player3text.setString(p.player3 == p.ME ? "[YOU]" : "" + p.player3);

    p.player4text.setFont(cf);
    p.player4text.setCharacterSize(textSize);
    p.player4text.setFillColor(textColor);
    p.player4text.setStyle(Text::Bold);
    p.player4text.setString(p.player4 == p.ME ? "[YOU]" : "" + p.player4);

    p.player5text.setFont(cf);
    p.player5text.setCharacterSize(textSize);
    p.player5text.setFillColor(textColor);
    p.player5text.setStyle(Text::Bold);
    p.player5text.setString(p.player5 == p.ME ? "[YOU]" : "" + p.player5);

    p.player6text.setFont(cf);
    p.player6text.setCharacterSize(textSize);
    p.player6text.setFillColor(textColor);
    p.player6text.setStyle(Text::Bold);
    p.player6text.setString(p.player6 == p.ME ? "[YOU]" : "" + p.player6);
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

void UpdateSelectedPlayer(Players& p){
    if(p.player1 == p.personTurn) p.player1text.setString((p.player1 == p.ME ? "ME" : p.player1) + " <");
    else p.player1text.setString(p.player1 == p.ME ? "ME" : p.player1);

    if(p.player2 == p.personTurn) p.player2text.setString((p.player2 == p.ME ? "ME" : p.player2) + " <");
    else p.player2text.setString(p.player2 == p.ME ? "ME" : p.player2);

    if(p.player3 == p.personTurn) p.player3text.setString((p.player3 == p.ME ? "ME" : p.player3) + " <");
    else p.player3text.setString(p.player3 == p.ME ? "ME" : p.player3);

    if(p.player4 == p.personTurn) p.player4text.setString((p.player4 == p.ME ? "ME" : p.player4) + " <");
    else p.player4text.setString(p.player4 == p.ME ? "ME" : p.player4);

    if(p.player5 == p.personTurn) p.player5text.setString((p.player5 == p.ME ? "ME" : p.player5) + " <");
    else p.player5text.setString(p.player5 == p.ME ? "ME" : p.player5);

    if(p.player6 == p.personTurn) p.player6text.setString((p.player6 == p.ME ? "ME" : p.player6) + " <");
    else p.player6text.setString(p.player6 == p.ME ? "ME" : p.player6);
}

void DisplayPlayersText(Players& p,RenderWindow* win){
    //cout << "Drawing Player Text @ " << p.player1text.getPosition().x << "," << p.player1text.getPosition().y << endl;
    UpdateSelectedPlayer(p);

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

    if(p.player1 == myName) playerText += "YOU > " + p.player1 + "\n"; else playerText += p.player1 + "\n";
    if(p.player2 == myName) playerText += "YOU > " + p.player2 + "\n"; else playerText += p.player2 + "\n";
    if(p.player3 == myName) playerText += "YOU > " + p.player3 + "\n"; else playerText += p.player3 + "\n";
    if(p.player4 == myName) playerText += "YOU > " + p.player4 + "\n"; else playerText += p.player4 + "\n";
    if(p.player5 == myName) playerText += "YOU > " + p.player5 + "\n"; else playerText += p.player5 + "\n";
    if(p.player6 == myName) playerText += "YOU > " + p.player6 + "\n"; else playerText += p.player6 + "\n";

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
    packet >> p.player1 >> p.player2 >> p.player3 >> p.player4 >> p.player5 >> p.player6;
    return packet;
}

void getPlayerPositions(sf::Packet& packet, Players& p){
    int x = 0;
    int y = 0;
    packet >> x >> y;
    x += -35;
    y += -15;
    p.player1s.setPosition(x,720-y);
    p.player1p.x = x;
    p.player1p.y = y;

    packet >> x >> y;
    x += 0;
    y += -15;
    p.player2s.setPosition(x,720-y);
    p.player2p.x = x;
    p.player2p.y = y;

    packet >> x >> y;
    x += 35;
    y += -15;
    p.player3s.setPosition(x,720-y);
    p.player3p.x = x;
    p.player3p.y = y;

    packet >> x >> y;
    x += -35;
    y += 15;
    p.player4s.setPosition(x,720-y);
    p.player4p.x = x;
    p.player4p.y = y;

    packet >> x >> y;
    x += 0;
    y += 15;
    p.player5s.setPosition(x,720-y);
    p.player5p.x = x;
    p.player5p.y = y;

    packet >> x >> y;
    x += 35;
    y += 15;
    p.player6s.setPosition(x,720-y);
    p.player6p.x = x;
    p.player6p.y = y;
}

void getPlayerPositionsLerp(sf::Packet& packet, Players& p){
    int x = 0;
    int y = 0;
    packet >> x >> y;
    x += -35;
    y += -15;
    p.player1p.x = x;
    p.player1p.y = y;

    packet >> x >> y;
    x += 0;
    y += -15;
    p.player2p.x = x;
    p.player2p.y = y;

    packet >> x >> y;
    x += 35;
    y += -15;
    p.player3p.x = x;
    p.player3p.y = y;

    packet >> x >> y;
    x += -35;
    y += 15;
    p.player4p.x = x;
    p.player4p.y = y;

    packet >> x >> y;
    x += 0;
    y += 15;
    p.player5p.x = x;
    p.player5p.y = y;

    packet >> x >> y;
    x += 35;
    y += 15;
    p.player6p.x = x;
    p.player6p.y = y;
}

float start;
void onSecondstart(float f){
    start = f;
}

float clamp(float x, float min, float max){
    if(x >= max) return max;
    if(x <= min) return min;
    return x;
}

float lerp(float a, float b, float t)
{
    t = clamp(t,0,1);
    return t * (b-a) + a;
}

void lerpPlayerPositions(Players& p,Clock c){
    float seconds = c.getElapsedTime().asSeconds() - start;
    float time = seconds/5;

    p.player1s.setPosition(lerp(p.player1s.getPosition().x,p.player1p.x,time),lerp(p.player1s.getPosition().y,720-p.player1p.y,time));
    p.player2s.setPosition(lerp(p.player2s.getPosition().x,p.player2p.x,time),lerp(p.player2s.getPosition().y,720-p.player2p.y,time));
    p.player3s.setPosition(lerp(p.player3s.getPosition().x,p.player3p.x,time),lerp(p.player3s.getPosition().y,720-p.player3p.y,time));
    p.player4s.setPosition(lerp(p.player4s.getPosition().x,p.player4p.x,time),lerp(p.player4s.getPosition().y,720-p.player4p.y,time));
    p.player5s.setPosition(lerp(p.player5s.getPosition().x,p.player5p.x,time),lerp(p.player5s.getPosition().y,720-p.player5p.y,time));
    p.player6s.setPosition(lerp(p.player6s.getPosition().x,p.player6p.x,time),lerp(p.player6s.getPosition().y,720-p.player6p.y,time));
}