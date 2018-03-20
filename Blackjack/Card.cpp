#include "Card.h"
#include <iostream>

Card::Card(char* name, wchar_t suit, int scores) {
	this->name[0] = name[0];
	this->name[1] = name[1];
	this->name[2] = name[2];
	this->suit = suit;
	this->scores = scores;
}


Card::~Card() {
}


char* Card::getName() {
	return this->name;
}

int Card::getScores() {
	return this->scores;
}

std::wostream& operator<<(std::wostream& o, const Card& card) {
	o << card.name << card.suit;
	return o;
}