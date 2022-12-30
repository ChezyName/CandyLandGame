#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player {
    private:
        TcpSocket* Client;
        std::string Username;

    public:
        Player(TcpSocket* Socket,std::string Name){
            Client = Socket;
            Username = Name;
        }

        std::string getUsername() { return Username; }
        
        void sendPacket(Packet p) {
            Client->send(p);
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
    return packet << p.player1->getUsername() << p.player2->getUsername() << p.player3->getUsername() << p.player4->getUsername() << p.player5->getUsername() << p.player6->getUsername();
}