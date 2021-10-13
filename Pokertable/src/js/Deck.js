//This code was appropriated from a tutorial by 101computing.net:
//https://www.101computing.net/poker-card-game-javascript/

class Deck {
  constructor() {
  this.deck = [];
  this.reset(); //Add 52 cards to the deck
  this.shuffle(); //Suffle the deck
} //End of constructor


reset() {
  this.deck = [];
  const suits = ['Hearts', 'Diamonds', 'Clubs', 'Spades'];
  const values = ['Ace', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'Jack', 'Queen', 'King'];

  for (let suit in suits) {
    for (let value in values) {
      this.deck.push(values[value] + " of " + suits[suit]);
    }
  }
} //End of reset()


shuffle() {
  let numberOfCards = this.deck.length;  
  for (var i=0; i<numberOfCards; i++) {
    let j = Math.floor(Math.random() * numberOfCards);
    let tmp = this.deck[i];
    this.deck[i] = this.deck[j];
    this.deck[j] = tmp;
  }
} //End of shuffle()

deal(){
  return this.deck.pop();
} //End of deal()

isEmpty() {
  return (this.deck.length==0);
} //End of isEmpty()

length() {
  return this.deck.length;
}

} //End of Deck Class

module.exports.Deck=Deck
