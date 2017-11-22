// Parser tekstu,czyt. linkow ze stron int.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "AbstractReader.h"
#include "FileReader.h"
#include "WebPageReader.h"

#include <iostream>
#include <conio.h>
#include <string>


using namespace std;

int main()
{
	FileReader file;
	WebPageReader web;

//	AbstractReader *ptr_file = &file, *ptr_web = &web;

	cout << "Parser do odczytywania linkow" << endl;
	cout << "ze stron zapisanych w pliku lub adresu URL" << endl << endl;
	cout << "Wybierz: " << endl;
	cout << "1. Otworz plik." << endl;
	cout << "2. Otworz adres URL." << endl;

	
	int wybor;
	cin >> wybor;
	
	if (!cin)
	{
		cin.clear();
		cin.sync();
	}
	
	switch (wybor)
	{
		case 1: file.read(); file.show_number_of_links();
				int wybor2;
				cout << "Chcesz zobaczyc wszystkie linki? [1]-Tak, [2]-Nie : ";
				cin >> wybor2;
				if (wybor2 == 1) file.show_all_links();
				else return 0;
				break;

		case 2: web.read(); web.show_number_of_links(); 
				int wybor3;
				cout << "Chcesz zobaczyc wszystkie linki? [1]-Tak, [2]-Nie : ";
				cin >> wybor3;
				if (wybor3 == 1) web.show_all_links();
				else return 0;
				break;

		case 3: exit(0); break;

		default: cout << "Wybrano zly numer!" << endl; getchar();
	}
	
	//ptr_file->read();
	//ptr_web->read();

	getch(); getch();
	system("cls");

    return 0;
}

