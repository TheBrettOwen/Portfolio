package main

import (
	"log"
	"sort"
	"sync"
)

type lobbyList []*lobby

func (ll lobbyList) Len() int { return len(ll) }

func (ll lobbyList) Less(i, j int) bool {
	return ll[i].id < ll[j].id
}

func (ll lobbyList) Swap(i, j int) {
	ll[i], ll[j] = ll[j], ll[i]
}

func (ll lobbyList) Sort() {
	sort.Sort(ll)
}

func (ll lobbyList) Search(id string) (int, bool) {
	i := sort.Search(ll.Len(), func(i int) bool {
		return ll[i].id >= id
	})
	return i, i < len(ll) && ll[i].id == id
}

func (ll *lobbyList) Add(l *lobby) lobbyList {
	*ll = append(*ll, l)
	ll.Sort()
	return *ll
}

type state struct {
	sync.RWMutex
	list lobbyList
}

func (st *state) findOrCreate(id string) *lobby {
	st.RLock()
	i, ok := st.list.Search(id)
	st.RUnlock()
	if ok {
		return st.list[i]
	}
	log.Printf("Creating lobby %q", id)
	lobby := &lobby{
		id:    id,
		gs:    newGame(),
		joinQ: make(chan player, 6),
	}
	go lobby.Run()
	st.Lock()
	st.list.Add(lobby)
	st.Unlock()
	return lobby
}

func (st *state) remove(id string) bool {
	log.Printf("Removing lobby %q", id)
	st.RLock()
	i, ok := st.list.Search(id)
	st.RUnlock()
	if !ok {
		return false
	}
	st.Lock()
	copy(st.list[i:], st.list[i+1:])
	st.list = st.list[:len(st.list)-1]
	st.Unlock()
	return true
}

var st = new(state)
