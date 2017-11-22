#include "stdafx.h"

#include <iostream>
#include "Magazyn.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <conio.h>

using namespace std;

void transformacja(string name) 
{
	transform(name.begin(), name.end(), name.begin(), ::tolower);
}

void Magazyn::zaladowanie_bazy()
{
	string ilosc_linijek;
	string rodzaj, nazwa, rozmiar, cena, kolor, firma, ilosc;

	fstream plik;
	plik.open("magazyn.txt", ios::in);
	if (plik.good() == false)
	{
		plik.close();
		cout << "Plik nie istnieje!" << endl;
		cout << "Czy chcesz utworzyc nowy plik magazynu [1], czy zamknac program [2] ?" << endl;
		int wybor;
		cin>>wybor;
		if (wybor < 1 || wybor>2) { cout << "Zly numer!"; getch();  cin.clear(); cin.sync(); }
		else 
		{
			if (!cin)			//sprawdzamy czy napewno wpisano liczbe
			{					//wpisano cos co nie jest liczba
				cin.clear();    //czyscimy flagi bledu strumienia
				cin.sync();     //czyscimy bufor strumienia
			}

			if (wybor == 1)
			{
				plik.open("magazyn.txt", ios::out);
				cout << "Utworzono nowy magazyn! Otworz program na nowo! " << endl;
				plik << "0";
				plik << endl;
				plik.close();



				getch();
				exit(0);
			}
			if (wybor == 2)
			{
				exit(0);
			}

		}

	}
	else {


		string wyraz;

		getline(plik, wyraz, '\n');  //pobiera ilosc linijek, pamietaj ilosc_linijek_int
		ilosc_linijek = wyraz;

		int ilosc_linijek_int; //zamiana string na int
		istringstream lol(ilosc_linijek);
		lol >> ilosc_linijek_int;

		il_lin = ilosc_linijek_int; //wczytuje ilosc linii do zawartosc klasy by moc odczytac w innym voidzie


		//rezerwujemy pamiec na tablice
		//wskaznik,nazwa tablicy=new typ_elementy[liczba]
		tablica_przedmiotow_w_magazynie = new Przedmiot[il_lin];


		for (int i = 0; i < ilosc_linijek_int; i++)  //wczytuje wszystkie linijki z atrybutami przedmiotow
		{

			getline(plik, wyraz, ','); //1 pobiera rodzaj
			rodzaj = wyraz;

			getline(plik, wyraz, ','); //2 pobiera nazwe
			nazwa = wyraz;

			getline(plik, wyraz, ','); //3 pobiera rozmiar
			rozmiar = wyraz;

			getline(plik, wyraz, ','); //4 pobiera cena, pamietaj cena_fl
			cena = wyraz;

			getline(plik, wyraz, ','); //5 pobiera kolor
			kolor = wyraz;

			getline(plik, wyraz, ','); //6 pobiera firma
			firma = wyraz;

			getline(plik, wyraz, '\n'); //7 pobiera ilosc, pamietaj ilosc_int
			ilosc = wyraz;

			float cena_fl = strtof((cena).c_str(), 0);   //zamiana stringa na float

			int ilosc_int;             //zamiana stringa na int
			istringstream iss(ilosc);
			iss >> ilosc_int;



			//tworzenie tablicy dynamicznej
			//typ elementu *nazwa_tab_dyn = 
			//tworzy wskaznik do obiektu "atrybuty przedmiotow" = obiekt,atrybuty obiekty
			Przedmiot *atrybuty_przedmiotu = new Przedmiot(rodzaj, nazwa, rozmiar, cena_fl, kolor, firma, ilosc_int);

			//ustawienie elementow tablicy na atrybuty obiektu Przedmiot
			tablica_przedmiotow_w_magazynie[i] = *atrybuty_przedmiotu;


			/* //sprawdzenie
		   cout << endl << "Rodzaj przedmiotu z tablicy[0]= "  tablica_przedmiotow_w_magazynie[0].rodzaj;
		   cout << endl << "Nazwa przedmiot z tablicy[0]= " << tablica_przedmiotow_w_magazynie[0].nazwa;

		   cout << endl << "Wyswietlanie przedmiotu: " << endl;
		   cout << "Rodzaj: " << atrybuty_przedmiotu->rodzaj << endl;
		   cout << "Cena: " << atrybuty_przedmiotu->cena << endl;
		   cout << "Rozmiar: " << atrybuty_przedmiotu->rozmiar << endl;
		   cout << "kolor: " << atrybuty_przedmiotu->kolor << endl;
		   cout << "firma: " << atrybuty_przedmiotu->firma << endl;
		   cout << "ilosc: " << atrybuty_przedmiotu->ilosc << endl;
		   cout << "ilosc: " << tablica_przedmiotow_w_magazynie[i].ilosc << endl;

		   // */

		}
		plik.close();
	}

}


