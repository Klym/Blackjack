#include "Player.h"

Player::Player(int money, Deck** decks) {
	this->money = money;
	this->hand = new Hand(2, decks);
	this->decks = decks;
	this->scores = 0;
	this->countScores();
}

Player::~Player() {
}

double Player::getMoney() {
	return this->money;
}

void Player::setMoney(double money) {
	this->money = money;
}