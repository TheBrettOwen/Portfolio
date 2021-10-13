
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
let g = new Game(6); // Game with 6 opponents.
let playing=false;
let plusMinusAudio=new Audio('Audio/Coin+-.mp3');
let checkAudio=new Audio('Audio/CheckTap.mp3');
let betRaiseCallAudio=new Audio('Audio/CoinBet.mp3');
let foldAudio=new Audio('Audio/CardFlip.mp3');
let dealAudio=new Audio('Audio/CardPlace.mp3');
let shuffleAudio=new Audio('Audio/CardShuffle.mp3');
let mixAudio=new Audio('Audio/CardMix.mp3');
let jazzAudio=new Audio('Audio/royalty_free_bar_jazz_piano_ballad.mp3');
jazzAudio.volume=0.2;
jazzAudio.loop=true;

//counter used to track the bet the player wants to place
this.counter = 0;
//get the current counter, returns the counter
let getCounter = function (){
	return this.counter;
}
//adds the passed number to the counter
let updateCounter = function (number) {
	if ((this.counter + number) >= 0) {
		this.counter += number;
	}
}
//resets the counter
let resetCounter = function () {
	this.counter = 0;
}

let draw_card = function(x, y, angle, s, shown) {
	if (!shown) {
		s = '🂠';
	}
	ctx.translate(x, y);
	ctx.rotate(angle);
	const w = 70;
	const h = 120;
	const cx = -w/2;
	const cy = -h/2
	ctx.fillStyle = 'white';
	ctx.fillRect(cx, cy, w, h);
	let prevStyle = ctx.fillStyle;
	ctx.font = '115px sans';
	if ('🂱' <= s && s <= '🃎') {
		ctx.fillStyle = 'red';
	} else if (s == '🂠') {
	ctx.fillStyle = 'gray';
	} else {
		ctx.fillStyle = 'black';
	}
	ctx.fillText(s, cx-2, cy+h-28);
	ctx.fillStyle = prevStyle;
	ctx.rotate(-angle);
	ctx.translate(-x, -y);
}

let draw_current = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 670, 650);
	ctx.fillText("Bet: $"+p.bet.toString(), 670, 680);
	ctx.fillText("Cash: $"+p.cash.toString(), 670, 710);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? -Math.PI/3 : 0;
	draw_card(700, 800, angle, fst.unicode, true);
	if (!p.folded) {
		draw_card(800, 800, angle, snd.unicode, true);
		return;
	}
	draw_card(750, 800, angle, snd.unicode, true);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(700, 800, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 700, 850);
}

let draw_opponent1 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 220, 120);
	ctx.fillText("Bet: $"+p.bet.toString(), 220, 150);
	ctx.fillText("Cash: $"+p.cash.toString(), 220, 180);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : Math.PI/2;
	draw_card(120, 100, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(120, 200, angle, snd.unicode, false);
		return;
	}
	draw_card(120, 150, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(100, 100, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 100, 150);
}

let draw_opponent3 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 220, 420);
	ctx.fillText("Bet: $"+p.bet.toString(), 220, 450);
	ctx.fillText("Cash: $"+p.cash.toString(), 220, 480);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : Math.PI/2;
	draw_card(120, 400, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(120, 500, angle, snd.unicode, false);
		return;
	}
	draw_card(120, 450, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(100, 400, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 100, 450);
}

let draw_opponent5 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 220, 720);
	ctx.fillText("Bet: $"+p.bet.toString(), 220, 750);
	ctx.fillText("Cash: $"+p.cash.toString(), 220, 780);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : Math.PI/2;
	draw_card(120, 700, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(120, 800, angle, snd.unicode, false);
		return;
	}
	draw_card(120, 750, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(100, 700, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 100, 750);
}

let draw_opponent2 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 1300, 120);
	ctx.fillText("Bet: $"+p.bet.toString(), 1300, 150);
	ctx.fillText("Cash: $"+p.cash.toString(), 1300, 180);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : -Math.PI/2;
	draw_card(1700, 100, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(1700, 200, angle, snd.unicode, false);
		return;
	}
	draw_card(1700, 150, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(1600, 100, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 1600, 150);
}

