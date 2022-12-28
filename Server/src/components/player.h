#include <SFML/Network.hpp>

class Player {
    private:
        sf::TcpSocket* Client;
    public:
        Player(sf::TcpSocket* Socket){
            Client = Socket;
        }
};