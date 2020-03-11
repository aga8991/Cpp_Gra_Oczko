#pragma once
#include "Karta.h"
#include "Gracz.h"

class Kasyno
{
	Karta talia[52];
	int liczba_graczy;
	int liczba_botow;
	Gracz **gracze;
	int liczba_wydanych_kart;
	Gracz *wygrany;
	bool czy_jest_juz_zwyciezca;

public:
	void tworzenie_graczy();
	void usuwanie_graczy();
	Kasyno();
	void przetasuj();
	Karta* daj_karte();
	int wynik_po_rozdaniu(int& _i, int& _spasowali);
	void wyswietl_wyniki();
	void zapisz_wyniki();
	void reset();
	void rozgrywka();
};
