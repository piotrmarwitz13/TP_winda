//Plik zawieraj¹cy klase osoby
#pragma once
#include "framework.h"
const int WAGA = 70;
class OSOBA {
private:
	int x;
	int y;
	int waga;
	int cel;
public:
	OSOBA(int x, int y, int cel) {
		this->x = x;
		this->y = y;
		this->cel = cel;
		waga = WAGA;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
};
