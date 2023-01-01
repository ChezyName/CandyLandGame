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


struct FinalSpot : public BasicSpot
{
    FinalSpot(int x,int y) : BasicSpot(x,y,"FINAL") {}

    virtual void onPlayerStandOn(class Player* p) override {
        cout << "BASIC SPOT" << endl;
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
};

vector<BasicSpot*> createSpots(){
    vector<BasicSpot*> Spots;

    int x = 64;
    int y = 64;

    StartingSpot* FirstSpot = new StartingSpot(64,64);
    Spots.push_back(FirstSpot);

    x += 16;
    y += 75;
    BasicSpot* S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 8;
    y += 75;
    S = new EmptySpot(x,y);
    Spots.push_back(S);
    
    x += 16;
    y += 75;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 24;
    y += 80;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 32;
    y += 68;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 80;
    y += 40;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 75;
    y += 15;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 75;
    y += 15;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 75;
    y += -30;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 65;
    y += -65;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 55;
    y += -75;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += -45;
    y += -85;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += -80;
    y += -24;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += -128;
    y += -24;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += -25;
    y += -85;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 45;
    y += -85;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 80;
    y += 12;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 80;
    y += 15;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 80;
    y += 18;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 60;
    y += 24;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    x += 70;
    y += 15;
    S = new EmptySpot(x,y);
    Spots.push_back(S);

    return Spots;
};

vector<BasicSpot*> createSpotsRand(){
    int spaceBetweenX = 128;
    int spaceBetweenY = 128;

    int MaxPlacementX = 1280;
    int MaxPlacementY = 720;

    vector<BasicSpot*> Spots;

    int lastX = 64;
    int lastY = 64;

    StartingSpot* FirstSpot = new StartingSpot(64,64);

    Spots.push_back(FirstSpot);

    bool keepPlacing = true;
    for(int i = 0; i < 32; i++)
    {
        int nextX = lastX + (rand() % spaceBetweenX);
        int nextY = lastY + (rand() % spaceBetweenY);

        if(lastX > 1100){
            //X Majority
            nextX = lastX;
        }
        if(lastY > 650){
            //Y Majority
            nextY = lastY;
        }
        
        if(lastX == nextX || lastY == nextY){
            //Both X & Y is 2 Big
            keepPlacing = false;
            FinalSpot* spot = new FinalSpot(nextX,nextY);
            Spots.push_back(spot);
            break;
        }
        else{
            int padX = nextX - lastX;
            int padY = nextY - lastY;
            int fPadX = 64 - padX;
            int fpadY = 64-padY;

            if((padX + padY) > (spaceBetweenX*1.5)){
                if(fPadX > 0) nextX += fPadX;
                if(fPadX > 0) nextY += fpadY;
            }

            EmptySpot* spot = new EmptySpot(nextX,nextY);
            Spots.push_back(spot);
        }

        lastX = nextX;
        lastY = nextY;
    }
    return Spots;
};

sf::Packet& operator <<(sf::Packet& packet, const BasicSpot* p)
{
    return packet << p->Name << p->xPos << p->yPos;
}

sf::Packet& operator >>(sf::Packet& packet, EmptySpot* p)
{
    return packet >> p->Name >> p->xPos >> p->yPos;
}