#pragma once
#include "Przedmiot.h"
using namespace std;


class Magazyn
{
public:
	
	int il_lin; //ilosc linii w txt = rozmiar magazynu

	Przedmiot *tablica_przedmiotow_w_magazynie;
	Przedmiot *nowa_tablica_magazynu; 


	Magazyn();
	~Magazyn();

	void zaladowanie_bazy();
	void wypisanie_zawartosci_magazynu();
	void szukanie();
	void zmiana_stanu_magazynu();
	void dodanie_nowego_przedmiotu();
	void zapisanie_powstalej_tablicy();

};