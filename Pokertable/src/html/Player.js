
let Player = function(name) {
	let hand = [null, null] // Cards held
	this.cash = 100           // Cash to bet
	this.bet = 0           // Cash bet
	this.name = name        // Name of player
	this.folded = false	// Whether or not player folded
	this.finalhand=null     //Final showdown hand of the player
	this.rank = 0; 

	this.place_bet = function(amount) {
		let cash = this.cash
		if (cash-amount < 0) {
			// error
			return null
		}
		this.cash -= amount
		this.bet += amount
		return amount
	}

	this.call = function(amount) {
		let cash = this.cash
		if (cash-amount < 0) {
			// error
			return null
		}
		this.cash -= amount
		this.bet = amount
		return amount
	}

	this.reset = function () {
		this.cash = 100;
		this.bet = 0;
		this.folded = false;

	}

	this.deposit = function(amount) {
		this.cash += amount
	}

	this.hand = function() {
		return hand
	}

	this.set_hand = function(card_a, card_b) {
		hand[0] = card_a
		hand[1] = card_b
	}

	this.move = function(passedRank){ 
		let buttonNum = 0;
		let betAmt = 0;
		
		
		if (passedRank  > 7 && passedRank < 15) {
			buttonNum = 1; 
		}

		if(passedRank > 15){
			betAmt = Math.floor(Math.random() * 10);
			betAmt*=5;
			buttonNum = 2; 
		}

		return[buttonNum,betAmt];

	}
}
