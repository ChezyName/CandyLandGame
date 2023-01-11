#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "players.h"
#include "spot.h"
#include "button.h"
#include "SidePanel.h"
#include "Cards.h"

using namespace std;
using namespace sf;

class GSocket {
    private:
        String username;
        TcpSocket socket;
    public:
        GSocket(String IP,String Name){
                username = Name;
                socket.connect(IpAddress(IP), 7777);

                Packet Username;
                Username << username.toAnsiString().c_str();
                socket.send(Username);
        }

        TcpSocket* getSocket() { return &socket; }
};


GSocket* playerSocket;
Players allPlayers;
Font currentFont;
string myName;
bool startGame = false;
RectangleShape PlayerList(Vector2f(400,80*6));

RectangleShape gameBG;
Texture gameBGT;

Vector2i MousePosition;

Button* RollDice;
Button* SkipTurn;
Button* UseCard;

Button* NextCard;
Button* LastCard;

void setMousePosition(int x, int y){
    MousePosition.x = x;
    MousePosition.y = y;
}

void ConnectToServer(String IP,String Name,RenderWindow* Window,Font F){
    playerSocket = new GSocket(IP,Name);
    myName = Name;
    allPlayers.ME = myName;
    currentFont = F;
}

bool hasGameStarted(){
    return startGame;
}
Text GameEndingT;
Font GameEndingF;
Text Timer;

void CreatePlayerSprites(RenderWindow* w){
    int x = w->getSize().x/2;
    int y = w->getSize().y/2;

    if(allPlayers.player1t.loadFromFile("Assets/Players/P1.png")){
        cout << "Loading Sprite For " << allPlayers.player1 << endl;
        allPlayers.player1s.setTexture(allPlayers.player1t);
        allPlayers.player1c.setTexture(allPlayers.player1t);

        allPlayers.player1s.setOrigin(allPlayers.player1s.getLocalBounds().width/2, allPlayers.player1s.getLocalBounds().height/2);
        allPlayers.player1c.setOrigin(allPlayers.player1c.getLocalBounds().width/2, allPlayers.player1c.getLocalBounds().height/2);

        allPlayers.player1s.setPosition(x,y);
    }

    if(allPlayers.player2t.loadFromFile("Assets/Players/P2.png")){
        cout << "Loading Sprite For " << allPlayers.player2 << endl;
        allPlayers.player2s.setTexture(allPlayers.player2t);
        allPlayers.player2c.setTexture(allPlayers.player2t);

        allPlayers.player2c.setOrigin(allPlayers.player2c.getLocalBounds().width/2, allPlayers.player2c.getLocalBounds().height/2);
        allPlayers.player2s.setOrigin(allPlayers.player2s.getLocalBounds().width/2, allPlayers.player2s.getLocalBounds().height/2);

        allPlayers.player2s.setPosition(0,0);
    }

    if(allPlayers.player3t.loadFromFile("Assets/Players/P3.png")){
        cout << "Loading Sprite For " << allPlayers.player3 << endl;
        allPlayers.player3s.setTexture(allPlayers.player3t);
        allPlayers.player3c.setTexture(allPlayers.player3t);

        allPlayers.player3s.setOrigin(allPlayers.player3s.getLocalBounds().width/2, allPlayers.player3s.getLocalBounds().height/2);
        allPlayers.player3c.setOrigin(allPlayers.player3c.getLocalBounds().width/2, allPlayers.player3c.getLocalBounds().height/2);

        allPlayers.player3s.setPosition(x,y);
    }

    if(allPlayers.player4t.loadFromFile("Assets/Players/P4.png")){
        cout << "Loading Sprite For " << allPlayers.player4 << endl;
        allPlayers.player4s.setTexture(allPlayers.player4t);
        allPlayers.player4c.setTexture(allPlayers.player4t);

        allPlayers.player4s.setOrigin(allPlayers.player4s.getLocalBounds().width/2, allPlayers.player4s.getLocalBounds().height/2);
        allPlayers.player4c.setOrigin(allPlayers.player4c.getLocalBounds().width/2, allPlayers.player4c.getLocalBounds().height/2);

        allPlayers.player4s.setPosition(x,y);
    }

    if(allPlayers.player5t.loadFromFile("Assets/Players/P5.png")){
        cout << "Loading Sprite For " << allPlayers.player5 << endl;
        allPlayers.player5s.setTexture(allPlayers.player5t);
        allPlayers.player5c.setTexture(allPlayers.player5t);

        allPlayers.player5s.setOrigin(allPlayers.player5s.getLocalBounds().width/2, allPlayers.player5s.getLocalBounds().height/2);
        allPlayers.player5c.setOrigin(allPlayers.player5c.getLocalBounds().width/2, allPlayers.player5c.getLocalBounds().height/2);

        allPlayers.player5s.setPosition(x,y);
    }

    if(allPlayers.player6t.loadFromFile("Assets/Players/P6.png")){
        cout << "Loading Sprite For " << allPlayers.player6 << endl;
        allPlayers.player6s.setTexture(allPlayers.player6t);
        allPlayers.player6c.setTexture(allPlayers.player6t);

        allPlayers.player6s.setOrigin(allPlayers.player6s.getLocalBounds().width/2, allPlayers.player6s.getLocalBounds().height/2);
        allPlayers.player6c.setOrigin(allPlayers.player6c.getLocalBounds().width/2, allPlayers.player6c.getLocalBounds().height/2);

        allPlayers.player6s.setPosition(x,y);
    }

    PlayerList.setFillColor(Color(80,80,80,255));
    PlayerList.setPosition(Vector2f(0,0));

    int xs = (allPlayers.player1c.getLocalBounds().width/2);
    int ys = (allPlayers.player1c.getLocalBounds().height);

    PlayerList.setSize(Vector2f(250,ys*GetPlayerCount(allPlayers)));

    createPlayerTextObjs(allPlayers);

    allPlayers.player1c.setPosition(xs,ys*0.5);
    allPlayers.player2c.setPosition(xs,ys*1.5);
    allPlayers.player3c.setPosition(xs,ys*2.5);
    allPlayers.player4c.setPosition(xs,ys*3.5);
    allPlayers.player5c.setPosition(xs,ys*4.5);
    allPlayers.player6c.setPosition(xs,ys*5.5);

    allPlayers.player1text.setPosition(xs*2,ys*0.25);
    allPlayers.player2text.setPosition(xs*2,ys*1.25);
    allPlayers.player3text.setPosition(xs*2,ys*2.25);
    allPlayers.player4text.setPosition(xs*2,ys*3.25);
    allPlayers.player5text.setPosition(xs*2,ys*4.25);
    allPlayers.player6text.setPosition(xs*2,ys*5.25);

    allPlayers.player1s.setScale(Vector2f(0.5,0.5));
    allPlayers.player2s.setScale(Vector2f(0.5,0.5));
    allPlayers.player3s.setScale(Vector2f(0.5,0.5));
    allPlayers.player4s.setScale(Vector2f(0.5,0.5));
    allPlayers.player5s.setScale(Vector2f(0.5,0.5));
    allPlayers.player6s.setScale(Vector2f(0.5,0.5));

    GameEndingF.loadFromFile("Arial.ttf");
    GameEndingT.setFont(GameEndingF);
    GameEndingT.setCharacterSize(72);
    GameEndingT.setString("A WINNER IS YOU!");
    GameEndingT.setFillColor(Color::White);
    GameEndingT.setStyle(Text::Bold);
    GameEndingT.setPosition(0,0);

    Timer.setFont(GameEndingF);
    Timer.setCharacterSize(72);
    Timer.setString("  5s Remaining");
    Timer.setFillColor(Color::White);
    Timer.setStyle(Text::Bold);
    Timer.setPosition(0,(720/2));

    //Change Background
    gameBGT.loadFromFile("Assets/BG.png");
    gameBG.setTexture(&gameBGT);
    gameBG.setSize(Vector2f(x*2,y*2));

    createSidePanel();
    cardsStart();

    //Create buttons
    RollDice = new Button("Roll Dice",1280-250,25,200,50,currentFont);
    SkipTurn = new Button("Skip Turn",1280-250,650,200,50,currentFont);
    NextCard = new Button(">",1280-250,25,50,50,currentFont);
    LastCard = new Button("<",1280-250,25,50,50,currentFont);
    UseCard = new Button("Use Card",1280-250,525,200,50,currentFont);
}

