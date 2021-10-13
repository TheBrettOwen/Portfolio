
let Game = function(num_opponents) {
	let deck = new Deck();

	let playerName = prompt("Please Enter your name", "Ted Lehr");
	this.current = new Player(playerName);
	this.current.set_hand(deck.deal(), deck.deal());
	this.stage=0
	this.currentPlayerIndex=0;
	this.maxBet = 0;
	this.winner=null;

	this.opponents = [];
	for (let i = 0; i < num_opponents; i++) {
		this.opponents.push(new Player(i));
		this.opponents[i].set_hand(deck.deal(), deck.deal());
	}

	//Creating one unified players array.
	this.players=Array.from(this.opponents);
	this.players.unshift(this.current);
	console.log(this.players);

	//A master while loop to control all three stages
	//of the game (flop, turn, river), and each turn of
	//the players.

	//finds the current highest bet out of all players
	//Pass 0 if calling, pass 5 if raising or betting
	this.findMaxBet = function (bet) {
		if (bet > 0) {
			this.maxBet += bet
			return this.maxBet;
		}
		else {
			return this.maxBet;
		}
	}
	this.getStage = function () {
		return this.stage; 
	}

		if(this.stage===0) {
			this.flop=[];
			for(let i=0; i<3; i++) {
				this.flop.push(deck.deal());
			}
		}


				this.fold=function() {
					console.log(this.current.name + " Folded");
					
					this.current.folded=true;
				}

				//makes a bet of $0, checks if a bet has already happened
				this.check=function() {
					if (!this.current.folded){
						let currentBet = this.findMaxBet(0);
						this.current.call(currentBet);
						console.log(currentBet);
						console.log("CHECKED");
					}
					else {
						console.log("FOLDED");
					}
				}
				//makes a bet based on what the user enters
				this.bet=function(betInput) {
					if (!this.current.folded){
						let currentBet = this.findMaxBet(betInput);
						this.current.place_bet(currentBet);
						console.log(currentBet);
						console.log("BET");
					}
					else {
						console.log("FOLDED");
					}
				}

				//calls, and increases the bet if it isn't already at max.
				this.call=function() {
					if (!this.current.folded){
						let currentBet = this.findMaxBet(0);
						this.current.call(currentBet);
						console.log(currentBet);
						console.log("CALLED");
					}
					else {
						console.log("FOLDED");
					}
				}

				//raises the bet by 5
				this.raise=function(betInput) {
					if (!this.current.folded){
						let currentBet = this.findMaxBet(betInput);
						this.current.place_bet(currentBet);
						console.log(currentBet);
						console.log("RAISED");
					}
					else {
						console.log("FOLDED");
					}
				}

				//check,call and bet,raise can honestly be consolidated to one button since they do basically the same thing.

	this.nextPlayer=function() {
		this.currentPlayerIndex=(this.currentPlayerIndex++)%7;
		this.current=this.players[this.currentPlayerIndex];
		while(this.current.folded===true){
			this.skip();
		}

		if(this.currentPlayerIndex===0) {
			let nextStage = this.stage + 1;
			nextStage = nextStage%3;
			this.stage = nextStage;

			if(this.stage===1) {
                                dealAudio.play();
				this.turn=deck.deal();
			}

			if(this.stage===2) {
                                dealAudio.play();
				this.river=deck.deal();
				let i; 
				
				for (i = 0; i < 7; i++) {
					
					this.makeFinalHand(this.players[i]);
				}
				winningHand();
			}
		}


	}

	this.skip=function(){

		if(this.currentPlayerIndex===0) {
			// (this.stage++)%3;
			//The following lines try to make the above line work, since webstorm has an issue with it and it doesn't seem to work
			let nextStage = this.stage + 1;
			nextStage = nextStage%3;
			this.stage = nextStage;

			if(this.stage===1) {
                                dealAudio.play();
				this.turn=deck.deal();
			}

			if(this.stage===2) {
                                dealAudio.play();
				this.river=deck.deal();
				
			}
		}
		this.currentPlayerIndex=(++this.currentPlayerIndex)%7;
		this.current=this.players[this.currentPlayerIndex];
	}


	this.reset=function() {
		this.winner=null;
		this.current=this.players[0];
		this.stage=0;
		deck=new Deck();
		this.flop=[];
		this.turn=null;
		this.river=null;

		for(let i=0; i<3; i++) {
			this.flop.push(deck.deal());
		}

		for(let i=0; i<this.players.length;i++){
			this.players[i].folded=false;
			this.players[i].set_hand(deck.deal(),deck.deal());
		}
	}

	this.get_rank = function() {
		let playerCards=this.current.hand();
		let thisHand = {
			'cards':[],
			'rank':null,
			'message':null
			};
			thisHand.cards[0]=playerCards[0].specialValue;
			thisHand.cards[1]=playerCards[1].specialValue;
			thisHand.cards[2]=this.flop[0].specialValue;
			thisHand.cards[3]=this.flop[1].specialValue;
			thisHand.cards[4]=this.flop[2].specialValue;
			if (this.stage===1) {
				thisHand.cards[5]=this.turn.specialValue;
			}
			if (this.stage === 2) {
				thisHand.cards[5]=this.turn.specialValue;
			}
			

			let rankedHand = rankHand(thisHand);
			console.log(this.current.name + "Hand Rank:" + rankedHand.rank);
			return rankedHand.rank; 

	}


	this.makeFinalHand=function(p){
			
		let playerCards=p.hand();
		 finalHand = {
			'cards':[],
			'rank':null,
			'message':null
			};
			finalHand.cards[0]=playerCards[0].specialValue;
			finalHand.cards[1]=playerCards[1].specialValue;
			finalHand.cards[2]=this.flop[0].specialValue;
			finalHand.cards[3]=this.flop[1].specialValue;
			finalHand.cards[4]=this.flop[2].specialValue;
			finalHand.cards[5]=this.turn.specialValue;
			finalHand.cards[6]=this.river.specialValue;

			p.finalHand=rankHand(finalHand);
			console.log(p);
		}


}
	// this function Rates the players hands. still working out how to find a tie. will work on later.
	//please spell winning with 2 n's
	this.winningHand = function() {
		//using the Winner object already made. making the first player = to the winner.
		this.winner = Player[0];
		for(let i=0; i < 7; i++)
		{
			Player[i].rank = Player[i].finalHand.rank;
		}
		for(let i=0; i<7; i++)
		{
			if(Player[i].rank < Player[i+1].rank) // if the first person's hand ranking is less than the second persons
			{
				this.winner = Player[i+1];	// make the winner = to the player with the higher card ranking.
			}
		}
		if (this.winner === this.Player[0]) {
			alert("You Won!");
		}
		else {
			alert("You Lost!");
		}

	}



