#include <iostream>
#include "Karta.h"
#include "Gracz.h"
#include "Kasyno.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	Kasyno kasyno;
	kasyno.rozgrywka();
	system("PAUSE");
}
