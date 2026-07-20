#include <iostream>
#include <functional>
#include "wyswietlanie.h"
using namespace std;

//WYSWIETLANIE NAPISOW ORAZ OKREGU JAKO OBRAMOWANIE
Wyswietlanie::Wyswietlanie(): tekst(czcionka){					
		
	if (czcionka.openFromFile("HARLOWSI.ttf") == false) {    
 		cout << "Blad we wczytywaniu czcionki!!!" << endl;
		return;
	}
}

//USTAWIANIE WARTOSCI DLA PROSTOKATA
void Wyswietlanie::aktualizuj_ksztalt(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position) {
	ksztalt.setSize(SetSize);					
	ksztalt.setFillColor(FillColor);
	ksztalt.setOutlineColor(OutlineColor);
	ksztalt.setOutlineThickness(Thickness);
	ksztalt.setOrigin(Origin);
	ksztalt.setPosition(Position);
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

	ksztalt.setOutlineColor(kolor);

}

//RYSOWANIE WSZYSTKIEGO ORAZ AKTUALIZACJA WARTOSCI STRINGA
void Wyswietlanie::rysuj(sf::RenderWindow& window, Wyswietlanie& obiekt, float wartosc){

	obiekt.aktualizuj_string(wartosc);

	window.draw(ksztalt);
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

