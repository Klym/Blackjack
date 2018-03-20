#include "Hand.h"
#include <iostream>

Hand::Hand(int count, Deck** decks) {
	this->cards = new Card*[5];
	this->count = count;
	this->fillHand(decks);
}

Hand::~Hand() {
}

void Hand::fillHand(Deck** decks) {
	for (int i = 0; i < count; i++) {
		this->cards[i] = decks[rand() % Deck::deckCount]->takeCard();
	}
}

void Hand::takeCard(Deck** decks) {
	this->cards[count++] = decks[rand() % Deck::deckCount]->takeCard();
}