#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <math.h>

#include "components/menu.h"

using namespace std;
using namespace sf;

enum GameState {Menu,WaitingForPlayers,Gameplay};
GameState GS = Menu;
bool frameOnLoading = true;

int main()
{
    RenderWindow window(sf::VideoMode(1280, 720), "Candyland");
    MenuComponent* MainMenu = new MenuComponent();

    float fps;
    Clock clock;;
    Time previousTime = clock.getElapsedTime();
    Time currentTime;

    Font arial;
    font.loadFromFile("Arial.ttf");

    Text FPSText;
    FPSText.setFont(font);
    FPSText.setCharacterSize(18);
    FPSText.setString("9999 FPS");
    FPSText.setFillColor(Color::White);
    FPSText.setStyle(Text::Bold);
    FloatRect bounds = FPSText.getLocalBounds();
    FPSText.setPosition(1280 - bounds.width, 0);

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
            if(event.type == Event::MouseMoved && GS == Gameplay){
                setMousePosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
            }
            if(event.type == Event::MouseButtonPressed && GS == Gameplay){
                onMouseClicked(Mouse::getPosition(window).x,Mouse::getPosition(window).y);
            }
        }

        switch (GS)
        {
            case Menu:
                MainMenu->UpdateComponent(window);
                if(MainMenu->isDone()) GS = WaitingForPlayers;
                break;
            case WaitingForPlayers:
                waitForConnections(&window);
                if(hasGameStarted()) GS = Gameplay;
                break;
            case Gameplay:
                GameUpdateFrame(&window);
            default:
                break;
        }

        //FPS
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        FPSText.setString(std::to_string((int)(floor(fps))) + "FPS");
        previousTime = currentTime;
        
        window.draw(FPSText);
        window.display();
    }

    return 0;
}