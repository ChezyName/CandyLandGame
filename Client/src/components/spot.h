#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Spot {
public:
    Spot(int x,int y,string n) : xPos(x), yPos(y), name(n) {};
    int xPos = 0;
    int yPos = 0;
    string name;
    Texture spottexture;
    Sprite spotsprite;
    void createSprite(){
        spottexture.loadFromFile("Assets/Spots/"+name+".png");
        spotsprite.setTexture(spottexture);
        spotsprite.setOrigin(spotsprite.getLocalBounds().width/2, spotsprite.getLocalBounds().height/2);
        spotsprite.setPosition(xPos,720-yPos);
        cout << "Created Spot: " << name << " @ " << xPos << "," << yPos << endl;
    }
};

struct prespot {
public:
    string n;
    int x;
    int y;
};

sf::Packet& operator >>(sf::Packet& packet, prespot& p)
{
    return packet >> p.n >> p.x >> p.y;
}