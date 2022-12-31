#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Spot {
public:
    int xPos = 0;
    int yPos = 0;
    string name;
    Texture spottexture;
    Sprite spotsprite;
};

sf::Packet& operator >>(sf::Packet& packet, Spot& p)
{
    return packet >> p.name >> p.xPos >> p.yPos;
}