void Magazyn::wypisanie_zawartosci_magazynu()
{
	if (il_lin == 0)
	{
		cout << "Magazyn jest pusty!" << endl; 
	}
	else 
	{
		for (int i = 0; i < il_lin; i++)  //wczytuje wszystkie linijki z atrybutami przedmiotow
		{
			cout << endl << i << "." << endl;
			cout << "Rodzaj:_ " << tablica_przedmiotow_w_magazynie[i].rodzaj << endl;
			cout << "Nazwa:__ " << tablica_przedmiotow_w_magazynie[i].nazwa << endl;
			cout << "Rozmiar: " << tablica_przedmiotow_w_magazynie[i].rozmiar << endl;
			cout << "Cena:___ " << tablica_przedmiotow_w_magazynie[i].cena << endl;
			cout << "Kolor:__ " << tablica_przedmiotow_w_magazynie[i].kolor << endl;
			cout << "Firma:__ " << tablica_przedmiotow_w_magazynie[i].firma << endl;
			cout << "Ilosc:__ " << tablica_przedmiotow_w_magazynie[i].ilosc << endl << endl;
		}
	}
}

void Magazyn::szukanie()
{	
	if (il_lin == 0)
	{
		cout << "Magazyn jest pusty!" << endl;
	}
	else
	{
		string szukaj;
		cout << "Wpisz czego szukasz : ";
		cin >> szukaj;
		transformacja(szukaj);
		//transform(szukaj.begin(), szukaj.end(), szukaj.begin(), ::tolower); //zamiana liter na male


		bool czyZnalazl = false; //czy znaleziono wyraz
		for (int i = 0; i < il_lin; i++)
		{
			//bede porownywal wyrazy (litery w obu slowach beda male)
			transformacja(tablica_przedmiotow_w_magazynie[i].rodzaj);
			transformacja(tablica_przedmiotow_w_magazynie[i].nazwa);
			transformacja(tablica_przedmiotow_w_magazynie[i].kolor);
			transformacja(tablica_przedmiotow_w_magazynie[i].rozmiar);

			//transform(tablica_przedmiotow_w_magazynie[i].rodzaj.begin(), tablica_przedmiotow_w_magazynie[i].rodzaj.end(), tablica_przedmiotow_w_magazynie[i].rodzaj.begin(), ::tolower);
			//transform(tablica_przedmiotow_w_magazynie[i].nazwa.begin(), tablica_przedmiotow_w_magazynie[i].nazwa.end(), tablica_przedmiotow_w_magazynie[i].nazwa.begin(), ::tolower);
			//transform(tablica_przedmiotow_w_magazynie[i].kolor.begin(), tablica_przedmiotow_w_magazynie[i].kolor.end(), tablica_przedmiotow_w_magazynie[i].kolor.begin(), ::tolower);
		//	transform(tablica_przedmiotow_w_magazynie[i].rozmiar.begin(), tablica_przedmiotow_w_magazynie[i].rozmiar.end(), tablica_przedmiotow_w_magazynie[i].rozmiar.begin(), ::tolower);


			//raczej ktos bedzie szukal tylko po rodzaju,nazwie,kolorze i firmie 
			if (tablica_przedmiotow_w_magazynie[i].rodzaj == szukaj || tablica_przedmiotow_w_magazynie[i].nazwa == szukaj || tablica_przedmiotow_w_magazynie[i].kolor == szukaj || tablica_przedmiotow_w_magazynie[i].firma == szukaj)
			{
				czyZnalazl = true;
				cout << "Nr " << i << ". " << tablica_przedmiotow_w_magazynie[i].rodzaj << "," << tablica_przedmiotow_w_magazynie[i].nazwa << "," << tablica_przedmiotow_w_magazynie[i].rozmiar << "," << tablica_przedmiotow_w_magazynie[i].kolor << "," << tablica_przedmiotow_w_magazynie[i].firma << ", Cena: " << tablica_przedmiotow_w_magazynie[i].cena << endl;
			}
		}

		if (!czyZnalazl)
		{
			cout << "Nie znaleziono!";
		}
	}
}

