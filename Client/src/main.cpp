#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "components/menu.h"

using namespace std;
using namespace sf;

enum GameState {Menu,WaitingForPlayers};
GameState GS = Menu;
bool frameOnLoading = true;

int main()
{
    RenderWindow window(sf::VideoMode(1280, 720), "Candyland");
    MenuComponent* MainMenu = new MenuComponent();

    while (window.isOpen())
    {
        window.clear();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(event.type == Event::TextEntered && GS == Menu){
                cout << "KeyCode: " << (event.text.unicode) << endl;
                MainMenu->addText(event.text.unicode,&window);
            }
        }

        switch (GS)
        {
            case Menu:
                MainMenu->UpdateComponent(window);
                if(MainMenu->isDone()) GS = WaitingForPlayers;
                break;
            case WaitingForPlayers:
                waitForConnections();
                break;
            default:
                break;
        }
        window.display();
    }

    return 0;
}