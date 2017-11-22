// ConsoleApplication1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include "Przedmiot.h"
#include "Magazyn.h"

Magazyn mag; //utworzenie magazynu

using namespace std;

int main()
{
	
	mag.zaladowanie_bazy();  //otworzenie pliku i zaladowanie magazynu z .txt

	for (;;)
	{  //MENU

		cout << "Sklep internetowy" << endl << endl;
		cout << "Co chcesz zrobic?" << endl;
		cout << "1. Sprawdz co jest na magazynie" << endl;
		cout << "2. Znalezc cos w magazynie" << endl;
		cout << "3. Sprzedac/Dodac przedmiot bedacy w magazynie" << endl;
		cout << "4. Dodac nowy przedmiot do magazynu" << endl;
		cout << "5. Koniec" << endl;
		
		//wybor z menu
		int wybor;
		cin >> wybor;

		if (!cin)			//sprawdzamy czy napewno wpisano liczbe
		{					//wpisano cos co nie jest liczba
			//cout << "Nie wpisano numeru!" << endl;
			cin.clear();    //czyscimy flagi bledu strumienia
			cin.sync();     //czyscimy bufor strumienia
		}
	
			switch (wybor)
			{
				case 1: { mag.wypisanie_zawartosci_magazynu();        break; }
				case 2: { mag.szukanie();							  break; }
				case 3: { mag.zmiana_stanu_magazynu();				  break; }
				case 4: { mag.dodanie_nowego_przedmiotu();			  break; }
				case 5: { mag.zapisanie_powstalej_tablicy(); exit(0); break; }

				default: { cout << "Wybrano zly numer!" << endl; getch(); }
			}
			
			getchar(); getchar();			//czekamy na enter
			system("cls");				    //czysci ekran czyli wypisuje menu ponownie
		
	}
	return 0;

}



