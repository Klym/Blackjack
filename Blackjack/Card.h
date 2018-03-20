#pragma once
#include <iostream>

class Card {
	char name[3];
	wchar_t suit;
	int scores;
public:
	Card(char* name, wchar_t suit, int scores);
	~Card();
	
	char* getName();
	int getScores();

	friend std::wostream& operator<<(std::wostream& out, const Card &card);
};