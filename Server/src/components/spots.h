#include <iostream>
#include <vector>

using namespace std;

struct BasicSpot
{
    BasicSpot(int x, int y,string n) : xPos(x), yPos(y), Name(n) {}
    virtual ~BasicSpot() = default;

    virtual void onPlayerStandOn(class Player* p) = 0; // pure virtual (must be defined by deriving classes)
    
    string Name = "BASIC";

    int xPos;
    int yPos;
};

struct StartingSpot : public BasicSpot
{
    StartingSpot(int x,int y) : BasicSpot(x,y,"START") {}

    virtual void onPlayerStandOn(class Player* p) override {
        cout << "STARTING SPOT" << endl;
    }
};

struct EmptySpot : public BasicSpot
{
    EmptySpot(int x,int y) : BasicSpot(x,y,"EMPTY") {}

    virtual void onPlayerStandOn(class Player* p) override {
        cout << "BASIC SPOT" << endl;
    }
};

bool getRandomBool(){
    int randomval = rand() % 2;
    return randomval == 1;
}


vector<BasicSpot*> createSpots(){
    int spaceBetweenX = 32;
    int spaceBetweenY = 32;

    int MaxPlacementX = 1280;
    int MaxPlacementY = 720;

    vector<BasicSpot*> Spots;

    int lastX = 32;
    int lastY = 32;

    StartingSpot* FirstSpot = new StartingSpot(32,32);

    Spots.push_back(FirstSpot);

    bool keepPlacing = true;
    for(int i = 0; i < 15; i++)
    {
        int nextX = lastX + getRandomBool() ? -spaceBetweenX : spaceBetweenX;
        int nextY = lastY + getRandomBool() ? -spaceBetweenY : spaceBetweenY;

        if(nextX < 32) nextX = lastX + (rand() % spaceBetweenX);
        if(nextX > MaxPlacementX) keepPlacing = false;
        if(nextY < 32) nextY = lastY + (rand() % spaceBetweenY);
        if(nextY > MaxPlacementY) keepPlacing = false;
        
        EmptySpot* spot = new EmptySpot(nextX,nextY);
        Spots.push_back(spot);

        lastX = nextX;
        lastY = nextY;
    }
    return Spots;
}

sf::Packet& operator <<(sf::Packet& packet, const BasicSpot* p)
{
    return packet << p->Name << p->xPos << p->yPos;
}

sf::Packet& operator >>(sf::Packet& packet, EmptySpot* p)
{
    return packet >> p->Name >> p->xPos >> p->yPos;
}