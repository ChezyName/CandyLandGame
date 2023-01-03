#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "components/math.h"
#include "components/spots.h"
#include "components/players.h"

Players players;
int playerCount = 0;

TcpListener listener;
bool gameStarted = false;

vector<BasicSpot*> spots;

void runCommands();
void letJoin();
void gameplayLoop();
void sendCPlayer();
void UpdatePlayerPositions();
void setAllPlayersPos(int x, int y);
void getPlayerData(Player* p);
int setNextPlayingPlayer();
void playerTouchSpace(BasicSpot* s,Player* p);
string getRandomCard(){
    int random = rand() % 2;
    if(random == 1) return "JUMP";
    else return "SWAP";
}