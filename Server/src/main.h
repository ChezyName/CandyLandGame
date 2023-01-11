#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <time.h>

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
void playerWinGame(Player* p);
string getRandomCard(){
    int random = rand() % 100 + 1;
    if(random <= 25) return "JUMP";
    if(random <= 50) return "SKIP";
    if(random <= 75) return "REVERSE";
    if(random <= 95) return "SWAP";
    else return "RESET";
}