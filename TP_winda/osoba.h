//Plik zawieraj¹cy klase osoby
#pragma once
#include "framework.h"
const int WAGA = 70;
const enum STANY_OSOBY { OSOBA_STOP, OSOBA_KOLEJKA, OSOBA_W_WINDZIE, OSOBA_PO_WINDZIE, OSOBA_USUN };
class OSOBA {
private:
	int x;
	int y;
	int waga;
	int cel;
    int cel_x;
	char kierunek;
    STANY_OSOBY stan;
public:
	OSOBA(int x, int y, int cel) {
		this->x = x;
		this->y = y;
		this->cel = cel;
		waga = WAGA;
		kierunek = 's';
        stan = OSOBA_STOP;
	}
    void ObierzCel(int cel_x) {
        this->cel_x = cel_x;
    }
    void UstawKierunek(char kierunek) {
        this->kierunek = kierunek;
    }
    void Ruch() {
        switch (kierunek)
        {
        case 'g':
            y -= PREDKOSC;
            break;
        case 'd':
            y += PREDKOSC;
            break;
        case 'l':
            x -= PREDKOSC;
            if (cel_x >= x) {
                if (stan == OSOBA_PO_WINDZIE) stan = OSOBA_USUN;
                else stan = OSOBA_W_WINDZIE;
                kierunek = 's';
            }
            break;
        case 'p':
            x += PREDKOSC;

            if (cel_x <= x) {
                if (stan == OSOBA_PO_WINDZIE) stan = OSOBA_USUN;
                else stan = OSOBA_W_WINDZIE;
                kierunek = 's';
            }
            break;
        case 's': return;
        default:
            break;
        }
    }
    char SetKierunek(char kierunek) {
        this->kierunek = kierunek;
        return kierunek;
    }
    char GetKierunek() {
        return kierunek;
    }
    const STANY_OSOBY GetStan() const {
        return stan;
    }
    STANY_OSOBY SetStan(STANY_OSOBY stan) {
        this->stan = stan;
        return stan;
    }
    int GetCel() {
        return cel;
    }
    int GetWaga() {
        return waga;
    }

	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
};
