#include "Bot.h"
#include "Gracz.h"
#include <string>
#include <cstring>
#include <iostream>

std::string nazwy_dla_botow[] = { "bot1","bot2","bot3" };

void Bot::nazwij()
{
	char nazwa_bota[5];
	strcpy_s(nazwa_bota, nazwy_dla_botow[ktory_to_bot].c_str());
	for (int i = 0; i < 5; i++)
	{
		nazwa[i] = nazwa_bota[i];
	}
}

Bot::Bot(Kasyno& _jego_gra, int _odwaga, int _i)
	:Gracz(_jego_gra)
	, ktory_to_bot(_i)
	, odwaga(_odwaga)
{
	nazwij();
}

void Bot::decyzja()
{
	if (odwaga == 1) //ryzykujacy
	{
		if (wartosc_kart >= 20) pass = 1;
	}
	else if (odwaga == 2) //normalny
	{
		if (wartosc_kart >= 18) pass = 1;
	}
	else if (odwaga == 3) //zachowawczy
	{
		if (wartosc_kart >= 16) pass = 1;
	}
}