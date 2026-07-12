#include "dane.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool odczyt(fstream& logi, Pojazd& AktualnyStan) {

	string linia;
	float przepisanie[6];

		if (getline(logi, linia)) {

			stringstream strumien(linia);			//zapisuje cala linijke z pliku az do znaku enter 
			string wartosc;

			int i = 0;
			while (getline(strumien, wartosc, ',') && i < 6) {
				przepisanie[i] = stof(wartosc);		//przepisujemy wartosci z linijek oddzielone przecinkiem do tablicy zmieniajac string na float
				i++;
			}
			AktualnyStan = Pojazd(przepisanie[0], przepisanie[1], przepisanie[2], przepisanie[3], przepisanie[4], przepisanie[5]);

			for (int i = 0; i < 6; i++) {
				cout << przepisanie[i] << endl;
			}
			return true;
		}
		else {
			return false;
		}

}

