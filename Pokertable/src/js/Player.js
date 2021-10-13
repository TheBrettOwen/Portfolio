let Player = function(name) {
	let hand = [null, null] // Cards held
	let cash = 0            // Cash to bet
	this.name = name        // Name of player
	this.fold = false	// Whether or not player folded

	this.bet = function(amount) {
		let cash = this.cash
		if (cash-amount < 0) {
			// error
			return null
		}
		this.cash -= amount
		return amount
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
}

module.exports.Player=Player
