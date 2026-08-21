#include <iostream>
#include <functional>
#include <sstream>
#include "wyswietlanie.h"
using namespace std;


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
	tekst.setPosition(Position);
}

//WPISYWANIE TEKSTU DO ZMIENNEJ
void Wyswietlanie::aktualizuj_string(float wartosc, int precyzja, string znak) {
	
	if (wartosc == wczesniejsza_wartosc) {
		return;
	}
	else {
		wczesniejsza_wartosc = wartosc;
	}

	if (precyzja == 0 && znak == "0") {
		int metoda = static_cast<int>(wartosc);
		tekst.setString(to_string(metoda));
	}
	else {
		stringstream stream;           

		stream.precision(precyzja);     
		stream.setf(ios::fixed);   // ustawienie precyzji po przecinku 
		stream<<wartosc;            

		tekst.setString(stream.str() + znak);
	}
}

//ZMIANA KOLORU OBRAMOWKI OD WARTOISC PREDKOSCI, OBROTOW ITD
void Wyswietlanie::zmiana_koloru_obramowki(sf::Color kolor) {

	prostokat.setOutlineColor(kolor);

}

void Wyswietlanie::alarm_gorny(float wartosc, float prog_ostrzegawczy, float prog_krytyczny, sf::Clock& Zegar, Ladowanie_grafik& image1, Ladowanie_grafik& image2, sf::RenderWindow& window){
	if (wartosc >= prog_krytyczny) {

		if (Zegar.getElapsedTime().asMilliseconds() % 500 > 250) {
			image1.rysuj(window);
			prostokat.setOutlineColor({ 255,0,0 });
		}
		else {
			prostokat.setOutlineColor({ sf::Color::Transparent });
			image2.rysuj(window);
		}
	}
	else if (wartosc >= prog_ostrzegawczy) {
		prostokat.setOutlineColor({ 255,165,0 });
		image1.rysuj(window);
	}
	else {
		prostokat.setOutlineColor({0,255,0});
		image2.rysuj(window);
	}
}
void Wyswietlanie::alarm_dolny(float wartosc, float prog_ostrzegawczy, float prog_krytyczny, sf::Clock& Zegar, Ladowanie_grafik& image1, Ladowanie_grafik& image2, sf::RenderWindow& window) {
	if (wartosc <= prog_krytyczny) {

		if(Zegar.getElapsedTime().asMilliseconds() % 500 > 250) {
			image1.rysuj(window);
			prostokat.setOutlineColor({ 255,0,0 });
		}
		else {
		prostokat.setOutlineColor({ sf::Color::Transparent });
		image2.rysuj(window);
		}
	}
	else if (wartosc <= prog_ostrzegawczy) {
		prostokat.setOutlineColor({ 255,165,0 });
		image1.rysuj(window);
	}
	else {
		prostokat.setOutlineColor({ 0,255,0 });
		image2.rysuj(window);
	}
}

//RYSOWANIE WSZYSTKIEGO ORAZ AKTUALIZACJA WARTOSCI STRINGA
void Wyswietlanie::rysuj(sf::RenderWindow& window, float wartosc, int precyzja, string znak){

	aktualizuj_string(wartosc, precyzja, znak);

	window.draw(prostokat);
	window.draw(tekst);
}


//--------------------------------------------------------------------------------------------------------


//LADOWANIE I WYSWIETLANIE GRAFIK

 //USTALENIE LOKALIZACJI
void Ladowanie_grafik::aktualizuj_polozenie(sf::Vector2f pozycja){

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

//ZMIANA KOLORU WYPELNIENIA
void Proste_kolo::zmiana_wypelnienia(sf::Color color) {

	kolo.setFillColor(color);

}

//WYSWIETLANIE KOLA
void Proste_kolo::rysuj(sf::RenderWindow& window) {

	window.draw(kolo);

}
//-------------------------------------------------------------------------------------------

//AKTUALIZOWANIE DANYCH PROSTOKATA
void Prosty_prostokat::aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Position) {

	prostokat.setSize(SetSize);
	prostokat.setFillColor(FillColor);
	prostokat.setOutlineColor(OutlineColor);
	prostokat.setOutlineThickness(Thickness);
	prostokat.setPosition(Position);
}

//OBLICZENIE POZIOMU PALIWA

void Prosty_prostokat::poziom_paliwa(float max, float min, float wartosc, float max_width, float height){
	float procent = (wartosc - min) / (max - min);

	float szerokosc = procent * max_width;
	prostokat.setSize(sf::Vector2f(szerokosc, height));
}

//ZMIANA KOLORU WYPELNIENIA
void Prosty_prostokat::zmiana_wypelnienia(sf::Color color) {
	prostokat.setFillColor(color);
}

//RYSOWANIE PRSOTKATA
void Prosty_prostokat::rysuj(sf::RenderWindow& window) {
	window.draw(prostokat);
}

//---------------------------------------------------------------

//PLYNNA ZMIANA KOLORU
sf::Color plynna_zmiana_koloru(float wartosc, float maxwartosc, float minwartosc, sf::Color start, sf::Color koniec) {

	if (wartosc > maxwartosc) {
		return koniec;
	}
	if (wartosc < minwartosc) {
		return start;
	}

	float procent = (wartosc - minwartosc) / (maxwartosc - minwartosc);

	int r = start.r + (koniec.r - start.r) * procent;
	int g = start.g + (koniec.g - start.g) * procent;
	int b = start.b + (koniec.b - start.b) * procent;
	
	sf::Color finalny(r, g, b);
	return finalny;

}