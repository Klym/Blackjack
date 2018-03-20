#include "Shuffle.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <fcntl.h>
#include <io.h>

void main() {
	srand(time(0));
	_setmode(_fileno(stdout), _O_U16TEXT);

	int keyCode;
	Shuffle* shuffle = new Shuffle(4);

start:
	shuffle->startShuffle();
	if (shuffle->getPlayerMoney() <= 0) {
		_getch();
		return;
	}
	std::wcout << std::endl << L"Играть ещё?" << std::endl;
	std::wcout << L"1. Да\n2. Нет" << std::endl;
loop:
	keyCode = _getch();
	switch (keyCode) {
		case 49: system("cls"); shuffle->restartGame(); goto start; break;
		case 50: break;
		default: goto loop; break;
	}

	delete shuffle;
}