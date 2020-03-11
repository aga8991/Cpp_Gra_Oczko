#include "Kasyno.h"
#include "Karta.h"
#include <cstdlib>
#include "Gracz.h"
#include <iomanip>
#include <fstream>
#include "Bot.h"

void Kasyno::tworzenie_graczy() {
	liczba_graczy = 0;
	liczba_botow = 0;
	do {
		std::cout << "Podaj liczbe graczy ludzkich od 1 do 3: ";
		std::cin >> liczba_graczy;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	} while (liczba_graczy < 1 || liczba_graczy > 3);

	do {
		std::cout << "Podaj liczbe graczy wirtualnych od 1 do 3: ";
		std::cin >> liczba_botow;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	} while (liczba_botow < 1 || liczba_botow > 3);
	system("cls");

	gracze = new Gracz * [liczba_graczy + liczba_botow];
	char _nazwa[20];

	for (int i = 0; i < liczba_graczy; i++) {
		std::cout << "Podaj nazwe gracza " << i + 1 << ". (dopuszczalna liczba znakow to 19): ";
		std::cin >> std::setw(20) >> _nazwa;      //zabezpieczenie przed wpisaniem za dlugiego ciagu znakow
		std::cin.clear();
		std::cin.ignore(100, '\n');
		gracze[i] = new Gracz(*this);
		gracze[i]->nazwij(_nazwa);
		system("cls");
	}

	for (int i = 0; i < liczba_botow; i++) {
		int wybor_trybu = 0;
		std::cout << "Wybierz tryb gracza wirtualnego " << i + 1 << ". :\n1.ryzykujacy\n2.normalny\n3.zachowawczy" << std::endl;
		do {
			std::cin >> wybor_trybu;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(100, '\n');
			}
		} while (wybor_trybu < 1 || wybor_trybu > 3);
		gracze[liczba_graczy + i] = new Bot(*this, wybor_trybu, i);
		system("cls");
	}
	//wygrany = new Gracz(*this);
}

void Kasyno::usuwanie_graczy()
{
	for (int i = 0; i < liczba_graczy + liczba_botow; i++) {
		if(gracze[i] == nullptr) delete gracze[i];
	}
	delete[] gracze;
	//delete wygrany;
}

Kasyno::Kasyno() {
	//tworzenie talii 52 roznych kart
	int n = 0;
	for (int i = 0; i < 13; i++) {
		for (int k = 0; k < 4; k++) {
			talia[n] = Karta(k, i);
			if(n < 52) n++;
		}
	}
	liczba_wydanych_kart = 0;
	czy_jest_juz_zwyciezca = false;
	liczba_botow = 0;
	liczba_graczy = 0;
}

void Kasyno::przetasuj() {
	int a = 0, b = 0;

	for (int i = 0; i < 100; i++) {
		a = rand() % 52;
		b = rand() % 52;
		Karta temp_karta = talia[a];
		talia[a] = talia[b];
		talia[b] = temp_karta;
	}
}

Karta* Kasyno::daj_karte() {
		liczba_wydanych_kart++;
		int a = 52 - liczba_wydanych_kart;
		if (a < 0) {
			std::cout << "Brak kart w talii. Koniec gry." << std::endl;
		}
		else return &talia[a];
}

int Kasyno::wynik_po_rozdaniu(int& _i, int& _spasowali) {
	if (gracze[_i]->jaka_wartosc_kart() == 21) {
		std::cout << "OCZKO!" << std::endl;
		gracze[_i]->automatyczny_pass();
		if (czy_jest_juz_zwyciezca == false)
		{
			wygrany = gracze[_i];
			//wygrany = new Gracz(*this);
			wygrany->nazwij(gracze[_i]->zwroc_nick());
			czy_jest_juz_zwyciezca = true;
		}
		return 1;
	} else if (gracze[_i]->jaka_wartosc_kart() > 21) {
		std::cout << "Przegrana :C" << std::endl;
		gracze[_i]->automatyczny_pass();
		return 2;
	} else {
		return 0;
	}
}

