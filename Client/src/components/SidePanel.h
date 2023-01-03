#include <SFML/Graphics.hpp>

using namespace sf;

RectangleShape Interact(Vector2f(600,720));

bool showPanel = false;
int setX = 0;

float clamp2(float x, float min, float max){
    if(x >= max) return max;
    if(x <= min) return min;
    return x;
}

float lerp2(float a, float b, float t)
{
    t = clamp2(t,0,1);
    return t * (b-a) + a;
}

float starttime;

void createSidePanel(){
    setX = 1280-(Interact.getLocalBounds().width/2);
    Interact.setPosition(1280,0);
    Interact.setFillColor(Color(80,80,80,255));
}

void UpdatePanel(RenderWindow* win,Clock clock){
    float seconds = clock.getElapsedTime().asSeconds() - starttime;
    float time = seconds/2.5;

    int x = lerp2(Interact.getPosition().x,setX,time);
    cout << "Interact Pannel X is " << x << endl;
    Interact.setPosition(x,0);

    win->draw(Interact);
}

RectangleShape getPanel(){
    return Interact;
}

void UpdateButton(class Button* b,RenderWindow* win,Vector2i cursor){
    int finalX = ((Interact.getPosition().x + (Interact.getPosition().x + (Interact.getLocalBounds().width/2)))/2)-(b->getShape().getLocalBounds().width/2);
    b->setPosition(finalX,b->getShape().getPosition().y);
    b->UpdateButton(win,cursor);
}

void setShowPanel(bool sp,Clock clock){
    showPanel = sp;
    if(showPanel) setX = 1280-(Interact.getLocalBounds().width/2);
    else setX = 1280;
    starttime = clock.getElapsedTime().asSeconds();
}