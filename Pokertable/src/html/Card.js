//This code was appropriated from a tutorial by 101computing.net:
//https://www.101computing.net/poker-card-game-javascript/
class Card {
  constructor(card) {
      this.card = card;
      const cardValues = {
      	"Ace of Hearts":1, "2 of Hearts":2, "3 of Hearts":3, "4 of Hearts":4,
	"5 of Hearts":5, "6 of Hearts":6, "7 of Hearts":7, "8 of Hearts":8,
	"9 of Hearts":9, "10 of Hearts":10, "Jack of Hearts":11, "Queen of Hearts":12, "King of Hearts":13,
	"Ace of Diamonds":1, "2 of Diamonds":2, "3 of Diamonds":3, "4 of Diamonds":4,
	"5 of Diamonds":5, "6 of Diamonds":6, "7 of Diamonds":7, "8 of Diamonds":8,
	"9 of Diamonds":9, "10 of Diamonds":10, "Jack of Diamonds":11, "Queen of Diamonds":12, "King of Diamonds":13,
	"Ace of Clubs":1, "2 of Clubs":2, "3 of Clubs":3, "4 of Clubs":4,
	"5 of Clubs":5, "6 of Clubs":6, "7 of Clubs":7, "8 of Clubs":8,
	"9 of Clubs":9, "10 of Clubs":10, "Jack of Clubs":11, "Queen of Clubs":12, "King of Clubs":13,
	"Ace of Spades":1, "2 of Spades":2, "3 of Spades":3, "4 of Spades":4,
	"5 of Spades":5, "6 of Spades":6, "7 of Spades":7, "8 of Spades":8,
	"9 of Spades":9, "10 of Spades":10, "Jack of Spades":11, "Queen of Spades":12, "King of Spades":13
	};
      const unicodValues=[
      	"🂱","🂲","🂳","🂴",
      	"🂵","🂶","🂷","🂸",
      	"🂹","🂺","🂻","🂽","🂾",
	"🃁","🃂","🃃","🃄",
	"🃅","🃆","🃇","🃈",
	"🃉","🃊","🃋","🃍","🃎",
        "🃑","🃒","🃓","🃔",
        "🃕","🃖","🃗","🃘",
        "🃙","🃚","🃛","🃝","🃞",
	"🂡","🂢","🂣","🂤",
	"🂥","🂦","🂧","🂨",
	"🂩","🂪","🂫","🂭","🂮"
	];

    this.value = cardValues[card];
    this.suit = card.substring(card.indexOf(" of ")+4);
    this.flipped = false;
    var suits = {'Hearts':0, 'Diamonds':13, 'Clubs':26, 'Spades':39 }
    this.position = suits[this.suit] + this.value; //Position in a sorted deck
      //Corresponding unicode for a card image based upon the deck ordering found in carValues
      //and the matching ordering found in unicodeValues.
      this.unicode=unicodValues[(this.position-1)]

	  if((this.value>=2) && (this.value<=9)) {
		  this.specialValue=this.value+card.substring(card.indexOf(" of ")+4);
		  this.specialValue=this.specialValue.substring(0,2);
	  }
	  else{
	  	if (this.value===1) {
			this.specialValue = 'A' + card.substring(card.indexOf(" of ") + 4);
			this.specialValue = this.specialValue.substring(0, 2);
			}
		if (this.value === 10) {
			this.specialValue = 'T' + card.substring(card.indexOf(" of ") + 4);
			this.specialValue = this.specialValue.substring(0, 2);
			}
		if (this.value === 11) {
			this.specialValue = 'J' + card.substring(card.indexOf(" of ") + 4);
			this.specialValue = this.specialValue.substring(0, 2);
		  }
		if (this.value === 12) {
			this.specialValue = 'Q' + card.substring(card.indexOf(" of ") + 4);
			this.specialValue = this.specialValue.substring(0, 2);
		  }
		if (this.value === 13) {
			this.specialValue = 'K' + card.substring(card.indexOf(" of ") + 4);
			this.specialValue = this.specialValue.substring(0, 2);
		  }
		}

	  }

}

