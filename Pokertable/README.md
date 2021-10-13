# PokerTable

## How to enjoy

Open [index.html](src/html/index.html) on a web browser.

## Status

Functional user interface. Single player game starts and can move through one round (restarts when game is reloaded).
Simple AI in singleplayer mode. Users can connect to the multiplayer lobby, but gameplay through multiplayer is not 
yet available. 

## Next step

* **Michael**
* Implementing the CardHandler class to rank each individual
  player hands to show which hand is the winning hand. 

* **Dylan**
* Implement the functionality of the Game class revisiting
  player that need to ante up or fold depending on if they 
  want to stay in the game or not.

* **Russell**
* Implement mulitplayer

* **Brett**
* Improve Ai opponent
* make check/call and bet/raise buttons contextual to the state of the game
* disperse money at the end of the round

### Work Scope reduction and reallocation of Sprint 2:
NOTE: Over estimation of task complexity and time required changes to our board for sprint 2.
Implementing proper round iterations and button functions was more complex and time intensive
then fist thought. To accommodate for this mistake the task POK-27 had a subsequent refinement task
POK-39 added. The same was applied to task POK-26 with an added refinement task POK-44. Due to 
more work being done on EpicPOK-28 (Playable Game) Epic POK-38 (Single Player Opponent) was reduced
in scope for Sprint 2. This entailed moving Tasks POK-40 to the Backlog and changing POK-39 to its 
current description and requirements.

### Work Scope reduction of Sprint 1:
NOTE: Poor task creation was a major hurdle for sprint 1. Over/under estimation on completion time,
and over/under simplification of individual task complexity hindered progress significantly. Some
tasks were not fleshed out enough and in time to understand what truly should be done for that task.


## Table of contents
* [Project Members](#project-members)
* [What is PokerTable?](#what-is-pokertable)
* [Who is this for?](#who-is-this-for)
* [Why are we making this?](#why-are-we-making-this)
* [Technologies](#technologies)
* [Features](#features)

![PokerTable Logo](img/Poker%20Table%20Logo.png)


## Project Members
* Michael Kammer
* Dylan Ray
* Russell Hernandez Ruiz
* Brett Owen


## What is PokerTable?
PokerTable is a website that lets people play poker online.


## Who is this for?
People who want to play Poker with friends online while not risking Covid at a casino.


## Why are we making this?
PokerTable wants users to be able to enjoy a simple, easy game of poker with no setup or fee's over the internet.


## Technologies
* JavaScript
* Node
* React


## Features/Accomplishments (Sprint2)
* **Michael**
* edited the GameClass (pokertable/src/js/GameClass.js)
  created a specialhand variable to allow the face cards to be valued and handed to the
  CardHandler class to allow ranking. 

* **Dylan**
* Implemented semi-proper rounds for the flow of the poker game in the Game.js file. 
  The Game class with now properly shuffle through each player in order, skipping folded
  players. It also knows when to now deal the other two communal cards, i.e the 'turn' and
  'river'. Changes can be found in [Game.js](src/html/Game.js)
* Implemented a very basic random move generating algorithm for a single player code. To keep
  the code flexible and allow for both multiplayer and single player these changes were made as
  a single function in Player.js which randomly generates a chosen move for a npc player, and is
  then used as input in the Game.js file. Changes can be found in [Player.js](src/html/Player.js)

* **Russell**
* Almost finished the back-end. See [server](src/server/). There is a
  server, and the front-end will connect to it and send some messages.
  It has most of the game logic, mostly what is left is actually sending
  messages to and from the server and client. The game is also online,
  connect to <http://hyperlife.xyz/pokertable>. Use `go run . [ipaddr]`
  from inside the [server](src/server/) directory to run it.

* **Brett**
* Implemented UI functions, such as bet and call when the bet and call buttons are pressed. 
* Fully implemented the fold feature, preventing folded users from making moves. 
* Improved the UI to show the current max bet and let players make specific bets using the + and - buttons
* implemented betting and tracking the current amount of cash players have. 

### TODO

Play a full poker game online

* Featuring all rulesets for many different games of poker.
* Includes systems for betting against other players.
* Allow players to play rounds with friends!

Poker Hand Recogniztion

* Create a function which takes in a players hand and returns a unique number which ranks 
  the hand and then comopares it to all other player hand to determine who has won the round.

Private Rooms

* Allow users to meet in individual poker sessions to play with friends or anyone with a room code.

Customize your PokerTable with unique unlockables

* Allow users to get different aesthetic upgrades with points earned through playing the game.
* Upgrades include background colors, chip decals, and Deck Designs.

Gambling free

* To protect our users, the website does not include or condone using real world money for playing the game.

