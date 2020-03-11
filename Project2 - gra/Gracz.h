#pragma once
#include "Karta.h"
class Kasyno;

class Gracz
{
protected:
	char nazwa[20];
	Karta *talia_gracza;
	int ilosc_kart;
	int wartosc_kart;
	bool pass;

public:
	void nazwij(char *_nazwa);
	Gracz(Kasyno& _jegoGra);
	~Gracz();
	int ile_kart();
	int jaka_wartosc_kart();
	Karta* jaka_talia();
	void wezKarte(Karta * _karta);
	void wyswietl_posiadane_karty();
	virtual void decyzja();
	void automatyczny_pass();
	void reset();
	bool czy_spasowano();
	char* zwroc_nick();
};