void Magazyn::zmiana_stanu_magazynu()
{
	if (il_lin == 0)
	{
		cout << "Magazyn jest pusty!" << endl;
	}
	else
	{
		cout << "Jakiego przedmiotu szukasz : ";
		string szukaj;
		cin >> szukaj;
		transformacja(szukaj);
		//transform(szukaj.begin(), szukaj.end(), szukaj.begin(), ::tolower);

		bool czyZnalazl = false; //czy znaleziono wyraz

		for (int i = 0; i < il_lin; i++)
		{
			transformacja(tablica_przedmiotow_w_magazynie[i].rodzaj);
			transformacja(tablica_przedmiotow_w_magazynie[i].nazwa);
			transformacja(tablica_przedmiotow_w_magazynie[i].kolor);
			transformacja(tablica_przedmiotow_w_magazynie[i].rozmiar);

		//	transform(tablica_przedmiotow_w_magazynie[i].rodzaj.begin(), tablica_przedmiotow_w_magazynie[i].rodzaj.end(), tablica_przedmiotow_w_magazynie[i].rodzaj.begin(), ::tolower);
		//	transform(tablica_przedmiotow_w_magazynie[i].nazwa.begin(), tablica_przedmiotow_w_magazynie[i].nazwa.end(), tablica_przedmiotow_w_magazynie[i].nazwa.begin(), ::tolower);
		//	transform(tablica_przedmiotow_w_magazynie[i].kolor.begin(), tablica_przedmiotow_w_magazynie[i].kolor.end(), tablica_przedmiotow_w_magazynie[i].kolor.begin(), ::tolower);
		//	transform(tablica_przedmiotow_w_magazynie[i].rozmiar.begin(), tablica_przedmiotow_w_magazynie[i].rozmiar.end(), tablica_przedmiotow_w_magazynie[i].rozmiar.begin(), ::tolower);


			if (tablica_przedmiotow_w_magazynie[i].rodzaj == szukaj || tablica_przedmiotow_w_magazynie[i].nazwa == szukaj || tablica_przedmiotow_w_magazynie[i].kolor == szukaj || tablica_przedmiotow_w_magazynie[i].firma == szukaj)
			{
				czyZnalazl = true;
				cout << "Nr " << i << ". " << tablica_przedmiotow_w_magazynie[i].rodzaj << "," << tablica_przedmiotow_w_magazynie[i].nazwa << "," << tablica_przedmiotow_w_magazynie[i].rozmiar << "," << tablica_przedmiotow_w_magazynie[i].kolor << "," << tablica_przedmiotow_w_magazynie[i].firma << ", Cena: " << tablica_przedmiotow_w_magazynie[i].cena << endl;
			}

		}

		if (!czyZnalazl)
		{
			cout << "Nie znaleziono!";
			return;
		}

		cout << endl << "Wpisz numer przedmiotu, ktory chcesz dodac/sprzedac: ";
		int numer;
		cin >> numer;
		if (numer < 0 || numer>il_lin - 1) { cout << "Zly numer!"; getch(); cin.clear(); cin.sync(); }
		else
		{
			if (!cin)			//sprawdzamy czy napewno wpisano liczbe
			{					//wpisano cos co nie jest liczba
				cin.clear();    //czyscimy flagi bledu strumienia
				cin.sync();     //czyscimy bufor strumienia
			}
			system("cls");
			cout << "Nr " << numer << ". " << tablica_przedmiotow_w_magazynie[numer].rodzaj << "," << tablica_przedmiotow_w_magazynie[numer].nazwa << "," << tablica_przedmiotow_w_magazynie[numer].rozmiar << "," << tablica_przedmiotow_w_magazynie[numer].kolor << "," << tablica_przedmiotow_w_magazynie[numer].firma << ", Cena: " << tablica_przedmiotow_w_magazynie[numer].cena << ", Ilosc: " << tablica_przedmiotow_w_magazynie[numer].ilosc << endl;

			cout << endl << "Wpisz [1]-Dodac , [2]-Sprzedac : ";
			int wybor;
			cin >> wybor;
			if (wybor < 1 || wybor>2) { cout << "Zly numer!"; getch();  cin.clear(); cin.sync(); }
			else 
			{
				if (!cin)			//sprawdzamy czy napewno wpisano liczbe
				{					//wpisano cos co nie jest liczba
					cin.clear();    //czyscimy flagi bledu strumienia
					cin.sync();     //czyscimy bufor strumienia
				}
				if (wybor == 1)
				{
					cout << "Ile przedmiotow chcesz dodac: ";
					int ile;
					cin >> ile;
					if (!cin)			//sprawdzamy czy napewno wpisano liczbe
					{					//wpisano cos co nie jest liczba
						cin.clear();    //czyscimy flagi bledu strumienia
						cin.sync();     //czyscimy bufor strumienia
					}
					tablica_przedmiotow_w_magazynie[numer].ilosc = tablica_przedmiotow_w_magazynie[numer].ilosc + ile;
					cout << "Aktualny stan: " << endl;
					cout << "Nr " << numer << ". " << tablica_przedmiotow_w_magazynie[numer].rodzaj << "," << tablica_przedmiotow_w_magazynie[numer].nazwa << "," << tablica_przedmiotow_w_magazynie[numer].rozmiar << "," << tablica_przedmiotow_w_magazynie[numer].kolor << "," << tablica_przedmiotow_w_magazynie[numer].firma << ", Cena: " << tablica_przedmiotow_w_magazynie[numer].cena << ", Ilosc: " << tablica_przedmiotow_w_magazynie[numer].ilosc << endl;

				}
				if (wybor == 2)
				{
					cout << "Ile przedmiotow chcesz sprzedac: ";
					int ile;
					cin >> ile;
					if (!cin)			//sprawdzamy czy napewno wpisano liczbe
					{					//wpisano cos co nie jest liczba
						cin.clear();    //czyscimy flagi bledu strumienia
						cin.sync();     //czyscimy bufor strumienia
					}

					//1 gdy przedmioty mozna sprzedac
					if (tablica_przedmiotow_w_magazynie[numer].ilosc > ile)
					{
						tablica_przedmiotow_w_magazynie[numer].ilosc = tablica_przedmiotow_w_magazynie[numer].ilosc - ile;
						cout << "Aktualny stan: " << endl;
						cout << "Nr " << numer << ". " << tablica_przedmiotow_w_magazynie[numer].rodzaj << "," << tablica_przedmiotow_w_magazynie[numer].nazwa << "," << tablica_przedmiotow_w_magazynie[numer].rozmiar << "," << tablica_przedmiotow_w_magazynie[numer].kolor << "," << tablica_przedmiotow_w_magazynie[numer].firma << ", Cena: " << tablica_przedmiotow_w_magazynie[numer].cena << ", Ilosc: " << tablica_przedmiotow_w_magazynie[numer].ilosc << endl;
					}

					//2 gdy przedmiotu nie mozna sprzedac
					else if (tablica_przedmiotow_w_magazynie[numer].ilosc < ile)
					{
						cout << "Chcesz sprzedac za duzo przedmiotow! Nie ma tyle w magazynie!" << endl;
					}

					//3 gdy przedmioty sie wyzeruja, usuniecie tego elementu tablicy ze wszystkimi argumentami obiektu
					else if (tablica_przedmiotow_w_magazynie[numer].ilosc == ile)
					{
						cout << "Dany przedmiot zostal usuniety z magazynu!" << endl; //ale dopiero zaraz bedzie, hue hue
						nowa_tablica_magazynu = new Przedmiot[il_lin - 1]; //tworze nowa tablice mniejsza o jeden


						for (int i = 0; i < il_lin - 1; i++)
						{
							if (numer == 0) // gdy ktos wprowadzi 0, 'i' nie obejmuje zera
								nowa_tablica_magazynu[i] = tablica_przedmiotow_w_magazynie[i + 1];
							if (i < numer)
								nowa_tablica_magazynu[i] = tablica_przedmiotow_w_magazynie[i];
							else //czyli gdy i>=numer;
								nowa_tablica_magazynu[i] = tablica_przedmiotow_w_magazynie[i + 1]; //bedzie przepisywac z jednego miejsca dalej, element dla ktorego ilosc sie wyzeruje zostanie nadpisany

						}

						delete[] tablica_przedmiotow_w_magazynie; //usuwanie starej tablicy

						tablica_przedmiotow_w_magazynie = nowa_tablica_magazynu; //ustawienie wskaznika ze starej tablica->na nowa

						il_lin = il_lin - 1;  //zmniejszenie rozmiaru magazynu

					}
				}
			}
		}
	}
}

