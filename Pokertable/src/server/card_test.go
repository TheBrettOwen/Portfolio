// SPDX-License-Identifier: BlueOak-1.0.0
// Copyright YEAR Russell Hernandez Ruiz <qrpnxz@hyperlife.xyz>

package main

import "testing"

func TestCompareHands(t *testing.T) {
	type vector struct {
		handA, handB   [2]card
		public         [5]card
		scoreA, scoreB Score
		sign           int
	}
	cases := []vector{
		{
			[2]card{Two + Spades, Three + Spades},
			[2]card{Three + Spades, Two + Spades},
			[5]card{
				Two + Spades, Two + Spades, Two + Spades,
				Five + Hearts, Six + Diamonds,
			},
			Quad, Quad,
			0,
		},
		{
			[2]card{Five + Spades, Six + Spades},
			[2]card{Nine + Spades, Ten + Spades},
			[5]card{
				Three + Spades, Two + Spades, Four + Spades,
				Queen + Hearts, King + Hearts,
			},
			StraightFlush, Flush,
			1,
		},
		{
			[2]card{Five + Spades, Six + Spades},
			[2]card{Nine + Spades, Ten + Spades},
			[5]card{
				Three + Spades, Two + Spades, Four + Diamonds,
				Queen + Hearts, King + Hearts,
			},
			Straight, NoPair,
			1,
		},
		{
			[2]card{Nine + Spades, Ten + Spades},
			[2]card{Five + Spades, Six + Spades},
			[5]card{
				Three + Spades, Two + Spades, Four + Diamonds,
				Queen + Hearts, King + Hearts,
			},
			NoPair, Straight,
			-1,
		},
	}
	abs := func(n int) int {
		if n < 0 {
			return -n
		}
		return n
	}
	for i, vec := range cases {
		var cardsA [7]card
		copy(cardsA[:], vec.handA[:])
		copy(cardsA[2:], vec.public[:])

		var cardsB [7]card
		copy(cardsB[:], vec.handB[:])
		copy(cardsB[2:], vec.public[:])

		scoreA := ScoreHand(cardsA)
		scoreB := ScoreHand(cardsB)
		cmp := int(scoreA - scoreB)
		expect := vec.sign * abs(cmp)
		if Score(scoreA).Normal() != Score(vec.scoreA) ||
			Score(scoreB).Normal() != Score(vec.scoreB) ||
			cmp != expect {
			t.Errorf("%v: %v, %v, %v, expected %v, %v, %v got %v, %v, %v",
				i, vec.handA, vec.handB, vec.public,
				Score(vec.scoreA), Score(vec.scoreB), expect,
				Score(scoreA).Normal(), Score(scoreB).Normal(), cmp,
			)
		}
	}
}
