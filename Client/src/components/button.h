#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Button {
private:
    RectangleShape ButtonShape;
    Text ButtonText;
    Font cf;

    bool isHovering(Vector2i Mouse){
        int maxX = (ButtonShape.getLocalBounds().width + ButtonShape.getPosition().x);
        int minX = ButtonShape.getPosition().x;
        int maxY = (ButtonShape.getLocalBounds().height + ButtonShape.getPosition().y);
        int minY = ButtonShape.getPosition().y;

        return (maxX >= Mouse.x && minX <= Mouse.x && maxY >= Mouse.y && minY <= Mouse.y);
    }

public:
    Button(String buttonStr,int x,int y,int width,int height,Font f) {
        ButtonShape.setSize(Vector2f(width,height));
        ButtonShape.setPosition(Vector2f(x,y));

        cf.loadFromFile("Arial.ttf");

        ButtonText.setFont(cf);
        ButtonText.setStyle(Text::Bold);
        ButtonText.setFillColor(Color::White);
        ButtonText.setString(buttonStr);
        ButtonText.setOrigin(ButtonText.getLocalBounds().width/2,ButtonText.getLocalBounds().height/2);
        ButtonText.setPosition(ButtonShape.getPosition().x + (ButtonShape.getLocalBounds().width/2),ButtonShape.getPosition().y + (ButtonShape.getLocalBounds().height/2));
    }

    void setText(string T){
        ButtonText.setString(T);
    }

    void UpdateButton(RenderWindow* w,Vector2i cursorPos){

        if (isHovering(cursorPos)){
            // Hovering on shape
            ButtonShape.setFillColor(Color::Cyan);
        }
        else{
            ButtonShape.setFillColor(Color::Black);
        }


        w->draw(ButtonShape);
        w->draw(ButtonText);
    }

    bool buttonClicked(Vector2i mouse){
        if(isHovering(mouse)){
            cout << "Clicked On Button : " << ButtonText.getString().toAnsiString().c_str() << endl;
            return true;
        }
        else return false;
    }
};