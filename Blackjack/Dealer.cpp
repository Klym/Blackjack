#include "Dealer.h"

Dealer::Dealer() {
}

Dealer::Dealer(Deck** decks) {
	this->hand = new Hand(1, decks);
	this->decks = decks;
	this->scores = 0;
	this->countScores();
}

Dealer::~Dealer() {
	delete this->hand;
}

void Dealer::takeCard() {
	this->hand->takeCard(this->decks);
	this->countScores();
}

Hand* Dealer::getHand() {
	return this->hand;
}

int Dealer::getScores() {
	return this->scores;
}

void Dealer::countScores() {
	int aceCount = 0;
	this->scores = 0;
	for (int i = 0; i < this->hand->getCount(); i++) {
		if (this->hand->getCards()[i]->getName()[0] == 'A') {
			aceCount++;
		}
		this->scores += this->hand->getCards()[i]->getScores();
	}
	if (this->scores > 21) {
		while (aceCount > 0 && this->scores > 21) {
			this->scores -= 10;
			aceCount--;
		}
		if (this->scores > 21) {
			throw L"Перебор!";
		}
	}
}