#include "Gracz.h"
#include "Kasyno.h"
#include <iostream>
#include <string.h>

void Gracz::nazwij(char* _nazwa)
{
	strcpy_s(nazwa, _nazwa);
}

Gracz::Gracz(Kasyno& _jegoGra) 
{
	ilosc_kart = 0;
	wartosc_kart = 0;
	talia_gracza = nullptr;
	pass = 0;
}

Gracz::~Gracz() {
	if (talia_gracza != nullptr) delete[] talia_gracza;
}

int Gracz::ile_kart() {
	return ilosc_kart;
}

int Gracz::jaka_wartosc_kart() {
	return wartosc_kart;
}

Karta* Gracz::jaka_talia()
{
	return talia_gracza;
}

void Gracz::wezKarte(Karta * _karta) {
	ilosc_kart++;
	wartosc_kart += _karta->getWartosc();

	Karta *talia_temp = nullptr;

	if (talia_gracza != nullptr) {
		talia_temp = talia_gracza;
		talia_gracza = new Karta[ilosc_kart];
		for (int i = 0; i < ilosc_kart - 1; i++) {
			talia_gracza[i] = talia_temp[i]; 
		}
		talia_gracza[ilosc_kart - 1] = *_karta;
		delete[] talia_temp;
	}
	else {
		talia_gracza = new Karta[ilosc_kart];
		talia_gracza[ilosc_kart - 1] = *_karta;
	}
}

void Gracz::wyswietl_posiadane_karty() {
	if (ilosc_kart != 0) {
		std::cout << "Karty gracza: " << std::endl;
		for (int i = 0; i < ilosc_kart; i++) {
			std::cout << talia_gracza[i].getFigura() << "\t" << talia_gracza[i].getKolor() << "\t" << talia_gracza[i].getWartosc() << std::endl;
		}
		std::cout << "Wartosc wszystkich kart: " << wartosc_kart << std::endl;
	}
	else {
		std::cout << "Gracz nie posiada zadnych kart. " << std::endl;
	}
}

void Gracz::decyzja() {
	int _decyzja;
	std::cout << "Dezycja:\n1. Dobieram\n2. Pasuje" << std::endl;
	do {
		std::cin >> _decyzja;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		if (_decyzja == 2) pass = 1;
		else pass = 0;
		
	} while (_decyzja != 1 && _decyzja != 2);
}

void Gracz::automatyczny_pass()
{
	pass = 1;
}

void Gracz::reset()
{
	ilosc_kart = 0;
	wartosc_kart = 0;
	if (talia_gracza != nullptr) delete[] talia_gracza;
	talia_gracza = nullptr;
	pass = 0;
}

bool Gracz::czy_spasowano() {
	if (pass == 1) return 1;
	else return 0;
}

char* Gracz::zwroc_nick()
{
	return nazwa;
}