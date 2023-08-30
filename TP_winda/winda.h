//Plik zawieraj¹cy klase windy
#pragma once
#include "framework.h"
#include "osoba.h"
class WINDA {
private:
	int y;
	int pietro;
	int cel;
	int cala_waga;
	bool gora;
	std::vector<int> kolejka;
	std::vector<OSOBA> osobywwindzie;
public:
	WINDA() {
		this->y = 500;
		this->pietro = 0;
		this->cel = 0;
		this->cala_waga = 0;
		this->gora = true;
	}
	int GetY() {
		return y;
	}
};