let draw_opponent4 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 1300, 420);
	ctx.fillText("Bet: $"+p.bet.toString(), 1300, 450);
	ctx.fillText("Cash: $"+p.cash.toString(), 1300, 480);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : -Math.PI/2;
	draw_card(1700, 400, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(1700, 500, angle, snd.unicode, false);
		return;
	}
	draw_card(1700, 450, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(1600, 400, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 1600, 450);
}

let draw_opponent6 = function(p) {
	ctx.fillStyle = '#FFFFFF';
	ctx.font = '32px sans';
	ctx.fillText("Name: "+p.name, 1300, 720);
	ctx.fillText("Bet: $"+p.bet.toString(), 1300, 750);
	ctx.fillText("Cash: $"+p.cash.toString(), 1300, 780);

	let hand = p.hand();
	let fst = hand[0];
	let snd = hand[1];
	let angle = (p.folded) ? Math.PI/3 : -Math.PI/2;
	draw_card(1700, 700, angle, fst.unicode, false);
	if (!p.folded) {
		draw_card(1700, 800, angle, snd.unicode, false);
		return;
	}
	draw_card(1700, 750, angle, snd.unicode, false);
	ctx.fillStyle = 'yellow';
	ctx.fillRect(1600, 700, 160, 70);
	ctx.fillStyle = 'purple';
	ctx.font = '48px sans';
	ctx.fillText("Folded", 1600, 750);
}

let draw_flop = function(flop) {
	let fst = flop[0];
	let snd = flop[1];
	let thr = flop[2];
	draw_card(700, 300, 0, fst.unicode, true);
	draw_card(800, 300, 0, snd.unicode, true);
	draw_card(900, 300, 0, thr.unicode, true);
}

let draw_turn = function(turn) {
	draw_card(1000, 300, 0, (turn) ? turn.unicode : '', turn);
}

let draw_river = function(river) {
	draw_card(1100, 300, 0, (river) ? river.unicode : '', river);
}

let draw_button = function(x, y, w, text) {
	ctx.fillStyle = '#006400';
	ctx.fillRect(x, y, w, 50);
	ctx.fillStyle = 'white';
	ctx.font = '48px sans';
	ctx.fillText(text, x, y+45);
}

let draw_bet_box = function () {
	//1050, 750, 175
	ctx.fillStyle = '#006400';
	ctx.fillRect(1040, 750, 195, 140);
	ctx.fillStyle = 'white';
	ctx.font = '48px sans';
	ctx.fillText("Edit Bet", 1050, 750+45);
}
let draw_fold = function() {
	draw_button(900, 680, 100, "Fold");
}

let draw_check = function() {
	draw_button(900, 820, 125, "Check")
}

let draw_bet = function() {
	draw_button(900, 750, 70, "Bet");
}

let draw_call = function() {
	draw_button(900, 820, 125, "Call")
}

let draw_raise = function() {
	draw_button(900, 750, 125, "Raise");
}

let draw_counter = function () {
	draw_button(1125, 820, 100, "$" + this.counter);
}

let draw_plus = function () {
	draw_button(1050, 820, 30, "+");

}

let draw_minus = function () {
	draw_button(1085, 820, 30, "-");
}

let draw_current_bet = function () {
	let c = getCounter();
	if (c > 0) {
		draw_button(900, 600, 350, "New bet: $" + (this.counter + g.maxBet));
	}
	else {
		draw_button(900, 600, 350, "Current Bet: $" + g.maxBet);
	}
}

let draw_play = function() {
	draw_button(750, 450, 280, "Click to play!");
}

let getMousePos = function(canvas, event) {
	let rect = canvas.getBoundingClientRect();
	let x = event.clientX - rect.left;
	let y = event.clientY - rect.top;
	return {x: x, y: y};
}

let opponentTurn=function() {
	let rank = g.get_rank();
	let oppMove=g.current.move(rank); 
	
	if(oppMove[0]===0){
		g.fold();
		g.nextPlayer();
	}

	if(oppMove[0]===1){
		g.check();
		g.nextPlayer();
	}

	if(oppMove[0]===2){
		g.bet(oppMove[1]);
		g.nextPlayer();
	}

	draw_game(g);
}

