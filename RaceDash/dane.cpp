#include <windows.h>
#include "dane.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//SAMODZIELNE WYBRANIE PLIKU
string wybierz_plik() {
	OPENFILENAMEA window_settings;			//TWORZENIE STRUKTURY Z USTAWIENIAMI OKNA
	char file_name[260] = { 0 };			//REZERWUJEMY MIEJSCE NA SCIEZKE DO PLIKU

	ZeroMemory(&window_settings, sizeof(OPENFILENAME));				//ZERUJEMY PAMIEC 

	window_settings.lStructSize = sizeof(OPENFILENAME);				//OKRESLAMY WIELKOSC STRUKTURY
	window_settings.hwndOwner = NULL;								//WLASCICIEL OKNA
	window_settings.lpstrFile = file_name;							//ZAPISUJEMY SCIEZKE DO PLIKU
	window_settings.nMaxFile = sizeof(file_name);					//OKRESLAMY MAKSYMALNA DLUGOSC SCIEZKI
	window_settings.lpstrFilter = "Pliki CSV\0*.csv\0Wszystkie pliki\0*.*\0";		//LISTA Z TYPAMI DO WYBORU
	window_settings.nFilterIndex = 1;								//PODSTAWOWO FILTOREWANIE NA PLIKOW CSV
	window_settings.lpstrFileTitle = NULL;							//IGNORUJEMY SKROCENIE SCIEZKI PLIKU DO SAMEJ NAZWY, BIERZENY CALA SCIEZKE DO PLIKU
	window_settings.nMaxFileTitle = 0;								//
	window_settings.lpstrInitialDir = NULL;							//OTWIERA OKIENKO W OSTATNIO UZYWANYM KATALOGU
	window_settings.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;		//REGULY WYBRANIA PLIKU

	if (GetOpenFileNameA(&window_settings) == true) {
		return string(window_settings.lpstrFile);

	}
	else { return "logi.csv"; }

}

//-----------------------------------------------------------------------------------------ODCZYTYWANIE PLIKU
bool odczyt(fstream& logi, Pojazd& AktualnyStan) {

	string linia;
	float przepisanie[9];

		if (getline(logi, linia)) {

			stringstream strumien(linia);			//zapisuje cala linijke z pliku az do znaku enter 
			string wartosc;

			int i = 0;
			while (getline(strumien, wartosc, ',') && i < 9) {
				przepisanie[i] = stof(wartosc);		//przepisujemy wartosci z linijek oddzielone przecinkiem do tablicy zmieniajac string na float
				i++;
			}
			AktualnyStan = Pojazd(przepisanie[0], przepisanie[1], przepisanie[2], przepisanie[3], przepisanie[4], przepisanie[5], przepisanie[6], przepisanie[7], przepisanie[8]);

			//for (int i = 0; i < 7; i++) {
				//cout << przepisanie[i] << endl;
			//}
			return true;
		}
		else {
			return false;
		}

}

