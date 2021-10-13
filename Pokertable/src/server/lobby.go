package main

import (
	"log"

	"nhooyr.io/websocket"
)

type lobby struct {
	id       string
	gs       *gameState
	joinQ    chan player
	startSig chan struct{}
}

//p.conn.Close(websocket.StatusNormalClosure, "")

func (l *lobby) Run() {
	log.Printf("Running lobby %q", l.id)
	for {
		select {
		case p := <-l.joinQ:
			log.Printf("lobby %q: player %q joined", l.id, p.name)
			if !l.gs.Add(p) {
				p.conn.Close(websocket.StatusInternalError, "game full or started")
			} else {
			}
		default:
		}
		switch {
		case !l.gs.Ongoing:
			l.gs.GatherVotes()
		default:
			l.gs.Action()
		}
	}
}
