#include <SFML/Graphics.hpp>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}