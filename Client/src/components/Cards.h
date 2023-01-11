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
Text CardIndex;
Font CardFont;

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
    CardIndex.setPosition(CardSprite.getPosition().x,CardSprite.getPosition().y+145);
    W->draw(CardIndex);

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
        if(cards.size() <= currentCard) currentCard = (cards.size()-1);
        DisplayCard();
        
    }
    else if(last->buttonClicked(mouse)){
        currentCard--;
        if(currentCard <= 0) currentCard = 0;
        DisplayCard();
    }

    if(cards.size() > 0){
        CardIndex.setString("Card:" + std::to_string(currentCard+1));
    }
    else{
        CardIndex.setString("0 Cards");
    }
}

void RemoveCard(){
    cards.erase(cards.begin()+currentCard);
    currentCard++;
    if(cards.size() < currentCard) currentCard--;
    if(currentCard < 0) currentCard = 0;
    DisplayCard();

    if(cards.size() > 0){
        CardIndex.setString("Card:" + std::to_string(currentCard+1));
    }
    else{
        CardIndex.setString("0 Cards");
    }
}

void RemoveAllCards(){
    cards.clear();
    currentCard = 0;
    CardIndex.setString("0 Cards");
    DisplayCard();
}

void cardsStart(){
    if(cards.size() == 0){
        cardTexture.loadFromFile("Assets/Cards/NA.png");
        CardSprite.setTexture(cardTexture);
    }

    CardFont.loadFromFile("Arial.ttf");

    CardIndex.setFont(CardFont);
    CardIndex.setCharacterSize(24);
    CardIndex.setString("Card:" + std::to_string(currentCard+1));
    CardIndex.setFillColor(Color::White);
    CardIndex.setStyle(Text::Bold);
    CardIndex.setOrigin(CardIndex.getLocalBounds().width/2,CardIndex.getLocalBounds().height/2);

    if(cards.size() > 0){
        CardIndex.setString("Card:" + std::to_string(currentCard+1));
    }
    else{
        CardIndex.setString("0 Cards");
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

    if(cards.size() > 0){
        CardIndex.setString("Card:" + std::to_string(currentCard+1));
    }
    else{
        CardIndex.setString("0 Cards");
    }
}

Card* getCurrentCard(){
    if(cards.size() > 0 && currentCard < cards.size()) return cards[currentCard];
    else return nullptr;
}