let handle_click = function(e) {

	if(!playing){
		let pos=getMousePos(canvas, e);
		if((e)) {
			playing=true;
			draw_game(g);
			shuffleAudio.play();
			dealAudio.play();
			jazzAudio.play();
		}
		else {
			draw_game(g);
		}
	}

	else {
	if(g.current===g.players[0]) {

		let pos=getMousePos(canvas, e);
		let c=getCounter(); 						//points to the counter object
		if((900<=pos.x&&pos.x<=900+100)&&
			(680<=pos.y&&pos.y<=680+50)) {//fold
			foldAudio.play();
			g.fold();
			resetCounter();
			g.nextPlayer();
		}
		else if((900<=pos.x&&pos.x<=900+125)&&
			(820<=pos.y&&pos.y<=820+50)) {//check
			checkAudio.play();
			g.check();
			resetCounter();
			g.nextPlayer();
		}
		else if((1050<=pos.x&&pos.x<=1050+30)&&
			(820<=pos.y&&pos.y<=820+50)) {//increase bet
			plusMinusAudio.play();
			updateCounter(5);
		}
		else if((1085<=pos.x&&pos.x<=1085+30)&&
			(820<=pos.y&&pos.y<=820+50)) {//decrease bet
			plusMinusAudio.play();
			updateCounter(-5);

		}
		else if((900<=pos.x&&pos.x<=900+70)&&
			(750<=pos.y&&pos.y<=750+50)) {// bet
			betRaiseCallAudio.play();
			g.bet(c);
			resetCounter();
			g.nextPlayer();
		}
		else if((900<=pos.x&&pos.x<=900+125)&&
			(820<=pos.y&&pos.y<=820+50)) {//call
			betRaiseCallAudio.play();
			g.call();
			resetCounter();
			g.nextPlayer();
		}
		else if((900<=pos.x&&pos.x<=900+125)&&
			(750<=pos.y&&pos.y<=720+50)) {//raise
			betRaiseCallAudio.play();
			g.raise(c);
			resetCounter();
			g.nextPlayer();
		}
	}

	if(g.players[0].folded){
		console.log("YOU FOLDED");
		shuffleAudio.play();
		g.reset();
	}
	while(g.current!==g.players[0]) {
		opponentTurn();
	}

	draw_game(g);
	}
}



let draw_game = function(g) {
	ctx.fillStyle = '#007b04';
	ctx.fillRect(10, 10, canvas.width, canvas.height);

	if(!playing){
		draw_play();
	}
	else {
		draw_card(1050, 120, 0, "", false);

		let p=g.current;   // The person playing.
		draw_current(p);

		let arr=[draw_opponent1, draw_opponent2, draw_opponent3,
			draw_opponent4, draw_opponent5, draw_opponent6];
		for(let i=0, j=++(g.currentPlayerIndex); i<g.opponents.length; j++, i++) {
			j=j%7;
			arr[i](g.players[i+1]);
		}
		draw_flop(g.flop);
		draw_turn(g.turn);
		draw_river(g.river);

		draw_fold();
		if(g.maxBet===0) {
			draw_check();
			draw_bet();
		}
		else {
			draw_call();
			draw_raise();
		}
		draw_bet_box();
		draw_plus();
		draw_minus();
		draw_counter();
		draw_current_bet();
		if(g.flop&&g.turn&&g.river&&g.winner) {
			g.reset();
		}
	}
}

draw_game(g);
canvas.addEventListener("mousedown", handle_click);


let socket = new WebSocket("ws://hyperlife.xyz:54902");

socket.onopen = function(event) {
  console.log(event)
  console.log("[open] Connection established");
  console.log("Sending to server");
  socket.send(JSON.stringify("room"));
  //socket.send(JSON.stringify("name"));
  socket.send(JSON.stringify(Math.random().toString()));
  //let s = prompt("msg");
  //socket.send(JSON.stringify(s));
};

socket.onmessage = function(event) {
  console.log(event)
  console.log(`[message] Data received from server: ${event.data}`);
};

socket.onclose = function(event) {
  console.log(event)
  if (event.wasClean) {
    console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
  } else {
    // e.g. server process killed or network down
    // event.code is usually 1006 in this case
    console.log('[close] Connection died');
  }
};

socket.onerror = function(error) {
  console.log(event)
  console.log(`[error] ${error.message}`);
};
