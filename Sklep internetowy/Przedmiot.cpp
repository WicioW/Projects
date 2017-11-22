#include "stdafx.h"

#include <iostream>
#include "Przedmiot.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

//konstruktor
Przedmiot::Przedmiot(string rodz, string n, string roz, float c, string k, string f, int ilo)
{
    rodzaj=rodz;
    nazwa=n;
    rozmiar=roz;
    cena=c;
    kolor=k;
    firma=f;
    ilosc=ilo;
}


//destruktor
Przedmiot::~Przedmiot()
{
   // cout<<"Destruktor usuwa obiekt"<<endl;
}