void Kasyno::wyswietl_wyniki() {
	
	//okresla zwyciezce jezeli nikt nie mial oczka

	if (czy_jest_juz_zwyciezca == false) {
		for (int i = 0; i < liczba_graczy + liczba_botow; i++) {
			if (gracze[i]->jaka_wartosc_kart() <= 21) {
				wygrany = gracze[i];
				break;
			}
			else wygrany = gracze[0];
		}

		for (int i = 0; i < liczba_graczy + liczba_botow; i++) {
			if ((gracze[i]->jaka_wartosc_kart() > wygrany->jaka_wartosc_kart()) && (gracze[i]->jaka_wartosc_kart() <= 21)) {
				wygrany = gracze[i];
			}
		}
	}

	if (wygrany->jaka_wartosc_kart() <= 21) {
		int ile_wygranych = 0; //uwzglednienie remisow
		for (int i = 0; i < liczba_graczy + liczba_botow; i++)
		{
			if (gracze[i]->jaka_wartosc_kart() == wygrany->jaka_wartosc_kart())
			{
				ile_wygranych++;
			}
		}

		if (ile_wygranych > 1)
		{		
			//wyswietlenie wygranych
			std::cout << "Wygrani to: " << std::endl;
			for (int i = 0; i < liczba_graczy + liczba_botow; i++)
			{
				if (gracze[i]->jaka_wartosc_kart() == wygrany->jaka_wartosc_kart())
				{
					std::cout << gracze[i]->zwroc_nick() << std::endl;
				}
			}
			std::cout << std::endl;
		}
		else
		{		//wyswietlanie wygranego
			std::cout << "Wygrany to " << wygrany->zwroc_nick() << std::endl <<std::endl;
		}
	} 
	else
	{
		//sytuacja bez wygranych
		std::cout << "Brak zwyciezcy. " << std::endl;
	}

	//wyswietlenie wynikow

	std::cout << "Wyniki gry w Oczko:\n\nNazwa:\t\tPunkty:\t\tKarty:";
	for (int i = 0; i < liczba_graczy + liczba_botow; i++)
	{
		std::cout << std::endl << gracze[i]->zwroc_nick() << "\t\t";
		std::cout << gracze[i]->jaka_wartosc_kart() << "\t\t";
		for (int j = 0; j < gracze[i]->ile_kart(); j++)
		{
			std::cout << gracze[i]->jaka_talia()[j].getFigura() << gracze[i]->jaka_talia()[j].getKolor() << "  ";
		}
	}
	std::cout << std::endl;
	
	std::ifstream plik_z_wynikami;
	plik_z_wynikami.open("Wyniki_Gry_w_Oczko.txt", std::ofstream::in);
	
}

void Kasyno::zapisz_wyniki() {
	std::ofstream plik_z_wynikami;
	plik_z_wynikami.open("Wyniki_Gry_w_Oczko.txt", std::ofstream::out);
	plik_z_wynikami << "Wyniki gry w Oczko:\n\nNazwa:\t\tPunkty:\t\tKarty:";
	for (int i = 0; i < liczba_graczy + liczba_botow; i++)
	{
		plik_z_wynikami << std::endl <<gracze[i]->zwroc_nick() << "\t\t";
		plik_z_wynikami << gracze[i]->jaka_wartosc_kart() << "\t\t";
		for (int j = 0; j < gracze[i]->ile_kart(); j++)
		{
			plik_z_wynikami << gracze[i]->jaka_talia()[j].getFigura() << gracze[i]->jaka_talia()[j].getKolor() << "  ";
		}
	}
	plik_z_wynikami.close();
}

void Kasyno::reset() {
	liczba_wydanych_kart = 0;
	czy_jest_juz_zwyciezca = false;
	liczba_botow;
	liczba_graczy;
	tworzenie_graczy();
}

void Kasyno::rozgrywka() {
	bool czy_chce_grac = true;
	
	while (czy_chce_grac)
	{
		reset();
		przetasuj();

		//rozdawanie dwoch kart na poczatek
		for (int i = 0; i < liczba_graczy + liczba_botow; i++) {
			for (int j = 0; j < 2; j++) {
				gracze[i]->wezKarte(daj_karte());
			}
		}

		int spasowali = 0;	//zmienna pomocnicza zeby wiedziec kiedy zakonczyc gre

		//rozgrywka - dobieranie lub pass
		do {
			for (int i = 0; i < liczba_graczy + liczba_botow; i++) {
				if (gracze[i]->czy_spasowano() == 0) {
					std::cout << gracze[i]->zwroc_nick() << ": " << std::endl;
					gracze[i]->wyswietl_posiadane_karty();
					if (!wynik_po_rozdaniu(i, spasowali)) gracze[i]->decyzja();
					if (gracze[i]->czy_spasowano() == 0) {
						gracze[i]->wezKarte(daj_karte());
						gracze[i]->wyswietl_posiadane_karty();
						wynik_po_rozdaniu(i, spasowali);
						std::cout << "\n-------------------------------------------------\n" << std::endl;
					}
				}
				else {
					spasowali++;
					std::cout << "Gracz " << gracze[i]->zwroc_nick() << " zakonczyl dobieranie." << std::endl;
				}
				system("Pause");
				system("cls");
				if (czy_jest_juz_zwyciezca == true) break;
			}
		} while (spasowali < (liczba_graczy + liczba_botow) && (czy_jest_juz_zwyciezca == false));
		system("cls");
		std::cout << "Koniec gry :)\n" << std::endl;
		wyswietl_wyniki();
		zapisz_wyniki();

		int x;
		std::cout << "\nChcesz zagrac jeszcze raz?\n1.tak\n2.nie" << std::endl;
		do {
			std::cin >> x;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(100, '\n');
			}
		} while (x != 1 && x != 2);

		if (x == 2) czy_chce_grac = false;
		usuwanie_graczy();
		system("cls");
	}
}