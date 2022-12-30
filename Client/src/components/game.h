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
Players allPlayers;
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

void CreatePlayerSprites(){
    int x = 1280/2;
    int y = 720/2;

    if(allPlayers.player1t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player1 << endl;
        allPlayers.player1s.setTexture(allPlayers.player1t);
        allPlayers.player1s.setPosition(x,y);
    }

    if(allPlayers.player2t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player2 << endl;
        allPlayers.player2s.setTexture(allPlayers.player1t);
        allPlayers.player2s.setPosition(x,y);
    }

    if(allPlayers.player3t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player2 << endl;
        allPlayers.player3s.setTexture(allPlayers.player3t);
        allPlayers.player3s.setPosition(x,y);
    }

    if(allPlayers.player4t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player3 << endl;
        allPlayers.player4s.setTexture(allPlayers.player4t);
        allPlayers.player4s.setPosition(x,y);
    }

    if(allPlayers.player5t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player4 << endl;
        allPlayers.player5s.setTexture(allPlayers.player5t);
        allPlayers.player5s.setPosition(x,y);
    }

    if(allPlayers.player6t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player5 << endl;
        allPlayers.player6s.setTexture(allPlayers.player6t);
        allPlayers.player6s.setPosition(x,y);
    }
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
            data >> allPlayers;
            //getUsernamesForConsole(allPlayers);
        }
        else if(dataName == "Start"){
            startGame = true;
            CreatePlayerSprites();
        }
    }

    //Display All Player Names
    ShowPlayerNames(allPlayers,win,currentFont,myName);
}

void GameUpdateFrame(RenderWindow* window){
    window->draw(allPlayers.player1s);
}