void Magazyn::dodanie_nowego_przedmiotu()
{	

	string rodzaj, nazwa, rozmiar, kolor, firma;
	float cena;
	int ilosc;

	nowa_tablica_magazynu = new Przedmiot[il_lin+1]; //nowa tablica wieksza o jeden

	for (int i = 0; i < il_lin; i++)  //kopiuje elementy ze starej do nowej
	{
		
		nowa_tablica_magazynu[i] = tablica_przedmiotow_w_magazynie[i];
		//cout << nowa_tablica_magazynu[i].rodzaj; //sprawdzenie
		//cout << nowa_tablica_magazynu[i].cena;
	}

	cout << endl << "Dodawanie nowego przedmiotu:"<<endl;

	cout << endl << "Rodzaj przedmiotu  (Np.Spodnie,Koszulki,Akcesoria,Bielizna): ";
	cin>>rodzaj;
	
			cout<<endl<<"Nazwa przedmiotu (Np.Jeansy,Dresowe ; T-shirt,Serek  ; Zegarek,Okulary ; Majtki,Skarpetki): ";
			cin>>nazwa;

			cout<<endl<<"Rozmiar(XL,L,M,S): ";
			cin>>rozmiar;

			if(rozmiar=="XL"||rozmiar=="L"||rozmiar=="M"||rozmiar=="S"||rozmiar == "xl" || rozmiar == "l" || rozmiar == "m" || rozmiar == "s")
			{
				cout<<endl<<"Cena (uzywaj kropki, nie przecinka!) : ";
				cin>>cena;
				if(!cin)
				{				//wpisano cos co nie jest liczba
					cout << "Nie wpisano liczby!" << endl;
					cout << "Nie dodano nowego przedmiotu!" << endl;
					getch();
					cin.clear(); //czyscimy flagi bledu strumienia
					cin.sync(); //czyscimy bufor strumienia
				}

				if(cena>0)
				{
					cout<<endl<<"Kolor: ";
					cin>>kolor;
					cout<<endl<<"Firma: ";
					cin>>firma;
					cout<<endl<<"Ilosc: ";
					cin>>ilosc;
					if(!cin)
					{				//wpisano cos co nie jest liczba
						cout << "Nie wpisano liczby!" << endl;
						cout << "Nie dodano nowego przedmiotu!" << endl;
						cin.clear(); //czyscimy flagi bledu strumienia
						cin.sync(); //czyscimy bufor strumienia
					}

					if(ilosc>0)
					{
						
						Przedmiot *atrybuty_przedmiotu = new Przedmiot(rodzaj, nazwa, rozmiar, cena, kolor, firma, ilosc);
						nowa_tablica_magazynu[il_lin] = *atrybuty_przedmiotu;
						
					}
					else
					{
						cout<<"Niepoprawna ilosc";
						return;
					}
				}
				else
				{
					cout<<"Niepoprawna cena";
					return;
				}
			}
			else
			{
				cout<<"Niepoprawny rozmiar";
				return;
			}

		
		/*
		//sprawdzenie
		for (int i = 0; i < il_lin+1; i++)
		{
			cout << nowa_tablica_magazynu[i].rodzaj << endl; //sprawdzenie
			cout << nowa_tablica_magazynu[i].cena << endl;

		}
		// */
		
		delete[] tablica_przedmiotow_w_magazynie; //usuwanie starej tablicy, po usunieciu nie dziala drugie dodanie. i tak nie dodaje ale program sie nie wysypuje
		
		tablica_przedmiotow_w_magazynie = nowa_tablica_magazynu; //ustawienie wskaznika ze starej tablica->na nowa

		il_lin = il_lin + 1;  //zwiekszenie rozmiaru magazynu

		//sprawdzenie
		//cout << "Nowy rozmiar magazynu= " << il_lin << endl;
		
		


}

void Magazyn::zapisanie_powstalej_tablicy()
{
	fstream plik;
	plik.open("magazyn.txt", ios::out);
	plik << il_lin;
	plik << endl;

	for( int i=0; i<il_lin; i++)
	{
		plik << tablica_przedmiotow_w_magazynie[i].rodzaj;
		plik <<",";

		plik << tablica_przedmiotow_w_magazynie[i].nazwa;
        plik <<",";

        plik << tablica_przedmiotow_w_magazynie[i].rozmiar;
        plik <<",";

        plik << tablica_przedmiotow_w_magazynie[i].cena;
        plik << ",";

        plik << tablica_przedmiotow_w_magazynie[i].kolor;
        plik << ",";

        plik << tablica_przedmiotow_w_magazynie[i].firma;
        plik << ",";

        plik << tablica_przedmiotow_w_magazynie[i].ilosc;
		plik << endl;
	}
	plik.close();
	delete[] nowa_tablica_magazynu;
}

//konstruktor
Magazyn::Magazyn()
{
	//ilosc linijek, pierwszy wiersz z magazyn.txt

}

//destruktor
Magazyn::~Magazyn()
{
	// cout<<"Destruktor usuwa obiekt"<<endl;
}