void waitForConnections(RenderWindow* win){
    Packet data;
    playerSocket->getSocket()->setBlocking(false);
    playerSocket->getSocket()->receive(data);

    if(data.getDataSize() > 0){
        string dataName;
        data >> dataName;

        if(dataName == "Players"){
            //Load Up Players
            data >> allPlayers;
            //getUsernamesForConsole(allPlayers);
        }
        else if(dataName == "Start"){
            startGame = true;
            CreatePlayerSprites(win);
        }
    }

    //Display All Player Names
    ShowPlayerNames(allPlayers,win,currentFont,myName);
}

vector<Spot*> spots;

void DisplaySpots(RenderWindow* window){
    for(auto spot : spots){
        window->draw(spot->spotsprite);
    }
}

bool myTurn = false;
bool hasDone = false;
bool hoverPlayerMode = false;
string C = "";
bool GameEnded = false;

void GameUpdateFrame(RenderWindow* window,Clock Lclock){
    if(!GameEnded){
        //BG
        window->draw(gameBG);

        //Spot Sprites
        lerpPlayerPositions(allPlayers,Lclock);
        DisplaySpots(window);
        glowSpritesOnHover(allPlayers,hoverPlayerMode,MousePosition);
        DisplayPlayers(allPlayers,window);

        //UI
        UpdatePanel(window,Lclock);
        UpdateButton(RollDice,window,MousePosition);
        UpdateButton(SkipTurn,window,MousePosition);
        UpdateButton(UseCard,window,MousePosition);
        UpdateCards(window,getPanel(),NextCard,LastCard,MousePosition);

        window->draw(PlayerList);
        DisplayPlayerIcons(allPlayers,window);
        DisplayPlayersText(allPlayers,window);
    }
    else {
        window->draw(GameEndingT);
        window->draw(Timer);
    }


    //Get Socket Updates
    Packet data;
    playerSocket->getSocket()->receive(data);
    string dataName;
    if(data.getDataSize() > 0){
        data >> dataName;
        if(dataName == "MAP"){
            //Load Up Map
            int spotSize = -1;
            data >> spotSize;
            data >> spotSize;
            cout << "Creating Map Of Size[v2]" << spotSize << endl;
            for(int i = 0; i < spotSize; i++){
                prespot newSpot;
                data >> newSpot;
                Spot* newS = new Spot(newSpot.x,newSpot.y,newSpot.n);
                newS->createSprite();
                spots.push_back(newS);
            }
        }
        else if(dataName == "WINNER"){
            string name;
            data >> name;
            cout << name << " Has Won The Game..." << endl;
            GameEndingT.setString(name + " Won The Game!");
            GameEnded = true;
            RemoveAllCards();
        }
        else if(dataName == "RESTART"){
            GameEnded = false;
            cout << "Restarted Game" << endl;
        }
        else if(dataName == "TIME"){
            int T;
            data >> T;
            cout << T << endl;
            Timer.setString("  " + std::to_string(T) + "s Remaining");
        }
        else if(dataName == "CPLR"){
            string name;
            data >> name;
            allPlayers.personTurn = name;
            cout << "Player Was Chosen: " << name << endl;
            if(allPlayers.ME == name){
                myTurn = true;
                RollDice->setText("Roll Dice");
                hasDone = false;
                setShowPanel(true,Lclock);
            }
            else {
                myTurn = false;
                setShowPanel(false,Lclock);
            }
        }
        else if(dataName == "PLoc"){
            getPlayerPositionsLerp(data,allPlayers);
            onSecondstart(Lclock.getElapsedTime().asSeconds());
        }
        else if(dataName == "FPLoc"){
            getPlayerPositions(data,allPlayers);
        }
        else if(dataName == "CARD"){
            string c;
            data >> c;
            cout << c << endl;
            createNewCard(c);
        }
        else if(dataName == "RCARD"){
            RemoveCard();
        }
    }
}

