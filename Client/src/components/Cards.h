#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Card {
private:
    string CardName;
    Texture t;
public:
    Card(string n){
        CardName = n;
        t.loadFromFile("Assets/Cards/" + n + ".png");
    }

    string getName() {return CardName; }
    Texture getTexture() {return t; }
};

Sprite CardSprite;

vector<Card*> cards;
int currentCard = 0;

void UpdateCards(RenderWindow* W,RectangleShape RS,Button* next,Button* last,Vector2i Mouse){
    CardSprite.setScale(Vector2f(2,2));
    CardSprite.setOrigin(CardSprite.getLocalBounds().width/2,CardSprite.getLocalBounds().height/2);
    int finalX = ((RS.getPosition().x + (RS.getPosition().x + (RS.getLocalBounds().width/2)))/2); //-(CardSprite.getLocalBounds().width/2 );

    if(cards.size() > currentCard) CardSprite.setTexture(cards[currentCard]->getTexture());
    else{
        Texture empty;
        empty.loadFromFile("Assets/Cards/SWAP.png");
        CardSprite.setTexture(empty);
    }
    CardSprite.setPosition(finalX,720/2);

    next->setPosition(finalX + (next->getShape().getLocalBounds().width*1.5),720/2);
    last->setPosition(finalX - (last->getShape().getLocalBounds().width*2.5),720/2);

    W->draw(CardSprite);
    next->UpdateButton(W,Mouse);
    last->UpdateButton(W,Mouse);
}

void onButtonClicked(int x,int y,Button* next,Button* last){
    Vector2i mouse;
    mouse.x = x;
    mouse.y = y;

    if(next->buttonClicked(mouse)){
        currentCard++;
        if(cards.size() > currentCard) currentCard = (cards.size()-1);
        if(currentCard <= 0) currentCard = 0;
    }
    else if(last->buttonClicked(mouse)){
        currentCard--;
        if(cards.size() > currentCard) currentCard = (cards.size()-1);
        if(currentCard <= 0) currentCard = 0;
    }
}

void createNewCard(string name){
    Card* c = new Card(name);
    cards.push_back(c);
}