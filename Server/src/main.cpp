#include "main.h"

using namespace std;
using namespace sf;

int main()
{
    std::thread commandThread(runCommands);

    TcpListener listener;

    if (listener.listen(7777) != Socket::Done)
    {
        printf("Error\n");
    }

    cout << "Server started on port 7777\n" << endl;

    while (true)
    {
        //Gameplay Loop
        TcpSocket *socket = new TcpSocket;
        if (listener.accept(*socket) != Socket::Done)
        {
            printf("Error\n");
        }

        Packet Username;
        socket->receive(Username);
        std::string UsernamePacket;

        if (Username.getDataSize() > 0)
        {
            Username >> UsernamePacket;
            Username.clear();
        }

        cout << UsernamePacket + " joined from " + socket->getRemoteAddress().toString() << endl;

        Player* newClient = new Player(socket,UsernamePacket);
        Clients.push_back(newClient);
    }
}

void runCommands(){
    while (true)
    {
        string input;
        cin >> input;

        if(input == "getplayers" || input == "players"){
            //get players command
            printf("Current Players In Server:\n");
            for(auto i : Clients){
                cout << i->getUsername() << endl;
            }
            printf("===========================\n");
        }
        else if(input == "clear"){
            system("cls");
        }
        else {
            printf("Command Not Found.\n");
        }
    }
    
}