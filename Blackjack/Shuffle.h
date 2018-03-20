#pragma once
#include "Player.h"
class Shuffle {
	Deck** decks;
	Dealer* dealer;
	Player* player;
	double rate;
	bool removed = false;
	bool endOfShuffle = false;
	bool endOfGame = false;
	bool playerWin = false;
	bool playerLoose = false;
	bool risk = false;
public:
	Shuffle(int count);
	~Shuffle();

	void startShuffle();
	void restartGame();
	double getPlayerMoney();

private:
	void initRate();
	void takingPlayerCards();
	void takingDealerCards();
	void printGame();
	void print—ongratulation();
	void checkCombination();
	void removeHalf();
	void stopShuffle();
	void compareScores();
	void winGame(double krate);
	void looseGame();
};

