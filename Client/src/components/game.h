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

void ConnectToServer(String IP,String Name,RenderWindow* Window,Font F){
    playerSocket = new GSocket(IP,Name);
    myName = Name;
    currentFont = F;
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
            getUsernamesForConsole(allOtherPlayers);
        }
    }

    //Display All Player Names
    ShowPlayerNames(allOtherPlayers,win,currentFont,myName);
}