void onMouseClicked(int x, int y,Clock clk){
    onButtonClicked(x,y,NextCard,LastCard);

    if(!C.empty() && hoverPlayerMode == true){
        //choose player to swap
        if(C == "SWAP"){
            Packet p;
            p << "SWAP";

            int HP = getPlayerClicked(allPlayers,MousePosition);
            int ME = getMyNumber(allPlayers);
            cout << "Sending " << HP << " and " << ME << " TO SERVER!" << endl;
            if(HP != -1 && ME != -1){
                p << HP << ME;
                playerSocket->getSocket()->send(p);
                hoverPlayerMode = false;
            }
        }

        if(C == "STEAL"){
            Packet p;
            p << "STEAL";

            int HP = getPlayerClicked(allPlayers,MousePosition);
            int ME = getMyNumber(allPlayers);
            cout << "Sending " << HP << " and " << ME << " TO SERVER!" << endl;
            if(HP != -1 && ME != -1){
                p << HP << ME;
                playerSocket->getSocket()->send(p);
                hoverPlayerMode = false;
            }
        }
    }
    
    else if(myTurn && !hasDone && !hoverPlayerMode){
        setMousePosition(x,y);
        if(RollDice->buttonClicked(MousePosition)){
            //Roll The Dice
            int r = rand() % 4 + 1;
            cout << "Rolled : " << r << endl;
            
            Packet p;
            p << "DICE";
            p << r;
            playerSocket->getSocket()->send(p);
            hasDone = true;
        }
        else if(SkipTurn->buttonClicked(MousePosition)){
            Packet p;
            p << "SKIP";
            playerSocket->getSocket()->send(p);
            hasDone = true;
        }
        else if(UseCard->buttonClicked(MousePosition)){
            Card* c = getCurrentCard();
            if(c == nullptr) return;
            if(c->getName() == "SWAP"){
                //Pick player to swap
                hoverPlayerMode = true;
                //remove card
                RemoveCard();
                C = "SWAP";
                setShowPanel(false,clk);
            }
            else if(c->getName() == "JUMP"){
                Packet p;
                p << "JUMP";
                playerSocket->getSocket()->send(p);
                RemoveCard();
            }
            else if(c->getName() == "SKIP"){
                Packet p;
                p << "SKIPO";
                playerSocket->getSocket()->send(p);
                RemoveCard();
            }
            else if(c->getName() == "STEAL"){
                hoverPlayerMode = true;
                //remove card
                RemoveCard();
                C = "STEAL";
                setShowPanel(false,clk);
            }
            else if(c->getName() == "RESET"){
                Packet p;
                p << "RESET";
                playerSocket->getSocket()->send(p);
                RemoveCard();
            }
            else if(c->getName() == "REVERSE"){
                Packet p;
                p << "REVERSE";
                playerSocket->getSocket()->send(p);
                RemoveCard();
            }
        }
    }
}