#pragma once
using namespace std;

class Obliczenia
{
public:
	int ilosc_wszystkich_linijek;
	int ilosc_komentarzy;
	int ilosc_spacji;
	int ilosc_nawiasow;
	int ilosc_drugich_komentarzy;

	Obliczenia();
	~Obliczenia();

	void podaj_wszystkie();
	void podaj_bez_enterow();
	void podaj_bez_nawiasow();
	void podaj_bez_obu();
	void policz();
	void furtka();

};