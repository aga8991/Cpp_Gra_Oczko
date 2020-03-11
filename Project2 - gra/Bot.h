#pragma once
#include "Gracz.h"

class Kasyno;

class Bot : public Gracz
{
	int odwaga;
	int ktory_to_bot;
public:
	void nazwij();
	Bot(Kasyno& _jego_gra, int _odwaga, int _i);
	void decyzja();
};