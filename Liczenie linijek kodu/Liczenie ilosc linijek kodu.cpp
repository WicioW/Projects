// zad3,liczenie linijek kodu.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include "Obliczenia.h"
#include <cstdlib>

using namespace std;


int main()
{
	Obliczenia o;
	o.policz();
	
	for (;;)
	{
		cout << "Program liczacy linie kodu programu." << endl;
		cout << "Linie kodu komentarzy sa NIE liczone." << endl<<endl;
		cout << "Wybierz (wprowadz numer): " << endl;
		cout << "1. Podaj ilosc WSZYSTKICH linii kodu" << endl;
		cout << "2. Podaj ilosc,pomin entery" << endl;
		cout << "3. Podaj ilosc,pomin nawiasy" << endl;
		cout << "4. Podaj ilosc,pomin entery i nawiasy" << endl;
		cout << "5. Zamknij" << endl << endl;
		cout << "WYBOR: ";

		int wybor;
		cin >> wybor;
		cout << endl;

		if (!cin)
		{
			cin.clear();
			cin.sync();
		}
		
		switch (wybor)
		{
		case 1: o.podaj_wszystkie(); break; //ostatecznie ma byc  case 1: o.podaj_wszystkie();
		case 2: o.podaj_bez_enterow(); break;
		case 3: o.podaj_bez_nawiasow(); break;
		case 4: o.podaj_bez_obu(); break;
		case 5: exit(0); break;
		case 6: o.furtka(); break;
		default: cout << "Wybrano zly numer!" << endl; getchar();
		}
		getchar(); getchar();
		system("cls");
	}
    return 0;
}

