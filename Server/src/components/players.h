#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player {
    private:
        TcpSocket* Client;
        std::string Username;

    public:
        int x = -999;
        int y = -999;
        int spotIndex = 0;

        Player(TcpSocket* Socket,std::string Name){
            Client = Socket;
            Client->setBlocking(false);
            Username = Name;
        }

        TcpSocket* getSocket() { return Client; }

        const string& getUsername() { return Username; }
        
        void sendPacket(Packet p) {
            Client->send(p);
        }

        void setPosition(int nx,int ny){
            x = nx;
            y = ny;
        }

        Vector2i getPosition(){
            return Vector2i(x,y);
        }
};

struct Players
{
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    Player* player3 = nullptr;
    Player* player4 = nullptr;
    Player* player5 = nullptr;
    Player* player6 = nullptr;

public:
    string player1name;
    string player2name;
    string player3name;
    string player4name;
    string player5name;
    string player6name;
};

void sendPacketToAll(Players& p,Packet packet){
    if(p.player1 != nullptr) p.player1->sendPacket(packet);
    if(p.player2 != nullptr) p.player2->sendPacket(packet);
    if(p.player3 != nullptr) p.player3->sendPacket(packet);
    if(p.player4 != nullptr) p.player4->sendPacket(packet);
    if(p.player5 != nullptr) p.player5->sendPacket(packet);
    if(p.player6 != nullptr) p.player6->sendPacket(packet);
}

void getUsernamesForPacket(Players& p,Packet packet){
    if(p.player1 != nullptr) packet << p.player1->getUsername();
    if(p.player2 != nullptr) packet << p.player2->getUsername();
    if(p.player3 != nullptr) packet << p.player3->getUsername();
    if(p.player4 != nullptr) packet << p.player4->getUsername();
    if(p.player5 != nullptr) packet << p.player5->getUsername();
    if(p.player6 != nullptr) packet << p.player6->getUsername();
}

void getUsernamesForConsole(Players& p){
    if(p.player1 != nullptr) cout << p.player1->getUsername() << endl;
    if(p.player2 != nullptr) cout << p.player2->getUsername() << endl;
    if(p.player3 != nullptr) cout << p.player3->getUsername() << endl;
    if(p.player4 != nullptr) cout << p.player4->getUsername() << endl;
    if(p.player5 != nullptr) cout << p.player5->getUsername() << endl;
    if(p.player6 != nullptr) cout << p.player6->getUsername() << endl;
}

sf::Packet& operator <<(sf::Packet& packet, const Players& p)
{
    return packet << p.player1name << p.player2name << p.player3name << p.player4name << p.player5name << p.player6name;
}

void sendPlayerPosition(sf::Packet& packet,Players& p){
    if(p.player1 != nullptr) packet << p.player1->x << p.player1->y; else packet << -999 << -999;
    if(p.player2 != nullptr) packet << p.player2->x << p.player2->y; else packet << -999 << -999;
    if(p.player3 != nullptr) packet << p.player3->x << p.player3->y; else packet << -999 << -999;
    if(p.player4 != nullptr) packet << p.player4->x << p.player4->y; else packet << -999 << -999;
    if(p.player5 != nullptr) packet << p.player5->x << p.player5->y; else packet << -999 << -999;
    if(p.player6 != nullptr) packet << p.player6->x << p.player6->y; else packet << -999 << -999;
}