#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "components/player.h"

std::vector<Player*> Clients;

void runCommands();