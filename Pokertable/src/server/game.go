package main

import (
	"context"
	"errors"
	"log"
	"math/rand"
	"time"

	"nhooyr.io/websocket"
	"nhooyr.io/websocket/wsjson"
)

type player struct {
	conn   *websocket.Conn
	name   string
	hand   [2]card
	cash   int
	bet    int
	Folded bool
}

type GameRound int

const (
	PreFlop GameRound = iota
	Flop
	Turn
	River
	Showdown
)

type gameState struct {
	ps         []player
	deck       []card
	Dealt      []card
	votes      int
	Ongoing    bool
	Active     int
	Round      GameRound
	Turns      int
	SmallBlind int
	BigBlind   int
	RaiseBet   int
	MaxBet     int
	Pool       int
}

func (gs *gameState) Playing() int {
	var n int
	for _, p := range gs.ps {
		if !p.Folded {
			n++
		}
	}
	return n
}

func (gs *gameState) Add(p player) bool {
	if len(gs.ps) == 7 || gs.Ongoing {
		return false
	}
	gs.ps = append(gs.ps, p)
	return true
}

func (gs *gameState) GatherVotes() {
	baseCtx := context.Background()
	var v interface{}
	for _, p := range gs.ps {
		ctx, cancel := context.WithTimeout(baseCtx, 100*time.Millisecond)
		err := wsjson.Read(ctx, p.conn, &v)
		cancel()
		if err == nil {
			action, ok := v.(string)
			if !ok || action != "ready" {
				log.Printf("match: expected \"ready\", got %q", v)
			}
			gs.votes++
			continue
		}
		if !errors.Is(err, context.DeadlineExceeded) {
			log.Printf("GatherVotes: %v", err)
			bp := p
			var bad int
			for i, p := range gs.ps {
				if p.conn == bp.conn {
					bad = i
					break
				}
			}
			last := len(gs.ps) - 1
			gs.ps[bad] = gs.ps[last]
			gs.ps = gs.ps[:last]
			break
		}
	}
	if gs.votes == len(gs.ps) && len(gs.ps) > 0 {
		gs.Start()
	}
}

func (gs *gameState) Deal() card {
	card := gs.deck[0]
	gs.deck = gs.deck[1:]
	return card
}

func (gs *gameState) Start() {
	log.Println("Game started")
	gs.Ongoing = true
	gs.votes = 0
	gs.deck = make([]card, 52)
	for i := range gs.deck {
		gs.deck[i] = card(i)
	}
	rand.Shuffle(len(gs.deck), func(i, j int) {
		gs.deck[i], gs.deck[j] = gs.deck[j], gs.deck[i]
	})
	for _, p := range gs.ps {
		p.cash = 0
		p.bet = 0
		p.hand[0] = gs.Deal()
		p.hand[1] = gs.Deal()
	}
	gs.Dealt = gs.Dealt[:0]
	gs.Active = 0
	gs.Round = PreFlop
	gs.Turns = 0
	gs.MaxBet = 0
	gs.Pool = 0
}

func (gs *gameState) EndAction() {
	gs.Active = (gs.Active + 1) % len(gs.ps)
}

func (gs *gameState) Action() {
	p := gs.ps[gs.Active]
	defer gs.EndAction()
	if p.Folded {
		return
	}

	var v interface{}
	err := wsjson.Read(context.Background(), p.conn, &v)
	if err != nil {
		// TODO
	}

	action, ok := v.(string)
	if !ok {
		// TODO
	}

	switch gs.Round {
	case PreFlop:
		switch action {
		case "fold":
			p.Folded = true
		case "raise":
			gs.MaxBet += gs.SmallBlind
			fallthrough
		case "call":
			bet := gs.MaxBet - p.bet
			p.cash -= bet
			p.bet += bet
			gs.Pool += bet
		default:
			// TODO
		}
		done := true
		for _, p := range gs.ps {
			if !p.Folded && p.bet != gs.MaxBet {
				done = false
				break
			}
		}
		if done {
			gs.MaxBet = 0
			gs.Dealt = append(gs.Dealt, gs.Deal(), gs.Deal(), gs.Deal())
			gs.Round = Flop
		}
	case Flop:
		switch action {
		case "fold":
			p.Folded = true
		case "check":
			if gs.MaxBet != 0 || gs.Turns >= gs.Playing() {
				// TODO
			}
		case "raise":
			gs.MaxBet += gs.SmallBlind
			fallthrough
		case "call":
			bet := gs.MaxBet - p.bet
			p.cash -= bet
			p.bet += bet
			gs.Pool += bet
		default:
			// TODO
		}
		gs.Turns++
		done := true
		for _, p := range gs.ps {
			if !p.Folded && p.bet != gs.MaxBet {
				done = false
				break
			}
		}
		if done {
			gs.MaxBet = 0
			gs.Turns = 0
			gs.Round = River
		}
	case Turn:
		switch action {
		case "fold":
			p.Folded = true
		case "check":
			if gs.MaxBet != 0 || gs.Turns >= gs.Playing() {
				// TODO
			}
		case "raise":
			gs.MaxBet += gs.SmallBlind
			fallthrough
		case "call":
			bet := gs.MaxBet - p.bet
			p.cash -= bet
			p.bet += bet
			gs.Pool += bet
		default:
			// TODO
		}
		gs.Turns++
		done := true
		for _, p := range gs.ps {
			if !p.Folded && p.bet != gs.MaxBet {
				done = false
				break
			}
		}
		if done {
			gs.MaxBet = 0
			gs.Turns = 0
			gs.Dealt = append(gs.Dealt, gs.Deal())
			gs.Round = River
		}
	case River:
		switch action {
		case "fold":
			p.Folded = true
		case "check":
			if gs.MaxBet != 0 || gs.Turns >= gs.Playing() {
				// TODO
			}
		case "raise":
			gs.MaxBet += gs.SmallBlind
			fallthrough
		case "call":
			bet := gs.MaxBet - p.bet
			p.cash -= bet
			p.bet += bet
			gs.Pool += bet
		default:
			// TODO
		}
		gs.Turns++
		done := true
		for _, p := range gs.ps {
			if !p.Folded && p.bet != gs.MaxBet {
				done = false
				break
			}
		}
		if done {
			gs.MaxBet = 0
			gs.Turns = 0
			gs.Dealt = append(gs.Dealt, gs.Deal())
			gs.Round = Showdown
		}
	}
	if gs.Round == Showdown {
		// TODO
	}
}

func newGame() *gameState {
	return &gameState{
		SmallBlind: 1,
		BigBlind:   2,
		RaiseBet:   4,
	}
}
