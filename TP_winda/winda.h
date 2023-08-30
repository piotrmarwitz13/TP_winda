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

public:
	std::vector<int> kolejka;
	std::vector<OSOBA> osobywwindzie;
	std::vector<OSOBA> napietrach[5];
	WINDA() {
		this->y = 500;
		this->pietro = 0;
		this->cel = 0;
		this->cala_waga = 0;
		this->gora = true;
	}
	int getY() {
		return y;
	}
	void request(int ID) {
		int punkt_x_bazowy, modyfikator;
		int pietro = ID / 10;
		int cel = ID % 10;
		if (pietro % 2) {
			punkt_x_bazowy = 475;
			modyfikator = 1;
		}
		else {
			punkt_x_bazowy = 175;
			modyfikator = -1;
		}
		this->cel = cel;
		int x = punkt_x_bazowy + napietrach[pietro].size() * 25 * modyfikator;
		int y = (5 - pietro) * DLUGOSC_PIETRA - 60;

		OSOBA osoba(x, y, cel);
		napietrach[pietro].push_back(osoba);
	}
	void Wykonaj() {
		if (y > (5 - cel) * DLUGOSC_PIETRA) {
			y -= PREDKOSC;
		}
		else if (y < (5 - cel) *DLUGOSC_PIETRA) {
			y += PREDKOSC;
		}
		else {
			pietro = cel;
		}
	}
};
