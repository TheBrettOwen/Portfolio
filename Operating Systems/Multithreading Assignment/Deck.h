// File Name: Deck.h
//
// Authors: Dylan W. Ray, Brett M. Owen
// Date: 10/8/2021
// Program Number: 1
// CS 4328.001 Fall 2021
// Instructor: Dr. J. Marcos Palacios

//Needed libraries.
#include <vector>
#include <string>

class Deck {
private:
  std::vector<int> cards;
  
public:
  Deck();
  void shuffle();
  int draw();
  void discard(int);
  std::string getContent();
};
