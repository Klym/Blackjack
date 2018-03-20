#pragma once
#include "Hand.h"
class Dealer {
protected:
	Hand* hand;
	Deck** decks;
	int scores;
public:
	Dealer();
	Dealer(Deck** decks);
	~Dealer();
	
	void takeCard();

	Hand* getHand();
	int getScores();
	void countScores();
};

