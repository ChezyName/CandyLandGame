#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "players.h"

using namespace std;
using namespace sf;

class GSocket {
    private:
        String username;
        TcpSocket socket;
    public:
        GSocket(String IP,String Name){
                username = Name;
                socket.connect(IpAddress(IP), 7777);

                Packet Username;
                Username << username.toAnsiString().c_str();
                socket.send(Username);
        }

        TcpSocket* getSocket() { return &socket; }
};


GSocket* playerSocket;
Players allOtherPlayers;
Font currentFont;
string myName;
bool startGame = false;

void ConnectToServer(String IP,String Name,RenderWindow* Window,Font F){
    playerSocket = new GSocket(IP,Name);
    myName = Name;
    currentFont = F;
}

bool hasGameStarted(){
    return startGame;
}

void waitForConnections(RenderWindow* win){
    Packet data;
    playerSocket->getSocket()->setBlocking(false);
    playerSocket->getSocket()->receive(data);

    if(data.getDataSize() > 0){
        string dataName;
        data >> dataName;

        if(dataName == "Players"){
            //Load Up Players
            data >> allOtherPlayers;
            //getUsernamesForConsole(allOtherPlayers);
        }
        else if(dataName == "Start"){
            startGame = true;
        }
    }

    //Display All Player Names
    ShowPlayerNames(allOtherPlayers,win,currentFont,myName);
}

void GameUpdateFrame(RenderWindow* window){
    
}