#pragma once
#include <iostream>

using namespace std;


class Przedmiot
{
public:
	string rodzaj; //Spodnie,koszulka,akcesoria/bielizna
	string nazwa;  //jeansy,dresowe ; t-shirt,ser  ; zegarek,okulary ; majtki,skarpetki
	string rozmiar; //XL, L, M, S
	float  cena;
	string kolor;
	string firma;
	int    ilosc;

	Przedmiot(string = "rodzaj.h", string = "nazwa.h", string = "rozmiar.h", float = 0, string = "kolor.h", string = "firma.h", int = 0);
	~Przedmiot();

	friend class Magazyn; //klasa Magazyn ma dostep do atrybutów klasy Przedmiot
};