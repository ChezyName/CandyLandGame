#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "components/spots.h"
#include "components/players.h"

Players players;
int playerCount = 0;

TcpListener listener;
bool gameStarted = false;

void runCommands();
void letJoin();
void gameplayLoop();
void sendCPlayer();