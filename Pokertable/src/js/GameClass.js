//Michael Kammer Class
const deckMod=require('./Deck.js')
const playerMod=require('./Player.js')
const cardMod=require('./Card.js')

let cardsDelt = 0;
//Deal two cards to every player.
//use deck.deal.
//Need to figure out how this will work.
/*
var deck = deckMod.constructor();

console.log(deck.deck);
*/

while (cardsDelt <= 5 )
{
    if(cardsDelt == 0)
    {
        //this.deal(3);
        cardsDelt = cardsDelt + 3;
        //inset a Take bet function from chip handler class.
        console
    }
    elseif(cardsDelt == 3)
    {
       // this.deal(1);
        cardsDelt = cardsDelt + 1;
        //inset a Take bet function from chip handler class.
    }
    elseif(cardsDelt == 4)
    {
        //this.deal(1);
        cardsDelt = cardsDelt + 1;
        //inset a Take bet function from chip handler class.
    }
    //going to identify whos got what in their hands... maybe another class.

    //winning hand gets totalBet


}
/*
RoyalFlush(){
    HeartRoyalFlush = ["10 of Hearts":10 , "Jack of Hearts":11, "Queen of Hearts":12, "King of Hearts":13, "Ace of Hearts":1]
    SpadeRoyalFlush = ["10 of Spades":10,"Jack of Spades":11, "Queen of Spades":12, "King of Spades":13,"Ace of Spades":1]
    ClubRoyalFlush = ["10 of Clubs":10, "Jack of Clubs":11, "Queen of Clubs":12, "King of Clubs":13,"Ace of Clubs":1]
    DiamondRoyalFlush = ["10 of Diamonds":10, "Jack of Diamonds":11, "Queen of Diamonds":12, "King of Diamonds":13, "Ace of Diamonds":1]
}
 StrightFlush{




}



*/


