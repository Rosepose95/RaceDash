#include <iostream>
#include <functional>
#include "wyswietlanie.h"
using namespace std;

//WYSWIETLANIE NAPISOW ORAZ OKREGU JAKO OBRAMOWANIE
Wyswietlanie::Wyswietlanie(): tekst(czcionka){					
		
	if (czcionka.openFromFile("font/Gameplay.ttf") == false) {    
 		cout << "Blad we wczytywaniu czcionki!!!" << endl;
		return;
	}
}

//USTAWIANIE WARTOSCI DLA PROSTOKATA
void Wyswietlanie::aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position) {
	prostokat.setSize(SetSize);					
	prostokat.setFillColor(FillColor);
	prostokat.setOutlineColor(OutlineColor);
	prostokat.setOutlineThickness(Thickness);
	prostokat.setOrigin(Origin);
	prostokat.setPosition(Position);
}

//USTAWIANIE WARTOSCI DLA TEKSTU
void Wyswietlanie::aktualizuj_tekst(int CharacterSize, sf::Color TextColor, sf::Vector2f Position) {

	tekst.setCharacterSize(CharacterSize);								
	tekst.setFillColor(TextColor);
	sf::FloatRect wymiary = tekst.getLocalBounds();			
	tekst.setOrigin(sf::Vector2f((wymiary.position.x + wymiary.size.x) / 2.0, (wymiary.position.y + wymiary.size.y) / 2.0));
	tekst.setPosition(Position);
}

//WPISYWANIE TEKSTU DO ZMIENNEJ
void Wyswietlanie::aktualizuj_string(float wartosc) {
	
	int metoda = static_cast<int>(wartosc);
	tekst.setString(to_string(metoda));
}

//ZMIANA KOLORU OBRAMOWKI OD WARTOISC PREDKOSCI, OBROTOW ITD
void Wyswietlanie::zmiana_koloru_obramowki(sf::Color kolor) {

	prostokat.setOutlineColor(kolor);

}

//PLYNNA ZMIANA KOLORU
void Wyswietlanie::plynna_zmiana_koloru(float wartosc, float maxwartosc, float minwartosc, sf::Color start, sf::Color koniec) {

	if (wartosc <= minwartosc) {
		prostokat.setOutlineColor(start);
		return;
	}
	if (wartosc >= maxwartosc) {
		prostokat.setOutlineColor(koniec);
		return;
	}

	float procent = (wartosc - minwartosc) / (maxwartosc - minwartosc);

	int r = start.r + (koniec.r - start.r) * procent;
	int g = start.g + (koniec.g - start.g) * procent;
	int b = start.b + (koniec.b - start.b) * procent;

	prostokat.setOutlineColor(sf::Color(r, g, b));
}

//RYSOWANIE WSZYSTKIEGO ORAZ AKTUALIZACJA WARTOSCI STRINGA
void Wyswietlanie::rysuj(sf::RenderWindow& window, Wyswietlanie& obiekt, float wartosc){

	obiekt.aktualizuj_string(wartosc);

	window.draw(prostokat);
	window.draw(tekst);
}


//--------------------------------------------------------------------------------------------------------


//LADOWANIE I WYSWIETLANIE GRAFIK

Ladowanie_grafik::Ladowanie_grafik():  obraz(sf::Vector2u(1,1)), tekstura(sf::Vector2u(1,1)), lokalizacja(tekstura) {}

 //ZALADOWANIE GRAFIKI
void Ladowanie_grafik::aktualizuj_grafike(std::string zdjecie, sf::Vector2f pozycja){
	
	if (obraz.loadFromFile(zdjecie) == false) {
		cout << "Blad ladowania zdjecia!!!";
		return;
	}
	tekstura.loadFromImage(obraz);
	tekstura.setSmooth(true);
	lokalizacja.setTexture(tekstura, true);

	sf::FloatRect wymiar = lokalizacja.getLocalBounds();
	lokalizacja.setOrigin(sf::Vector2f((wymiar.position.x + wymiar.size.x) / 2.0, (wymiar.position.y + wymiar.size.y) / 2.0));
	lokalizacja.setPosition(pozycja);
}

//AKTUALIZOWSANIE WARTOSCI KATOW DLA WSKAZOWKI
void Ladowanie_grafik::aktualizuj_katy(float maxw, float minw, float ks, float kk) {
	maxwartosc = maxw;
	minwartosc = minw;
	katstartowy = ks;
	katkoncowy = kk;
}

//WYLICZAMY KAT DLA WSKAZNIKA
void Ladowanie_grafik::wyliczanie_kata(float wartosc) {

	if (wartosc > maxwartosc) {
		wartosc = maxwartosc;
	}
	if (wartosc < 0) {
		wartosc = 0;
	}
	if (minwartosc < 0) {
		minwartosc = 0;
	}

	float procent = (wartosc - minwartosc) / (maxwartosc - minwartosc);
	float aktualnykat = katstartowy + procent * (katkoncowy - katstartowy);

	lokalizacja.setRotation(sf::degrees(aktualnykat));
}

//ZMIANA SKALI GRAFIKI
void Ladowanie_grafik::zmiana_wielkosc(float skala) {
	lokalizacja.setScale(sf::Vector2f(skala,skala));
}

//SRODEK OBROTU DLA WKSAZNIKA
void Ladowanie_grafik::ustaw_srodek_obrotu(sf::Vector2f wspolrzedne) {
	lokalizacja.setOrigin(wspolrzedne);
}

//RYSOWANIE GRAFIKI I WSKAZNIKA
void Ladowanie_grafik::rysuj(sf::RenderWindow& window) {
	window.draw(lokalizacja);
}

//-------------------------------------------------------------------------------------------------

//AKTULAZIOWANIE WARTOSCI DLA KOLA
void Proste_kolo::aktualizuj_kolo(int Radius, sf::Color OutlineColor, sf::Color FillColor, int Thickness, sf::Vector2f Position) {

	kolo.setRadius(Radius);
	kolo.setOutlineColor(OutlineColor);
	kolo.setFillColor(FillColor);
	kolo.setOutlineThickness(Thickness);
	sf::FloatRect wymiar = kolo.getLocalBounds();
	kolo.setOrigin(sf::Vector2f((wymiar.position.x + wymiar.size.x)/2.0, (wymiar.position.y + wymiar.size.y)/2.0));
	kolo.setPosition({ Position });

}

//ZMIANA KOLORU DLA OBRAMOWKI
void Proste_kolo::zmiana_obramowki(sf::Color color) {

	kolo.setOutlineColor(color);

}

//PLYNNA ZMIANA KOLORU
void Proste_kolo::plynna_zmiana_koloru(float wartosc, float maxwartosc, float minwartosc, sf::Color start, sf::Color koniec) {

	if (wartosc <= minwartosc) {
		kolo.setOutlineColor(start);
		return;
	}
	if (wartosc >= maxwartosc) {
		kolo.setOutlineColor(koniec);
		return;
	}

	float procent = (wartosc - minwartosc) / (maxwartosc - minwartosc);

	int r = start.r + (koniec.r - start.r) * procent;
	int g = start.g + (koniec.g - start.g) * procent;
	int b = start.b + (koniec.b - start.b) * procent;

	kolo.setOutlineColor(sf::Color(r, g, b));
}

//WYSWIETLANIE KOLA
void Proste_kolo::rysuj(sf::RenderWindow& window) {

	window.draw(kolo);

}