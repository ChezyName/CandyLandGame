#include "main.h"

using namespace std;
using namespace sf;

int main()
{
    std::thread commandThread(runCommands);

    if (listener.listen(7777) != Socket::Done)
    {
        return 1;
    }
    listener.setBlocking(false);
    cout << "Server started on port 7777\n" << endl;

    while (true)
    {
        //Gameplay Loop
        if(gameStarted == false){
            letJoin();
        }
    }

    return 0;
}

void letJoin(){
    TcpSocket *socket = new TcpSocket;
    if (listener.accept(*socket) != Socket::Done)
    {
        return;
    }

    Packet Username;
    socket->receive(Username);
    std::string UsernamePacket;

    if (Username.getDataSize() > 0)
    {
        Username >> UsernamePacket;
        Username.clear();
    }

    cout << UsernamePacket + " joined from " + socket->getRemoteAddress().toString() << endl;

    Player* newClient = new Player(socket,UsernamePacket);
    
    switch (playerCount)
    {
        case 0:
            players.player1 = newClient;
            break;
        case 1:
            players.player2 = newClient;
            break;
        case 2:
            players.player3 = newClient;
            break;
        case 3:
            players.player4 = newClient;
            break;
        case 4:
            players.player5 = newClient;
            break;
        case 5:
            players.player6 = newClient;
            break;
        default:
            break;
    }

    playerCount++;

    //send player count to all clients
    int pSize;
    string Name;

    Packet clientCount;
    string C = "Players";
    clientCount << C.c_str();

    clientCount << players;
    sendPacketToAll(players,clientCount);

    if(playerCount >= 5) {
        cout << "Game is ready to start, player count is 6...\nStarting game." << endl;
        gameStarted = true;
    }
}

void runCommands(){
    while (true)
    {
        string input;
        cin >> input;

        if(input == "getplayers" || input == "players"){
            //get players command
            printf("Current Players In Server:\n");
            getUsernamesForConsole(players);
            printf("===========================\n");
        }
        else if(input == "clear"){
            system("cls");
        }
        else {
            printf("Command Not Found.\n");
        }
    }
    
}