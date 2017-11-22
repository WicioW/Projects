#include "stdafx.h"
#include "FileReader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void FileReader::read()
{
	cout << endl << "FILE READER - szukanie" << endl << endl;

	fstream plik;
	plik.open("plik.txt", ios::in);
	if (plik.good() == false)
	{
		plik.close();
		cout << "Plik nie istnieje!" << endl;
		getchar(); getchar();
		exit(0);
	}

	int no_of_links = 0;
	string line;
	string search1 = "<a href=\""; //mozna zachowac cudzyslow w stringu uzywajac backslasha
	string search2 = "</a>";
	// string search2 = "\""; //gdy bede chcial same linki "link"

	//przyk³ad linku w html
	//<a href="https://www.w3schools.com/html/">Visit our HTML tutorial</a>

	while (getline(plik, line))   //pobieram linijke
	{	
		
		//3 wersja
		size_t tmp = 0;
		while (string::npos != (tmp = line.find(search1, tmp))) //lub while (line.find(search1, tmp) != -1) //robia to samo
		{
			size_t position1 = line.find(search1, tmp);
			tmp = line.find(search1, tmp) + 9; //+9 by ominelo ca³e "<a href=\""

			if (line.find(search2, tmp) != string::npos)
			{
				size_t position2 = line.find(search2, tmp);
				tmp = line.find(search2, tmp) + 1; //+1 pasuje do obu wersji,czy wypisuje link do cudzyslowa czy do </a>
				string link = line.substr(position1+8 , position2 - position1-8);

				vector_with_links.push_back(link);
				no_of_links++;
			}
		}
		tmp = 0;
		

		
		/*
		//2 wersja 
		size_t tmp = 0;
		size_t tmp2 = 0;

		while (line.find(search1, tmp) != -1) //gdy znajdzie
		{
			size_t position1 = line.find(search1, tmp);
			tmp = line.find(search1, tmp) + 1; //nie moze byc = position+1; ? 

			if (line.find(search2, tmp2) != string::npos)
			{
				size_t position2 = line.find(search2, tmp2);
				tmp2 = line.find(search2, tmp2) + 1;
				
				string link = line.substr(position1, position2-position1+4); //subst(poczatek,ile znakow)
				vector_with_links.push_back(link);
				no_of_links++;
			}
		}
		tmp = 0;
		tmp2 = 0;
		*/

		// 1st - pierwsza wersja
		// string::size_type start_pos = 0; //znajduje wszystkie pojawienia sie w linijce
		// //while (string::npos != (start_pos = line.find(s, start_pos)))
		// {
		// 	cout << "linia: " << numer_linii << "  poz: " << start_pos << endl;
		// 	++start_pos;
		// }
	}

	number_of_links = no_of_links;

	plik.close();
}

void FileReader::show_number_of_links()
{
	cout << "Ilosc linkow: " << number_of_links << endl;
}

void FileReader::show_all_links()
{
	for (int i = 0; i < vector_with_links.size(); i++)
	{
		cout << i +1 << ". " << vector_with_links[i] << endl << endl;
	}
}

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
}
