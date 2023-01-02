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
        else {
            gameplayLoop();
        }
    }

    return 0;
}

int cPlayer = 1;
void gameplayLoop(){
    if(cPlayer == 1) getPlayerData(players.player1);
    else if(cPlayer == 2) getPlayerData(players.player2);
    else if(cPlayer == 3) getPlayerData(players.player3);
    else if(cPlayer == 4) getPlayerData(players.player4);
    else if(cPlayer == 5) getPlayerData(players.player5);
    else if(cPlayer == 6) getPlayerData(players.player6);
}

int setNextPlayingPlayer(){
    cPlayer++;
    if(cPlayer == 1 && players.player1 == nullptr) return setNextPlayingPlayer();
    else if(cPlayer == 2 && players.player2 == nullptr) return setNextPlayingPlayer();
    else if(cPlayer == 3 && players.player3 == nullptr) return setNextPlayingPlayer();
    else if(cPlayer == 4 && players.player4 == nullptr) return setNextPlayingPlayer();
    else if(cPlayer == 5 && players.player5 == nullptr) return setNextPlayingPlayer();
    else if(cPlayer == 6 && players.player6 == nullptr) return setNextPlayingPlayer();
    if(cPlayer >= 7){
        cPlayer = 0;
        cPlayer = setNextPlayingPlayer();
    }
    return cPlayer;
}

void setNextPlayer(){
    cPlayer = setNextPlayingPlayer();
    UpdatePlayerPositions();
    sendCPlayer();
}

void getPlayerData(Player* p){
    Packet data;
    if(p != nullptr){
        p->getSocket()->receive(data);

        if(data.getDataSize() > 0){
            string dn;
            data >> dn;
            if(dn == "DICE"){
                //rolled Dice
                int m;
                data >> m;
                cout << "\n" << endl;
                cout << p->getUsername() << " ROLLED THE DICE AND GOT #" << m << ", Moving Player." << endl;
                p->spotIndex += m;
                p->spotIndex = clamp(p->spotIndex,0,spots.size());
                BasicSpot* s = spots[p->spotIndex];
                cout << "Old Position Was: " << p->x << "," << p->y << ". New Position is: " << s->xPos << "," << s->yPos << "." << endl; 
                p->setPosition(s->xPos,s->yPos);
                setNextPlayer();
            }
        }
    }
}

void createSpotsForAll(){
    cout << "Creating Map, Please Wait..." << endl;
    spots = createSpots();
    Packet p;
    p << "MAP";
    p << spots.size();

    for(BasicSpot* s : spots){
        p << s;
    }

    cout << "Map was loaded on size " << spots.size() << endl;

    sendPacketToAll(players,p);
    sendCPlayer();

    //set player positions to first spot
    setAllPlayersPos(spots.front()->xPos,spots.front()->yPos);
    gameStarted = true;
}

void setAllPlayersPos(int x, int y){
    if(!players.player1name.empty()) players.player1->setPosition(x,y);
    if(!players.player2name.empty()) players.player2->setPosition(x,y);
    if(!players.player3name.empty()) players.player3->setPosition(x,y);
    if(!players.player4name.empty()) players.player4->setPosition(x,y);
    if(!players.player5name.empty()) players.player5->setPosition(x,y);
    if(!players.player6name.empty()) players.player6->setPosition(x,y);
    Packet pl;
    pl << "FPLoc";
    sendPlayerPosition(pl,players);
    sendPacketToAll(players,pl);
}

void UpdatePlayerPositions(){
    Packet pl;
    pl << "PLoc";
    sendPlayerPosition(pl,players);
    sendPacketToAll(players,pl);
}

void sendCPlayer(){
    Packet p;
    p << "CPLR";
    if(cPlayer == 1) p << players.player1name;
    else if(cPlayer == 2) p << players.player2name;
    else if(cPlayer == 3) p << players.player3name;
    else if(cPlayer == 4) p << players.player4name;
    else if(cPlayer == 5) p << players.player5name;
    else if(cPlayer == 6) p << players.player6name;
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

    if(players.player1 != nullptr && players.player1->getUsername() == UsernamePacket) return;
    if(players.player2 != nullptr && players.player2->getUsername() == UsernamePacket) return;
    if(players.player3 != nullptr && players.player3->getUsername() == UsernamePacket) return;
    if(players.player4 != nullptr && players.player4->getUsername() == UsernamePacket) return;
    if(players.player5 != nullptr && players.player5->getUsername() == UsernamePacket) return;
    if(players.player6 != nullptr && players.player6->getUsername() == UsernamePacket) return;

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