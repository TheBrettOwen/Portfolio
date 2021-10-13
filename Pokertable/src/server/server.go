package main

import (
	"context"
	"log"
	"net/http"
	"os"
	"time"

	"nhooyr.io/websocket"
	"nhooyr.io/websocket/wsjson"
)

func match(c *websocket.Conn) {
	var v interface{}
	var err error
	baseCtx := context.Background()

	ctx, cancel := context.WithTimeout(baseCtx, 5*time.Second)
	err = wsjson.Read(ctx, c, &v)
	cancel()
	if err != nil {
		log.Printf("match: failed to fetch room id: %v", err)
		return
	}

	id, ok := v.(string)
	if !ok {
		log.Printf("match: expected room id, got %v", v)
		return
	}

	ctx, cancel = context.WithTimeout(baseCtx, 5*time.Second)
	err = wsjson.Read(ctx, c, &v)
	cancel()
	if err != nil {
		log.Printf("match: failed to fetch name: %v", err)
		return
	}

	name, ok := v.(string)
	if !ok {
		log.Printf("match: expected player name, got %v", v)
		return
	}

	log.Printf("Player %q is trying to connect to lobby %q", name, id)

	lobby := st.findOrCreate(id)
	if lobby.joinQ == nil {
		log.Printf("Lobby %q was full", id)
		return
	}
	lobby.joinQ <- player{
		conn: c,
		name: name,
	}
}

func main() {
	addr := "127.0.0.1"
	if len(os.Args) > 1 {
		addr = os.Args[1] + ":54902"
	}
	log.Println(http.ListenAndServe(addr, http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		c, err := websocket.Accept(w, r, &websocket.AcceptOptions{
			InsecureSkipVerify: true,
		})
		if err != nil {
			log.Println(err)
			return
		}
		log.Println("Player connected.")
		go match(c)
		//c.Close(websocket.StatusNormalClosure, "")
	})))
}
