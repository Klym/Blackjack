#pragma once
#include "Card.h"

class Deck {
protected:
	Card** cards;
	int count;
public:
	Deck();
	Deck(int count);
	~Deck();

	Card* takeCard();
	void shuffleCards();
	Card** getCards();
	int getCount();
	void setCount(int count);

	static int deckCount;
	static Card** allCards;
	static void generateCards();
private:
	void putCards();
};