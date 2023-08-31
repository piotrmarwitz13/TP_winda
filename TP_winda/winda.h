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
	bool kierunek_gora;
	int nieaktywnosc;
	int drzwi;
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
		this->kierunek_gora = true;
		this->stan = WINDA_IDLE;
		this->nieaktywnosc = 0;
		this->drzwi = 0;
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
		case WINDA_DRZWI:
			StanDrzwi();
		}
		RuszaniePasazerow();
	}
	//FUNKCJE STANÓW
	void StanStop() {
		//inicjalizator ruchu dla pasazerow wchodz¹cych
		if (cala_waga >= MAX_WAGA) return;
		for (size_t kolejka_osob = 0; kolejka_osob < napietrach[pietro].size(); kolejka_osob++) {
			OSOBA& osoba = napietrach[pietro][kolejka_osob];
			if (osoba.GetKierunek() == 's' && osoba.GetStan() == OSOBA_STOP) {
				if (pietro % 2) {
					osoba.UstawKierunek('l');
					osoba.SetCelX(osoba.GetX() - 200 + osobywwindzie.size() * 10);
				}
				else {
					osoba.UstawKierunek('p');
					osoba.SetCelX(osoba.GetX() + 200 - osobywwindzie.size() * 10);
				}
				osoba.SetStan(OSOBA_KOLEJKA);
			}
			if (osoba.GetStan() == OSOBA_W_WINDZIE) {
				cala_waga += osoba.GetWaga();
				DodajDoKolejki(osoba.GetCel());
				osobywwindzie.push_back(osoba);
			}
		}
		//usuwanie osob wchodz¹cych do windy i osob które wysz³y z pietra Erase-Idiom Algorithm
		napietrach[pietro].erase(std::remove_if(napietrach[pietro].begin(), napietrach[pietro].end(), [](OSOBA const& p) {return p.GetStan() == OSOBA_W_WINDZIE || p.GetStan() == OSOBA_USUN; }), napietrach[pietro].end());

		//osoby wychodzace z windy
		for (auto& osoba : osobywwindzie) {
			if (osoba.GetCel() == pietro) {
				if (pietro % 2) {
					osoba.UstawKierunek('p');
					osoba.SetCelX(720);
				}
				else {
					osoba.UstawKierunek('l');
					osoba.SetCelX(0);
				}
				cala_waga -= osoba.GetWaga();
				osoba.SetStan(OSOBA_PO_WINDZIE);
				napietrach[pietro].push_back(osoba);
			}
		}
		//usuwanie osob wychodzaczych z windy
		osobywwindzie.erase(std::remove_if(osobywwindzie.begin(), osobywwindzie.end(), [&](OSOBA const& p) {return p.GetStan() == OSOBA_PO_WINDZIE; }), osobywwindzie.end());
		if (cala_waga >= MAX_WAGA) return;
		if (napietrach[pietro].empty()) {
			stan = WINDA_DRZWI;
		}
		return;
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
				DodajDoKolejki(0);
			}
		}
	}
	void StanRuch(){
		if (y > (5 - cel) * DLUGOSC_PIETRA) {
			y -= PREDKOSC;
			KierunekPasazerow('g');
		}
		else if (y < (5 - cel) *DLUGOSC_PIETRA) {
			y += PREDKOSC;
			KierunekPasazerow('d');
		}
		else {
			pietro = cel;
			stan = WINDA_DRZWI;
		}
	}
	void StanDrzwi() {
		KierunekPasazerow('s');
		bool check = false;
		for (auto& osoba : osobywwindzie) {
			if (osoba.GetCel() == pietro) check = true;
		}
		//drzwi sie otwieraja
		if (!napietrach[pietro].empty() || check) {
			if (drzwi >= 80) {
				stan = WINDA_STOP;
			}
			else drzwi += PREDKOSC;
		}
		else {
			//drzwi sie zamykaja
			if (drzwi <= 0) {
				KierunekWindy();
				stan = WINDA_RUCH;

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
			else drzwi -= PREDKOSC;
		}
	}
	//FUNKCJE DLA PASAZEROW I KIERUNEK WINDY
	void RuszaniePasazerow() {
		for (auto& osoba : osobywwindzie) {
			if((stan == WINDA_STOP && osoba.GetKierunek() != 'g' && osoba.GetKierunek() != 'd') || stan == WINDA_RUCH){
				osoba.Ruch();
			}
		}
		for (int i = 0; i < 5; i++) {
			for (auto& osoba : napietrach[i]) {
				if (i == pietro && stan == WINDA_STOP) osoba.Ruch();
			}
		}
	}
	void KierunekPasazerow(char k) {
		for (auto& osoba : osobywwindzie) {
			osoba.SetKierunek(k);
		}
	}
	void KierunekWindy() {
		if (kierunek_gora) {
			int max = *max_element(kolejka.begin(), kolejka.end());
			if (max == pietro) kierunek_gora = false;
		}
		else {
			int min = *min_element(kolejka.begin(), kolejka.end());
			if (min == pietro) kierunek_gora = true;
		}
	}
	//FUNKCJE REQUESTÓW
	void request(int ID) {
		int punkt_x_bazowy, modyfikator;
		int reqpietro = ID / 10;
		int reqcel = ID % 10;
		if (reqpietro % 2) {
			punkt_x_bazowy = 475;
			modyfikator = 1;
		}
		else {
			punkt_x_bazowy = 175;
			modyfikator = -1;
		}
		DodajDoKolejki(reqpietro);
		int x = punkt_x_bazowy + napietrach[reqpietro].size() * 25 * modyfikator;
		int y = (5 - reqpietro) * DLUGOSC_PIETRA - 60;

		OSOBA osoba(x, y, reqcel);
		napietrach[reqpietro].push_back(osoba);
	}
	void SortujKolejke() {
		//algorytm SCAN https://www.geeksforgeeks.org/scan-elevator-disk-scheduling-algorithms/
		std::vector<int> dol, gora;
		int head = pietro;
		bool check = false;

		for (auto req : kolejka) {
			if (req < head)
				dol.push_back(req);
			if (req > head)
				gora.push_back(req);
			if (req == head) {
				check = true;
			}
		}

		// sorting left and right vectors
		std::sort(dol.begin(), dol.end());
		std::sort(gora.begin(), gora.end());

		// run the while loop two times.
		// one by one scanning right
		// and left of the head
		kolejka.clear();
		int run = 2;
		while (run--) {
			if (!kierunek_gora) {
				for (int i = dol.size() - 1; i >= 0; i--) {
					int cur_track = dol[i];
					// appending current track to seek sequence
					kolejka.push_back(cur_track);
					// accessed track is now the new head
					head = cur_track;
				}
				kierunek_gora = true;
			}
			else if (kierunek_gora) {
				for (int i = 0; i < gora.size(); i++) {
					int cur_track = gora[i];
					// appending current track to seek sequence
					kolejka.push_back(cur_track);
					// accessed track is now new head
					head = cur_track;
				}
				kierunek_gora = false;
			}
		}
		//priorytetowy req dla osob na tym samym pietrze co winda
		if (check) kolejka.insert(kolejka.begin(), pietro);

	}
	void DodajDoKolejki(int przystanek) {
		kolejka.push_back(przystanek);
		SortujKolejke();
	}

	//FUNKCJE GET
	int getY() {
		return y;
	}
	int GetDoorOffset() {
		return drzwi;
	}
	int GetWeight() {
		return cala_waga;
	}
};
