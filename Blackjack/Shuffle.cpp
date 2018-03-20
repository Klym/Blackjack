#include <iostream>
#include <conio.h>
#include "Shuffle.h"

Shuffle::Shuffle(int count) {
	Deck::generateCards();
	this->decks = new Deck*[count];
	for (int i = 0; i < count; i++) {
		this->decks[i] = new Deck(52);
	}
	this->dealer = new Dealer(decks);
	this->player = new Player(10000, decks);
}

Shuffle::~Shuffle() {
	for (int i = 0; i < 52; i++) {
		delete Deck::allCards[i];
	}
	delete[] Deck::allCards;

	for (int i = 0; i < Deck::deckCount; i++) {
		delete this->decks[i];
	}
	delete[] this->decks;
	delete this->dealer;
	delete this->player;
}

void Shuffle::startShuffle() {
	this->initRate();
	this->takingPlayerCards();
	this->takingDealerCards();
	if (this->endOfGame) return;
	this->compareScores();
	this->printGame();
	this->print—ongratulation();
}

void Shuffle::initRate() {
	std::wcout << L"¬ÒÂ„Ó: " << this->player->getMoney() << std::endl << std::endl;
	do {
		std::wcout << L"¬‡¯‡ ÒÚ‡‚Í‡: ";
		std::wcin >> this->rate;
		if (this->rate > this->player->getMoney()) {
			std::wcout << L"¬‚Â‰ËÚÂ ‰ÓÔÛÒÚËÏÓÂ ÍÓÎË˜ÂÒÚ‚Ó ‰ÂÌÂ„.\n" << std::endl;
		}
	} while (this->rate > this->player->getMoney());
}

void Shuffle::takingPlayerCards() {
	int keyCode;
	do {
		this->checkCombination();
		this->printGame();
		if (this->playerWin) {
			this->print—ongratulation();
			break;
		}
		if (player->getHand()->getCount() == 5) {
			this->stopShuffle();
			break;
		}
		if (this->risk) {
			std::wcout << L"1. ¬ÁˇÚ¸ ‚˚Ë„˚¯¸ ‚ ‡ÁÏÂÂ 1:1" << std::endl;
			std::wcout << L"2. –ËÒÍÌÛÚ¸ Ë ÔÓÎÛ˜ËÚ¸ ‚˚Ë„˚¯¸ 3:2" << std::endl;
		loop:
			keyCode = _getch();
			switch (keyCode) {
				case 49: this->winGame(1); break;
				case 50: this->stopShuffle(); break;
				default: goto loop; break;
			}
		} else {
		loop1:
			std::wcout << L"1. ’‚‡ÚËÚ" << std::endl;
			std::wcout << L"2. ≈˘∏" << std::endl;
			if (player->getHand()->getCount() == 2 && !this->removed) {
				std::wcout << L"3. —ÌˇÚ¸ ÔÓÎÓ‚ËÌÛ ÒÚ‡‚ÍË?" << std::endl << std::endl;
			}
		loop2:
			keyCode = _getch();
			if (player->getHand()->getCount() == 2 && keyCode == 51 && !this->removed) {
				this->removeHalf();
				goto loop1;
			}
			switch (keyCode) {
				case 49: this->stopShuffle(); break;
				case 50: try {
					player->takeCard();
				} catch (const wchar_t* bust) {
					this->looseGame();
					this->printGame();
					std::wcout << bust << " ";
					this->print—ongratulation();
				} break;
				default: goto loop2; break;
			}
		}
	} while (!this->endOfShuffle);
}

void Shuffle::takingDealerCards() {
	if (this->playerWin || this->playerLoose) return;
	double krate;
	while (dealer->getScores() < 17) {
		try {
			dealer->takeCard();
		} catch (...) {
			if (this->risk) {
				krate = 1.5;
			} else {
				krate = 1;
			}
			this->winGame(krate);
			this->printGame();
			this->print—ongratulation();
			break;
		}
		if (dealer->getScores() == 21) {
			this->printGame();
			if (!this->risk) {
				this->looseGame();
			}
			this->print—ongratulation();
			break;
		}
		if (dealer->getHand()->getCount() == 5 && player->getHand()->getCount() != 5 && !this->risk) {
			this->looseGame();
			this->printGame();
			this->print—ongratulation();
			break;
		}
	}
}

void Shuffle::restartGame() {
	removed = false;
	endOfShuffle = false;
	endOfGame = false;
	playerWin = false;
	playerLoose = false;
	risk = false;
	for (int i = 0; i < Deck::deckCount; i++) {
		this->decks[i]->setCount(52);
		this->decks[i]->shuffleCards();
	}
	this->dealer->getHand()->setCount(1);
	this->player->getHand()->setCount(2);
	this->dealer->getHand()->fillHand(this->decks);
	this->player->getHand()->fillHand(this->decks);
	this->dealer->countScores();
	this->player->countScores();
}

void Shuffle::printGame() {
	std::wcout << std::endl << L" ÓÎÓ‰˚:  ";
	for (int i = 0; i < Deck::deckCount; i++) {
		std::wcout << "[" << this->decks[i]->getCount() << "] ";
	}
	std::wcout << std::endl << L"ƒËÎÂ:   ";
	for (int i = 0; i < dealer->getHand()->getCount(); i++) {
		std::wcout << *dealer->getHand()->getCards()[i] << "   ";
	}
	std::wcout << std::endl << L"¬˚:      ";
	for (int i = 0; i < player->getHand()->getCount(); i++) {
		std::wcout << *player->getHand()->getCards()[i] << "   ";
	}
	std::wcout << std::endl << std::endl;
}

void Shuffle::print—ongratulation() {
	this->endOfGame = true;
	if (this->playerWin) {
		std::wcout << L"œÓÁ‰‡‚ÎˇÂÏ! ¬˚ ‚˚Ë„‡ÎË! ¬‡¯ ‚˚Ë„˚¯: ";
	} else if (this->playerLoose) {
		std::wcout << L"¬˚ ÔÓË„‡ÎË! ¬‡¯ ÔÓË„˚¯: ";
	} else {
		std::wcout << L"–Ó‚ÌÓ! ¬ÓÁ‚‡Ú: ";
	}
	std::wcout << this->rate << L". ¬ÒÂ„Ó: ";
	std::wcout << player->getMoney() << "." << std::endl;
}

void Shuffle::checkCombination() {
	if (player->getScores() == 21) {
		if (dealer->getScores() >= 10 && dealer->getHand()->getCount() == 1) {
			this->risk = true;
			return;
		}
		this->winGame(1.5);
	}
}

void Shuffle::removeHalf() {
	this->rate /= 2;
	this->removed = true;
}

void Shuffle::stopShuffle() {
	this->endOfShuffle = true;
}

void Shuffle::compareScores() {
	int krate;
	if (this->risk) {
		krate = 1.5;
	} else {
		krate = 1;
	}
	if (player->getHand()->getCount() == 5 && dealer->getHand()->getCount() != 5) {
		this->winGame(krate);
	} else if (player->getScores() > dealer->getScores()) {
		this->winGame(krate);
	} else if (player->getScores() < dealer->getScores()) {
		this->looseGame();
	}
}

void Shuffle::winGame(double krate) {
	this->rate *= krate;
	this->player->setMoney(this->player->getMoney() + this->rate);
	this->playerWin = true;
}

void Shuffle::looseGame() {
	this->player->setMoney(this->player->getMoney() - this->rate);
	this->stopShuffle();
	this->playerLoose = true;
}

double Shuffle::getPlayerMoney() {
	return this->player->getMoney();
}