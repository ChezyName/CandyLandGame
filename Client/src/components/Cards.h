#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Card {
private:
    string CardName;
public:
    Card(string n){
        CardName = n;
    }

    string getName() {return CardName; }
};

Texture cardTexture;
Sprite CardSprite;

vector<Card*> cards;
int currentCard = 0;

void UpdateCards(RenderWindow* W,RectangleShape RS,Button* next,Button* last,Vector2i Mouse){
    CardSprite.setScale(Vector2f(2,2));
    CardSprite.setOrigin(CardSprite.getLocalBounds().width/2,CardSprite.getLocalBounds().height/2);
    int finalX = ((RS.getPosition().x + (RS.getPosition().x + (RS.getLocalBounds().width/2)))/2); //-(CardSprite.getLocalBounds().width/2 );

    CardSprite.setPosition(finalX,720/2);

    next->setPosition(finalX + (next->getShape().getLocalBounds().width*1.5),720/2);
    last->setPosition(finalX - (last->getShape().getLocalBounds().width*2.5),720/2);

    W->draw(CardSprite);
    next->UpdateButton(W,Mouse);
    last->UpdateButton(W,Mouse);
}

void DisplayCard(){
    if(cards.size() > 0 && currentCard < cards.size()){
        cardTexture.loadFromFile("Assets/Cards/" + cards[currentCard]->getName() + ".png");
    }
    else{
        cardTexture.loadFromFile("Assets/Cards/NA.png");
    }
    CardSprite.setTexture(cardTexture);
}

void onButtonClicked(int x,int y,Button* next,Button* last){
    Vector2i mouse;
    mouse.x = x;
    mouse.y = y;

    if(next->buttonClicked(mouse)){
        currentCard++;
        if(cards.size() >= currentCard) currentCard = (cards.size()-1);
        DisplayCard();
        
    }
    else if(last->buttonClicked(mouse)){
        currentCard--;
        if(currentCard <= 0) currentCard = 0;
        DisplayCard();
    }
}

void RemoveCard(){
    cards.erase(cards.begin()+currentCard);
    currentCard++;
    if(cards.size() < currentCard) currentCard--;
    if(currentCard < 0) currentCard = 0;
    DisplayCard();
}

void cardsStart(){
    if(cards.size() == 0){
        cardTexture.loadFromFile("Assets/Cards/NA.png");
        CardSprite.setTexture(cardTexture);
    }
}

void createNewCard(string name){
    bool exists = false;
    for(auto card : cards){
        if(card->getName() == name) exists = true; break;
    }
    if(exists) return;

    Card* c = new Card(name);
    cards.push_back(c);
    currentCard = cards.size() - 1;

    cardTexture.loadFromFile("Assets/Cards/" + c->getName() + ".png");
    CardSprite.setTexture(cardTexture);
}

Card* getCurrentCard(){
    if(cards.size() > 0 && currentCard < cards.size()) return cards[currentCard];
    else return nullptr;
}