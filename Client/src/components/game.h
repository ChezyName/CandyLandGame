#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

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
};


GSocket* playerSocket;
void ConnectToServer(String IP,String Name){
    playerSocket = new GSocket(IP,Name);
}