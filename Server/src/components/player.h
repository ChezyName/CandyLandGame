#include <SFML/Network.hpp>

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
};