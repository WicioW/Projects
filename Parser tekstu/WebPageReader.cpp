#include "stdafx.h"
#include "WebPageReader.h"

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "windows.h"
#include "Winhttp.h"

#include <vector>


#pragma comment(lib, "winhttp.lib")

using namespace std;

void WebPageReader::read()
{
	cout << "WEBPAGE READER - szukanie" << endl << endl;
	
	string source = "error";
	bool secure = false;
	const wchar_t *url = L"www.stackoverflow.com";
	const wchar_t *verb = L"questions/29547368";

	BOOL bResults = FALSE;

	HINTERNET hsession = NULL;
	HINTERNET hconnect = NULL;
	HINTERNET hrequest = NULL;

	hsession = WinHttpOpen(L"Example", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (!hsession) goto error;

	hconnect = WinHttpConnect(hsession, url, secure ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, 0);
	if (!hconnect) goto error;

	hrequest = WinHttpOpenRequest(hconnect, L"GET", verb, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, secure ? WINHTTP_FLAG_SECURE : 0);
	if (!hrequest) goto error;

	if (!WinHttpSendRequest(hrequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
		goto error;

	if (!WinHttpReceiveResponse(hrequest, NULL))
		goto error;

	source = "";

	for (DWORD size = 1, downloaded = 1; downloaded > 0;)
	{
		WinHttpQueryDataAvailable(hrequest, &size);
		if (!size) break;
		std::string buf(size + 1, 0);
		WinHttpReadData(hrequest, (LPVOID)&buf[0], size, &downloaded);
		buf.resize(downloaded);
		source += buf;
	}

error:
	if (hrequest) WinHttpCloseHandle(hrequest);
	if (hconnect) WinHttpCloseHandle(hconnect);
	if (hsession) WinHttpCloseHandle(hsession);

	//cout << source; //sprawdzenie
	//	std::ofstream f("c:\\temp\\test.txt"); //do pliku
	//f << src;

	int no_of_links = 0;
	string search1 = "<a href=\""; //mozna zachowac cudzyslow w stringu uzywajac backslasha
	string search2 = "</a>";
	//string search2 = "\""; //jesli chcemy "link", a nie "link"bzdury</a>


	//funkcja jak w FileReader
	size_t tmp = 0;
	while (string::npos != (tmp = source.find(search1, tmp))) //lub while (line.find(search1, tmp) != -1) //robia to samo
	{
		size_t position1 = source.find(search1, tmp);
		tmp = source.find(search1, tmp) + 9; //+9 by ominelo ca³e "<a href=\""

		if (source.find(search2, tmp) != string::npos)
		{
			size_t position2 = source.find(search2, tmp); 
			tmp = source.find(search2, tmp) + 1; //+1 pasuje do obu wersji,czy wypisuje link do cudzyslowa czy do </a>
			string link = source.substr(position1 + 8, position2 - position1 -8 ); //pos1+8 ominac <a href=; a po2-pos1-8 by byla poprawna dlugosc wydobytego substringa

			vector_with_links.push_back(link);
			no_of_links++;
		}
	}
	tmp = 0;

	number_of_links = no_of_links;

}


void WebPageReader::show_number_of_links()
{
	cout << "Ilosc linkow: " << number_of_links << endl;

}

void WebPageReader::show_all_links()
{
	for (int i = 0; i < vector_with_links.size(); i++)
	{
		cout << i + 1 << ". " << vector_with_links[i] << endl << endl;
	}
}

WebPageReader::WebPageReader()
{
}


WebPageReader::~WebPageReader()
{
}
