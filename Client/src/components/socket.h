#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Socket {
    public:
        Socket(){
            
        }
};

void JoinServer(){
    TcpSocket socket;
    Socket::Status status = socket.connect("localhost", 7777);

    Packet Username;
    Username << "ChezyName";
    socket.send(Username);
}