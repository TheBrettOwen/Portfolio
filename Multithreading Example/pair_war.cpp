// File Name: pair_war.cpp
//
// Authors: Dylan W. Ray, Brett M. Owen
// Date: 10/8/2021
// Program Number: 1
// CS 4328.001 Fall 2021
// Instructor: Dr. J. Marcos Palacios

//Needed libraries.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

//Custom header file.
#include "Deck.h"

//A structure used to represent
//a player, mainly two memory
//spaces for their hand.
struct player {
  int hand[2];
};

//A multipurpose mutex lock used
//for multiple different shared
//data.
pthread_mutex_t mutex_multiSeal = PTHREAD_MUTEX_INITIALIZER;

//All shared global vars/structures.
bool PLAYING = true;
const int NUM_THREADS = 4;
Deck DECK;
std::ofstream OFILE;
int GAME_DRAW = 10;
int TURN_COUNT = 0; 
int ROUND_COUNT = 1;
bool WIN = false;
int TURN = 0;
std::string FINAL_CONTENT = "";
player PLAYERS[3] = { {{-1,-1}},
		      {{-1,-1}},
		      {{-1,-1}} };

//Thread function prototypes.
void *dealer (void *NA);
void *player (void *threadID);
  
int main (int argc, char *argv[]) {
  //Seed input validation
  if (argc == 1 || argc > 2 || atoi(argv[1]) == 0) {
    std::cout << "ERROR INVALID SEED: A SEED MUST " 
	      << "BE AN INTEGER VALUE GREATER "
	      << "THEN 1.\n $ ./pair_war <SEED>\n";
    return -1;
  }

    //Seeding the srng.
    srand(atoi(argv[1]));
  
  //Creating and opening the log file.
  std::string seedString = argv[1];
  std::string fileName = "pair_war_log_" + seedString + ".txt";
  OFILE.open(fileName);

  //Log file header and metadata.
  OFILE << "**ULTIMATE PAIR_WAR TOURNAMENT**\n";
  OFILE << "SEED: " << argv[1] << "\n\n";

  //Creating memory space for all dealer and player.  
  pthread_t dealerPlayers[NUM_THREADS];
  int returnVal;

  //While loop to implement 3 rounds.
  while (ROUND_COUNT < 4) {
    //Round headers to console and log file.
    OFILE << "ROUND: " << ROUND_COUNT <<"\n";
    std::cout << "ROUND: " << ROUND_COUNT <<"\n";

    //Initializing dealer thread.
    returnVal = pthread_create(&dealerPlayers[0], NULL, dealer, NULL);

    //Thread creation verification.
    if (returnVal){
      std::cout << "ERROR; return code from pthread_create() is " << returnVal << std::endl;
      OFILE << "ERROR; return code from pthread_create() is " << returnVal << std::endl;
      OFILE.close();
      return -1;
    }
    
    //Waiting for dealer to finish and exit the round.
    pthread_join(dealerPlayers[0], NULL);

    //Initializing player threads.
    for (long t = 1; t < NUM_THREADS; t++){
      returnVal = pthread_create(&dealerPlayers[t], NULL, player, (void *)t);

      //Thread creation verification.
      if (returnVal){
	      std::cout << "ERROR; return code from pthread_create() is " << returnVal << std::endl;
        OFILE << "ERROR; return code from pthread_create() is " << returnVal << std::endl;
	      OFILE.close();
	      return -1;
      }
    }
    
    //Waiting for each player to finish and exit the round.
    pthread_join(dealerPlayers[1], NULL);
    pthread_join(dealerPlayers[2], NULL);
    pthread_join(dealerPlayers[3], NULL);
    OFILE << "\n";

    //Console output if the game is a draw.
    if (TURN_COUNT >= GAME_DRAW) {
      std::cout << "DRAW" << std::endl;
    }

    //Contents of the deck at the moment a draw/win
    //was declared, before the players returned their
    //cards to the deck.
    std::cout << "DECK: " << FINAL_CONTENT << "\n" << "\n";

    //Resetting variables for next round.
    TURN = ROUND_COUNT;
    ROUND_COUNT++;
    TURN_COUNT = 0;
    WIN = false;
  }

  //Closing our log file.
  OFILE.close();
  
  //Closing out our main thread.
  pthread_exit(0);
}

//Thread function implementations:

void *dealer (void *NA) {
  //Integer to store cards the dealer
  //interacts with.
  int card = 0;

  //Dealer shuffling and log file output
  OFILE << "DEALER: shuffle\n";
  DECK.shuffle();
  OFILE << "DECK: "<< DECK.getContent() << "\n";

  //A switch case with uses the current round number
  //to determine what order the dealer should deal
  //the card. For each case the dealer draws a card
  //the action and card a logged in the log file, then
  //the card is dealt to the proper player. At the end
  //of each case the contents of the deck is written
  //to the log.
  switch(ROUND_COUNT) {
  case 1: card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[0].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[1].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[2].hand[0] = card;
    OFILE << "DECK: "<< DECK.getContent() << "\n";
    break;
  case 2: card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[1].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[2].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[0].hand[0] = card;
    OFILE << "DECK: "<< DECK.getContent() << "\n";
    break;
  case 3: card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[2].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[0].hand[0] = card;
    card = DECK.draw();
    OFILE << "DEALER: deals " << card << "\n";
    PLAYERS[1].hand[0] = card;
    OFILE << "DECK: "<< DECK.getContent() << "\n";
    break;
  };
  OFILE << "DEALER: exits round\n";
  pthread_exit(NULL);  
}

