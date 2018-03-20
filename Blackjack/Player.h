#pragma once
#include "Dealer.h"
class Player :
	public Dealer {
	double money;
public:
	Player(int money, Deck** decks);
	~Player();

	double getMoney();
	void setMoney(double money);
};

