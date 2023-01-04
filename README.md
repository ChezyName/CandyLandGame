# Candyland : Battle of the Ages!

# Gameplay
On each turn, the **player** has the option to *skip thier turn*, *roll the dice* or *use the selected card*. First one to make it to the crown spot wins it all!
If you want to learn [how to play](#client) or learn how to [host a server](#server), scroll to the bottom.


# Spaces / Spots
![Starting Spot](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Spots/START.png)
**Starting Spot:** *where everyone starts*

![Empty Space](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Spots/EMPTY.png)
**Empty Spot:** *this does nothing...*

![Finish Spot](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Spots/END.png)
**End Spot:** *who ever touches this spot first, wins the game!*

![enter image description here](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Spots/CARDGAIN.png)
**Card Gain Spot:** *player gains a random card*



# Cards
*Cards impact gameplay and can only be used once per round.*
![NA Card](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Cards/NA.png)
**N/A Card:** *this shows when the player has no cards.*

![Jump](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Cards/JUMP.png)
**Jump Card:** *player forces themselve to jump two spaces.*

![Swap](https://raw.githubusercontent.com/ChezyName/CandyLandGame/main/Client/Builds/Assets/Cards/SWAP.png)
**Swap Card:** *player goes into 'swap' mode and once clicked on a an opposing player will switch places with them.*


# How To Play
## Client
Once you open up the game, type your name and the ip address given, and wait for the game to start. Once its your turn on the right side there will be a panel that will allow you to either *use a card, skip your turn, or roll a dice* to determine your fate. On the top left side will be the player panel and the player with `<` after thier name is whose turn it is. 
## Server
Server is open on port **7777**, so make sure to port forward on port **7777**.
Once you do that, you can find your public ip address so your friends can join [here](https://whatismyipaddress.com/).
> Its the **IPv4**, so make sure to copy that and send it over to your friends.

Game auto starts after 6 players join, but can be force started by using the command bellow.
### Server Commands:

| Command | Description |
| ----------- | ----------- |
| `start` | starts the game and will not allow others to join.|
| `players` | displays how many players are in the game and thier names.|


# Building the game from Source
In either the client or the server folder just run `mingw32-make`.