void *player (void *threadID) {
  //Private variables, i.e each thread gets
  //their own copies, used by the threads to
  //interact with the proper global vars.
  //id/discard for the PLAYERS[], and card
  //for the DECK.
  long id;
  id = (long)threadID - 1;
  int card = 0;
  int discard = -1;

  //While loop which iterates until a player has won
  //or a draw is declared.
  while (!WIN) {
    if (TURN_COUNT == GAME_DRAW) {
      break;
    }
    
    //Threads check here to tell if it is their
    //turn or not.
    if (id == TURN) {
      
      //Writing players current hand to the log file.
      if (PLAYERS[id].hand[0] == -1) { 
        OFILE << "PLAYER " << (id + 1) << ": hand "
	      << PLAYERS[id].hand[1] << "\n"; 
      }
      else {
	OFILE << "PLAYER " << (id + 1) << ": hand "
	      << PLAYERS[id].hand[0] << "\n";
      }
      
      //Player draws s card and the log file is updated.
      card = DECK.draw();
      OFILE << "PLAYER " << (id + 1) << ": draws "
	    << card << "\n";
      
      //Player puts card in the an open space
      //in their hand.
      if (PLAYERS[id].hand[0] == -1) {
	      PLAYERS[id].hand[0] = card;
      }
      else {
      	PLAYERS[id].hand[1] = card;
      }
      
      //Player checks for match and the log file is updated.
      //If a match is found WIN is set to true and the current
      //player breaks from the while loop.
      if (PLAYERS[id].hand[0] == PLAYERS[id].hand[1]) {
        OFILE << "PLAYER " << (id + 1) << ": hand " << PLAYERS[id].hand[0]
	      << " " << PLAYERS[id].hand[1] << "\n";
        OFILE << "PLAYER " << (id +1) << ": wins\n";
      	pthread_mutex_lock(&mutex_multiSeal);
      	OFILE << "DECK: "<< DECK.getContent() << "\n";
      	pthread_mutex_unlock(&mutex_multiSeal);
        WIN = true;
        break;
      }
      
      //Here the player found no match, thus a random
      //card is chosen to discarded and the log file
      //is updated.
      else {
        discard = rand() % 2;
        OFILE << "PLAYER " << (id + 1) << ": discard "
	      << PLAYERS[id].hand[discard] << "\n";
        DECK.discard(PLAYERS[id].hand[discard]);
        PLAYERS[id].hand[discard] = -1;
        
        //Writing players hand to the log file after
	//chosen card is discarded.
	OFILE << "PLAYER " << (id + 1) << ": hand ";
	
	//Determining which hand has  the
	//remaining card and updating the log file.
        if (PLAYERS[id].hand[0] == -1) { 
          OFILE << PLAYERS[id].hand[1] << "\n";
        }
        else {
          OFILE << PLAYERS[id].hand[0] << "\n";
        }
	
	//Updating the turn counter.
	pthread_mutex_lock(&mutex_multiSeal);
        TURN_COUNT++;
	pthread_mutex_unlock(&mutex_multiSeal);
      }
      
      //Writing current deck contents after
      //the current players turn to the log file.
      pthread_mutex_lock(&mutex_multiSeal);
      OFILE << "DECK: "<< DECK.getContent() << "\n";

      //Moving to the next turn by incrementing
      //TURN.
      TURN = (TURN + 1) % 3;
      if (TURN_COUNT == GAME_DRAW) {
	OFILE << "DRAW\n";
    }
      pthread_mutex_unlock(&mutex_multiSeal);
    }
    
  }

  //Printing the final match results, the players hand and
  //win status before the round ends.
  pthread_mutex_lock(&mutex_multiSeal);
  std::cout << "PLAYER " << id+1 << ":" << std::endl;
  if (PLAYERS[id].hand[0] == -1) { 
    std::cout << "HAND " << PLAYERS[id].hand[1] << " "; 
    if (PLAYERS[id].hand[0] > -1) {
        std::cout << PLAYERS[id].hand[1] << std::endl; 
    }
    else {std::cout << std::endl;}
  }
  else {
     std::cout << "HAND " << PLAYERS[id].hand[0] << " "; 
    if (PLAYERS[id].hand[1] > -1) {
        std::cout << PLAYERS[id].hand[1] << std::endl; 
    }
    else {std::cout << std::endl;}
  }
  if (PLAYERS[id].hand[0] == PLAYERS[id].hand[1]) {
    std::cout << "WIN yes" << std::endl;
  }
  else {std::cout << "WIN no" << std::endl;}

  //Contents of the deck at the moment a draw/win
  //was declared, before the players returned their
  //cards to the deck.
  FINAL_CONTENT = DECK.getContent(); 

  //Player returns their current hand to the deck.
  if (PLAYERS[id].hand[0] > -1) {
    OFILE << "PLAYER " << (id + 1) << ": discard "
	  << PLAYERS[id].hand[0] << "\n";
    DECK.discard(PLAYERS[id].hand[0]);
    PLAYERS[id].hand[0] = -1;
  }
  if (PLAYERS[id].hand[1] > -1) {
    OFILE << "PLAYER " << (id + 1) << ": discard "
	      << PLAYERS[id].hand[1] << "\n";
    DECK.discard(PLAYERS[id].hand[1]);
    PLAYERS[id].hand[1] = -1; 
  }
  OFILE << "PLAYER " << (id + 1) << ": exits round\n";
  pthread_mutex_unlock(&mutex_multiSeal);
  pthread_exit(NULL);
}
