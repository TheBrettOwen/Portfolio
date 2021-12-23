// File Name: Deck.cpp
//
// Authors: Dylan W. Ray, Brett M. Owen
// Date: 10/8/2021
// Program Number: 1
// CS 4328.001 Fall 2021
// Instructor: Dr. J. Marcos Palacios

//Needed libraries.
#include <vector>
#include <stdlib.h>
#include <algorithm>

//Custom header file.
#include "Deck.h"

//Deck member function definitions:

//**************************************************************************
//Class constructor which initialized the private
//member integer vector, {1,1,1,1, . . . 13,13,13,13}
//**************************************************************************
Deck::Deck() {
  for (int i = 1; i < 14; i++) {
    for (int j = 0; j < 4; j++) {
      cards.push_back(i);
    }
  }
}

//**************************************************************************
//Using the seeded srng, the srng was seeded at the top of
//main(), a random index of the deck integer vector is chosen
//and then swapped with 'i' as the for loop iterates through
//the entire deck.
//**************************************************************************
void Deck::shuffle() {
  for (int i = 0; i < cards.size(); i++) {
    int swapNum = rand() % 52;
    std::swap(cards[0], cards[swapNum]);
  }
}

int Deck::draw() {
  int card = cards[0];
  cards.erase(cards.begin());
  return card;
}

void Deck::discard(int card) {
  cards.push_back(card);
}

//**************************************************************************
//Iterate through the entire deck integer vector, and at
//each step pull the top card off the deck write
//its value to a string, put the card back at the bottom
//of the deck, and finally return the contents string.
//**************************************************************************
std::string Deck::getContent() {
  std::string contents;
  int card = 0;
  for (int i = 0; i < cards.size(); i++) {
    card = draw();
    contents += std::to_string(card) + " ";
    discard(card);
  }
  return contents;
}
