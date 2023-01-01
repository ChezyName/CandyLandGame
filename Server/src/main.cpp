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

void createSpotsForAll(){
    cout << "Creating Map, Please Wait..." << endl;
    vector<BasicSpot*> spots = createSpots();
    Packet p;
    p << "MAP";
    p << spots.size();

    for(BasicSpot* s : spots){
        p << s;
    }

    cout << "Map was loaded on size " << spots.size() << endl;

    sendPacketToAll(players,p);
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
    

    if(playerCount == 0){
        players.player1 = newClient;
        players.player1name = UsernamePacket;
    }
    else if(playerCount == 1){
        players.player2 = newClient;
        players.player2name = UsernamePacket;
    }
    else if(playerCount == 2){
        players.player3 = newClient;
        players.player3name = UsernamePacket;
    }
    else if(playerCount == 3){
        players.player4 = newClient;
        players.player4name = UsernamePacket;
    }
    else if(playerCount == 4){
        players.player5 = newClient;
        players.player5name = UsernamePacket;
    }
    else if(playerCount == 5){
        players.player6 = newClient;
        players.player6name = UsernamePacket;
    }

    playerCount++;

    Packet clientCount;
    string C = "Players";
    clientCount << C.c_str();

    //getUsernamesForPacket(players,clientCount);
    clientCount << players;
    sendPacketToAll(players,clientCount);

    if(playerCount >= 6) {
        cout << "Game is ready to start, player count is 6...\nStarting game." << endl;
        gameStarted = true;
        Packet p;
        p << "Start";
        sendPacketToAll(players,p);
        createSpotsForAll();
    }
}

void runCommands(){
    while (true)
    {
        string input;
        cin >> input;

        if(input == "getplayers" || input == "players"){
            //get players command
            printf("\nCurrent Players In Server:\n");
            getUsernamesForConsole(players);
            printf("===========================\n");
        }
        else if(input == "start"){
            if(players.player1 != nullptr){
                gameStarted = true;
                Packet p;
                p << "Start";
                sendPacketToAll(players,p);
                createSpotsForAll();
            }
        }
        else if(input == "clear"){
            system("cls");
        }
        else {
            printf("Command Not Found.\n");
        }
    }
    
}