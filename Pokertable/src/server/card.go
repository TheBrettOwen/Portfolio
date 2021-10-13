package main

import (
	"fmt"
	"log"
	"sort"
)

type card int

func (c card) Suit() int {
	return int(c / 13)
}

func (c card) Rank() int {
	return int(c % 13)
}

func CompareHands(handA, handB [2]card, public [5]card) int {
	var cardsA [7]card
	copy(cardsA[:], handA[:])
	copy(cardsA[2:], public[:])

	var cardsB [7]card
	copy(cardsB[:], handB[:])
	copy(cardsB[2:], public[:])

	return int(ScoreHand(cardsA) - ScoreHand(cardsB))
}

type Score int

func ScoreHand(cards [7]card) Score {
	log.Printf("\n\ncards: %s", cards)

	sort.Slice(cards[:], func(i, j int) bool {
		return cards[i] > cards[j]
	})
	log.Printf("cards sorted strat: %s", cards)
	suitHistogram := make(map[int]int, 4)
	for _, c := range cards {
		suitHistogram[c.Suit()]++
	}
	flush := -1
	for s, n := range suitHistogram {
		if n >= 5 {
			start := sort.Search(len(cards), func(i int) bool {
				return cards[i].Suit() <= s
			})
			flush = cards[start].Rank()
			length := 1
			for i := start + 1; i < len(cards) && cards[i].Suit() == s; i++ {
				if cards[i-1].Rank() != cards[i].Rank()+1 {
					log.Println("run:", cards[start:start+length])
					if length == 5 {
						break
					}
					start = i
					length = 1
					continue
				}
				length++
			}
			log.Println("run:", cards[start:start+length])
			if length == 5 {
				straight := cards[start].Rank()
				log.Println("Straight Flush")
				return StraightFlush + Score(straight<<(4*4))
			}
		}
	}

	rankHistogram := make(map[int]int, 7)
	for _, c := range cards {
		rankHistogram[c.Rank()]++
	}
	var trip []int
	var pair []int
	for c, n := range rankHistogram {
		if n == 4 {
			log.Println("Four of a kind")
			return Quad + Score(c<<(4*4))
		}
		if n == 3 {
			trip = append(trip, c)
			continue
		}
		if n == 2 {
			trip = append(trip, c)
			continue
		}
	}
	log.Println("trip:", trip)
	log.Println("pair:", pair)

	if len(trip) > 0 && (len(trip) > 1 || len(pair) > 0) {
		log.Println("House")
		var max int
		for _, c := range trip {
			if max > c {
				max = c
			}
		}
		return House + Score(max<<(4*4))
	}

	if flush != -1 {
		log.Println("Flush")
		return Flush + Score(flush<<(4*4))
	}

	sort.Slice(cards[:], func(i, j int) bool {
		return cards[i].Rank() > cards[j].Rank()
	})
	log.Printf("cards sorted rank: %s", cards)
	start := 0
	length := 1
	for i := 1; i < len(cards); i++ {
		if cards[i-1].Rank() != cards[i].Rank()+1 {
			log.Println("run:", cards[start:start+length])
			if length == 5 {
				break
			}
			start = i
			length = 1
			continue
		}
		length++
	}
	log.Println("run:", cards[start:start+length])
	if length == 5 {
		straight := cards[start].Rank()
		log.Println("Straight")
		return Straight + Score(straight<<(4*4))
	}

	if len(trip) > 0 {
		log.Println("Triple")
		var max int
		for _, c := range trip {
			if max > c {
				max = c
			}
		}
		return Triple + Score(max<<(4*4))
	}

	if len(pair) > 0 {
		var max int
		var maxi int
		for i, c := range pair {
			if max > c {
				max = c
				maxi = i
			}
		}
		if len(pair) > 1 {
			log.Println("TwoPair")
			copy(pair[maxi:], pair[maxi+1:])
			pair = pair[:len(pair)-1]
			var sndMax int
			for _, c := range pair {
				if max > c {
					sndMax = c
				}
			}
			return TwoPair + Score(max<<(4*4)+sndMax<<(3*4))
		}
		log.Println("Pair")
		return Pair + Score(max<<(4*4))
	}

	log.Println("NoPair")
	return NoPair + Score(cards[0].Rank()<<(4*4)+cards[1].Rank()<<(3*4)+
		cards[2].Rank()<<(2*4)+cards[3].Rank()<<(1*4)+
		cards[4].Rank()<<(0*4))
}

const (
	Spades card = iota * 13
	Hearts
	Diamonds
	Clubs
)

const (
	Two card = iota
	Three
	Four
	Five
	Six
	Seven
	Eight
	Nine
	Ten
	Jack
	Queen
	King
	Ace
)

const (
	NoPair Score = iota << (5 * 4)
	Pair
	TwoPair
	Triple
	Straight
	Flush
	House
	Quad
	StraightFlush
)

func (c card) String() string {
	var suit, rank string
	switch c.Suit() {
	case 0:
		suit = "S"
	case 1:
		suit = "H"
	case 2:
		suit = "D"
	case 3:
		suit = "C"
	default:
		panic("invalid suit")
	}
	switch c.Rank() {
	case 0:
		rank = "2"
	case 1:
		rank = "3"
	case 2:
		rank = "4"
	case 3:
		rank = "5"
	case 4:
		rank = "6"
	case 5:
		rank = "7"
	case 6:
		rank = "8"
	case 7:
		rank = "9"
	case 8:
		rank = "T"
	case 9:
		rank = "J"
	case 10:
		rank = "Q"
	case 11:
		rank = "K"
	case 12:
		rank = "A"
	default:
		panic("invalid rank")
	}
	return rank + suit
}

func (s Score) Normal() Score {
	return (s / (1 << (5 * 4))) << (5 * 4)
}

func (s Score) String() string {
	switch s.Normal() {
	case NoPair:
		return "NoPair"
	case Pair:
		return "Pair"
	case TwoPair:
		return "TwoPair"
	case Triple:
		return "Triple"
	case Straight:
		return "Straight"
	case Flush:
		return "Flush"
	case House:
		return "House"
	case Quad:
		return "Quad"
	case StraightFlush:
		return "StraightFlush"
	}
	panic(fmt.Sprintf("invalid score type: %x", int(s)))
}
