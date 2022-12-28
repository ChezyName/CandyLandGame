#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "game.h"

using namespace sf;

Font font;
Text Username;
Text Ip;

bool isUsername = true;

String UsernameText;
String IpText;

class MenuComponent {
public:
    MenuComponent(){
        font.loadFromFile("Arial.ttf");

        Username.setFont(font);
        Username.setCharacterSize(24);
        Username.setString("Username:");
        Username.setFillColor(Color::White);
        Username.setStyle(Text::Bold);
        Ip.setPosition(Vector2f(15,15));

        Ip.setFont(font);
        Ip.setCharacterSize(24);
        Ip.setString("Server Ip Address:");
        Ip.setFillColor(Color::White);
        Ip.setStyle(Text::Bold);
        Ip.setPosition(Vector2f(2.5,40));
    }

    void UpdateComponent(RenderWindow& window){
        window.draw(Username);
        window.draw(Ip);
    }

    void addText(Uint32 unicode){
        if(isUsername){
            if(unicode == 13){
                isUsername = false;
            }
            else{
                if(unicode == 8){
                    if(UsernameText.getSize() > 0) UsernameText.erase(UsernameText.getSize() - 1, 1);
                }
                else{
                    UsernameText += unicode;
                }
            }
            Username.setString("Username: " + UsernameText);
        }
        else{
            if(unicode == 13){
                if(IpText.getSize() > 0 && UsernameText.getSize() > 0){
                    //Load up game
                    printf("Ip & Username, PERFECT!\n");
                    printf("Loading Up Game...");
                    Username.setString("Username: " + UsernameText + " - Connecting To Server...");
                    ConnectToServer(IpText,UsernameText);
                }
                else{
                    printf("Text not good, retry");
                    isUsername = true;
                }
            }
            else{
                if(unicode == 8){
                    if(IpText.getSize() > 0) IpText.erase(IpText.getSize() - 1, 1);
                }
                else{
                    IpText += unicode;
                }
            }
            Ip.setString("Server Ip Address: " + IpText);
        }
    }
};