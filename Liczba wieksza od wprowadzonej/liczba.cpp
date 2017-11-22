//wprowadzana liczba
#include "stdafx.h"
#include <iostream>
#include "liczba.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void Liczba::wpr_linii()
{	
	string sortow = "423156798";
	sort(sortow.begin(), sortow.end());
	cout << sortow;
}

void Liczba::wprowadzenie()
{
	cout << "Wpisz liczby: " << endl;

	string linia;
	cin >> linia;   //pobieramy linie
	istringstream iss(linia);  //zamieniamy na stream

	string segment;
	vector<string> lista;  //do wektora bedziemy wprowadzali dane segmenty linii

	
	while (getline(iss, segment, ',')) //liczby do przecinkow
	{
		lista.push_back(segment);
	}
	

	while (getline(iss, segment, '\n')) //pobieramy ostatnia liczbe
	{
		lista.push_back(segment);
	}
	

	vector <string> lista_wynikow; //wektor na wyniki konwersji

	for (int i = 0; i < lista.size(); i++)
	{
		//jesli juz wprowadzono te sama liczbe
		int bylo;
		bool BYLO = false;
		for (int j = 0; j < i; j++)
		{
			if (lista[i] == lista[j])
			{
				BYLO = true;
				bylo = j;
			}
		}

		string ORYGINAL = lista[i];
		string s = lista[i]; 

		int przecinek;  //sprawdzamy gdzie jest przecinek
		//cout << "przecinek jest: ";
		bool istnienie = false;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '.') {
				przecinek = i;
				istnienie = true;
			}
		}
		//cout << przecinek << endl;

		if (BYLO == true)
		 {
		 	//cout << "powtorzenie" << endl;
			lista_wynikow.push_back(lista_wynikow[bylo]);
		 }

		else if (istnienie == false) //jesli liczba to int, wyglada tak: 123
		{
			for (int i = 0; i < s.size(); i++)
			{
				if (s[i] < s[i + 1])
				{
					swap(s[i], s[i + 1]);
				}
			}
			lista_wynikow.push_back(s);
		}
		else {  //jesli liczba to float, wyglada tak: 123.321

			//zamiana miejsc cyfr do przecinka, zostawiac przecinek tam gdzie jest

			for (int i = 0; i < przecinek; i++)
			{
				if (s[i] < s[i + 1])
				{
					swap(s[i], s[i + 1]);
				}
			}
			string PIERWSZA_KONWERSJA = s;
			//cout << "1: " << s << endl;

			for (int i = przecinek + 1; i < s.size(); i++) //jesli cyfry przed przecinkiem sa rowne:33.123
			{
				if (s[i] < s[i + 1])
				{
					swap(s[i], s[i + 1]);
				}
			}
			string DRUGA_KONWERSJA = s;
			//cout << "2: " << s << endl;

			//jesli wszystkie cyfry sa takie same to zmieniamy miejsce przecinka: 33.33
			swap(s[przecinek], s[przecinek + 1]);
			

			string TRZECIA_KONWERSJA = s;
			//cout << "3: " << s << endl;


			if (PIERWSZA_KONWERSJA == ORYGINAL)
			{
				if (DRUGA_KONWERSJA == ORYGINAL)
				{
					lista_wynikow.push_back(TRZECIA_KONWERSJA);
					//cout << TRZECIA_KONWERSJA << endl;
				}
				else
				{
					lista_wynikow.push_back(DRUGA_KONWERSJA);
					//cout << DRUGA_KONWERSJA << endl;
				}
			}
			else
			{
				lista_wynikow.push_back(PIERWSZA_KONWERSJA);
				//cout << PIERWSZA_KONWERSJA << endl;
			}
		}
	}

	cout << "WYNIKI: " << endl;
	for (int i = 0; i < lista_wynikow.size(); i++)
	{
		cout << lista_wynikow[i] << endl;
	}
}



//konstruktor
Liczba::Liczba()
{
	;
}

//destruktor
Liczba::~Liczba()
{
	;
}