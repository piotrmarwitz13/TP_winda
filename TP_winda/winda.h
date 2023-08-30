//Plik zawieraj¹cy klase windy
#pragma once
#include "framework.h"
#include "osoba.h"
const enum STANY_WINDY { WINDA_IDLE, WINDA_STOP, WINDA_DRZWI, WINDA_RUCH };
class WINDA {
private:
	int y;
	int pietro;
	int cel;
	int cala_waga;
	bool gora;
	int nieaktywnosc;
	STANY_WINDY stan;
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
		this->stan = WINDA_IDLE;
		this->nieaktywnosc = 0;
	}
	void NastepnaAkcja() {
		switch (stan) {
		case WINDA_STOP:
			StanStop();
			break;
		case WINDA_RUCH:
			StanRuch();
			break;
		case WINDA_IDLE:
			StanIdle();
			break;
		}
	}
	
	void StanStop() {
		if (!kolejka.empty()) {
			kolejka.erase(kolejka.begin());
			if (!kolejka.empty()) {

				cel = kolejka.front();
			}
			else {
				stan = WINDA_IDLE;
			}
		}
	}
	void StanIdle() {
		if (!kolejka.empty()) {
			nieaktywnosc = 0;
			cel = kolejka.front();
			if (cel == pietro) stan = WINDA_DRZWI;
			else stan = WINDA_RUCH;
		}
		else {
			nieaktywnosc += 33;
			if (nieaktywnosc >= 4000 && pietro != 0) {
				kolejka.push_back(0);
			}
		}
	}
	void StanRuch(){
		if (y > (5 - cel) * DLUGOSC_PIETRA) {
			y -= PREDKOSC;
		}
		else if (y < (5 - cel) *DLUGOSC_PIETRA) {
			y += PREDKOSC;
		}
		else {
			pietro = cel;
			stan = WINDA_STOP;
		}
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
		kolejka.push_back(cel);
		int x = punkt_x_bazowy + napietrach[pietro].size() * 25 * modyfikator;
		int y = (5 - pietro) * DLUGOSC_PIETRA - 60;

		OSOBA osoba(x, y, cel);
		napietrach[pietro].push_back(osoba);
	}
	int getY() {
		return y;
	}
};
