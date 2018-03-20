#include "Deck.h"
#include <ctime>
#include <iostream>
#include <algorithm>

Card** Deck::allCards = new Card*[52];
int Deck::deckCount = 0;

Deck::Deck() {
}

Deck::Deck(int count) {
	this->cards = new Card*[count];
	this->count = count;
	this->putCards();
	deckCount++;
}

Deck::~Deck() {
	delete[] this->cards;
}

Card* Deck::takeCard() {
	return cards[--count];
}

void Deck::putCards() {
	for (int i = 0; i < this->count; i++) {
		cards[i] = allCards[i];
	}
	this->shuffleCards();
}

void Deck::shuffleCards() {
	std::random_shuffle(cards, cards + count);
}

void Deck::generateCards() {
	char cardNames[5] = { 'J', 'Q', 'K', 'A' };
	wchar_t suits[4] = { 0x2660, 0x2663, 0x2665, 0x2666 };
	char name[3] = { 0, 0, 0 };
	short scores;
	for (int i = 0, n = 2, k = 0; i < 13; i++, n++) {
		for (int j = 0; j < 4; j++, k++) {
			if (n >= 2 && n < 10) {
				scores = n;
				name[0] = 48 + n;
			} else if (n == 10) {
				name[0] = 49;
				name[1] = 48;
				scores = 10;
			} else if (n > 10 && n <= 13) {
				scores = 10;
				name[0] = cardNames[n - 11];
				name[1] = 0;
			} else {
				scores = 11;
				name[0] = cardNames[n - 11];
			}
			allCards[k] = new Card(name, suits[j], scores);
		}
	}
}

Card** Deck::getCards() {
	return this->cards;
}

int Deck::getCount() {
	return this->count;
}

void Deck::setCount(int count) {
	this->count = count;
}