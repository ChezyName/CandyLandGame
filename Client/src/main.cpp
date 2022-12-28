#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "components/menu.h"

using namespace std;
using namespace sf;

enum GameState {Menu,Playing};
GameState GS = Menu;

int main()
{
    RenderWindow window(sf::VideoMode(1280, 720), "Candyland");
    MenuComponent* MainMenu = new MenuComponent();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(event.type == Event::TextEntered && GS == Menu){
                cout << "KeyCode: " << (event.text.unicode) << endl;
                MainMenu->addText(event.text.unicode);
            }
        }

        window.clear();
        switch (GS)
        {
            case Menu:
                MainMenu->UpdateComponent(window);
                break;
            
            default:
                break;
        }
        window.display();
    }

    return 0;
}