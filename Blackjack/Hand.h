#pragma once
#include "Deck.h"
class Hand :
	public Deck {
public:
	Hand(int count, Deck** decks);
	~Hand();
	
	void fillHand(Deck** decks);
	void takeCard(Deck** decks);
};

