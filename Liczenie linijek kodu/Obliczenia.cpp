#include "stdafx.h"
#include "Obliczenia.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <vector>



using namespace std;

void Obliczenia::policz()
{
	fstream plik;
	plik.open("kodzik.txt", ios::in);
	if (plik.good() == false)
	{
		plik.close();
		cout << "Plik nie istnieje! " << endl;
		getchar(); getchar();
		exit(0);
	}

	int il = 1; //linijka zaczyna sie od 1, nie od 0
	int il_kom = 0;
	int il_spac = 0;
	int il_naw = 0;
	string linijka;

	vector <int> rozp_kom; //wektor przechow. nr linijki gdzie komentarz sie rozpoczal
	vector <int> kon_kom; //gdzie sie konczy
	bool szukaj_poczatku = true;
	bool szukaj_konca = false;

	while (getline(plik, linijka))
	{
		//cout << il <<linijka<< endl; //sprawdzenie numerowania linijek
		string sz1 = "//";
		string sz2 = "/*";
		string sz3 = "*/";
		string sz4 = "{";
		string sz5 = "}";

		if (linijka.find(sz1) != string::npos) //znajduje wszystkie komentarze
		{
			size_t pozycja = linijka.find('/'); //znajduje gdzie jest komentarz w linijce

			bool jest_tekst_przed_komentarzem = false;
			for (int i = 0; i < pozycja; i++)
			{
				if (linijka[i] != ' ') { jest_tekst_przed_komentarzem = true; } //sprawdza czy jest cos procz spacji przed komentarzem
			}
			if (jest_tekst_przed_komentarzem == false) { il_kom++; } //jesli sa tylko spacje to zwieksza ilosc kom
		}
		if (all_of(linijka.begin(), linijka.end(), isspace) == true) { il_spac++; } //cout << linijka << endl; } //zlicza linijki z samymi spacjami

		if (linijka.find(sz4) != string::npos) //znajduje '{'
		{
			size_t pozycja1 = linijka.find('{'); //znajduje gdzie jest { w linijce

			bool jest_tekst_przed = false;
			bool jest_tekst_za = false;

			for (int i = 0; i < pozycja1; i++)
			{
				if ((linijka[i] != ' ') && (linijka[i] != '	')) { jest_tekst_przed = true; } //sprawdza czy jest cos procz spacji przed komentarzem
			}
			for (int i = pozycja1 + 1; i < linijka.size(); i++)
			{
				if ((linijka[i] != ' ') && (linijka[i] != '	')) { jest_tekst_za = true; } //sprawdza czy jest cos procz spacji przed komentarzem
			}
			if (jest_tekst_przed == false && jest_tekst_za == false) { il_naw++; } //jesli sa tylko spacje to zwieksza ilosc kom
		}

		if ((linijka.find(sz5) != string::npos)) //znajduje '}'
		{
			size_t pozycja2 = linijka.find('}'); //znajduje gdzie jest } w linijce

			bool jest_tekst_przed = false;
			bool jest_tekst_za = false;

			for (int i = 0; i < pozycja2; i++)
			{
				if ((linijka[i] != ' ') && (linijka[i] != '	')) { jest_tekst_przed = true; } //sprawdza czy jest cos procz spacji przed komentarzem
			}
			for (int i = pozycja2 + 1; i < linijka.size(); i++)
			{
				if ((linijka[i] != ' ') && (linijka[i] != '	')) { jest_tekst_za = true; } //sprawdza czy jest cos procz spacji przed komentarzem
			}
			if (jest_tekst_przed == false && jest_tekst_za == false) { il_naw++; } //jesli sa tylko spacje to zwieksza ilosc kom
		}

		if (linijka.find(sz2) != string::npos) //znajdzie poczatek komentarza /*
		{	
			if (szukaj_poczatku == true)
			{
				szukaj_konca = true;
				szukaj_poczatku = false;
		//		cout << linijka << endl;
				rozp_kom.push_back(il); //dodaje do wektora nr linijki,gdzie znaleziono
			}
		}
		
		
		if (linijka.find(sz3) != string::npos) //szuka zakonczenia,dodaje nr linijki
		{
			if (szukaj_konca == true)
			{
				szukaj_poczatku = true;
				szukaj_konca = false;
		//		cout << linijka << endl;
				kon_kom.push_back(il);
			}
		}

	 	il++; //zlicza ilosc wszystkich linijek	
	 }
	 
  	// cout << rozp_kom[0] << "," << kon_kom[0] <<","<<rozp_kom.size()<< endl;
	// cout << rozp_kom[1] << "," << kon_kom[1] << endl;
	 int il_drug_kom = 0;
	
	 for (int i = rozp_kom.size()-1; i >= 0; i--)
	 {
	 	il_drug_kom +=( (kon_kom[i]+1) - rozp_kom[i]);	
	 }
	//cout << il_drug_kom << endl;

	ilosc_wszystkich_linijek = il-1;
	ilosc_komentarzy = il_kom;
	ilosc_spacji = il_spac;
	ilosc_nawiasow = il_naw;
	ilosc_drugich_komentarzy = il_drug_kom;
	plik.close();
	//cout << "Wszystkie: " << ilosc_wszystkich_linijek << endl;
}

void Obliczenia::podaj_wszystkie()
{
	cout << "Ilosc wszystkich linijek: " << ilosc_wszystkich_linijek - ilosc_komentarzy - ilosc_drugich_komentarzy << endl;
}

void Obliczenia::podaj_bez_enterow()
{
	cout << "Ilosc linijek bez enterow: " << ilosc_wszystkich_linijek - ilosc_komentarzy - ilosc_drugich_komentarzy - ilosc_spacji << endl;
}

void Obliczenia::podaj_bez_nawiasow()
{
	cout << "Ilosc linijek bez nawiasow: "<< ilosc_wszystkich_linijek - ilosc_komentarzy - ilosc_drugich_komentarzy - ilosc_nawiasow<<endl;
}

void Obliczenia::podaj_bez_obu()
{
	cout << "Ilosc linijek bez nawiasow i enterow: "<< ilosc_wszystkich_linijek - ilosc_komentarzy - ilosc_drugich_komentarzy - ilosc_nawiasow - ilosc_spacji<<endl;
}


void Obliczenia::furtka()
{
	cout << "Wszystkie: " << ilosc_wszystkich_linijek << endl;
	cout << "Komentarze //: " << ilosc_komentarzy << endl;
	cout << "Spacje(same entery): " << ilosc_spacji << endl;
	cout << "Nawiasy: " << ilosc_nawiasow << endl;
	cout << "Komentarze /**/: " << ilosc_drugich_komentarzy << endl;
}

Obliczenia::Obliczenia()
{
	;
}

Obliczenia::~Obliczenia()
{
	;
}