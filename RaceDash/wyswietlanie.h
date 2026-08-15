#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "dane.h"

class Wyswietlanie {
	sf::Text tekst;
	sf::RectangleShape prostokat;

	float wczesniejsza_wartosc = 9999.0f;    //dla aktualizuj string

public:
	Wyswietlanie(sf::Font &c): tekst(c){}

	void aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position);
	void aktualizuj_tekst(int CharacterSize, sf::Color TextColor, sf::Vector2f Position);
	void aktualizuj_string(float wartosc, int precyzja, string znak);
	void zmiana_koloru_obramowki(sf::Color kolor);
	void rysuj(sf::RenderWindow& window, float wartosc, int precyzja, string znak);
};


class Ladowanie_grafik {
	sf::Sprite lokalizacja;

	float maxwartosc;
	float minwartosc;
	float katstartowy;
	float katkoncowy;

public:
	Ladowanie_grafik(sf::Texture& zdjecie) : lokalizacja(zdjecie){}

	void aktualizuj_polozenie(sf::Vector2f pozycja);
	void aktualizuj_katy(float maxw, float minw, float ks, float kk);
	void wyliczanie_kata(float wartosc);
	void zmiana_wielkosc(float skala);
	void ustaw_srodek_obrotu(sf::Vector2f wspolrzedne);
	void rysuj(sf::RenderWindow& window);

};

class Proste_kolo {

	sf::CircleShape kolo;

public:
	Proste_kolo(){}

	void aktualizuj_kolo(int Radius, sf::Color OutlineColor, sf::Color FillColor, int Thickness, sf::Vector2f Position);
	void zmiana_obramowki(sf::Color color);
	void zmiana_wypelnienia(sf::Color color);
	void rysuj(sf::RenderWindow& window);
};

class Prosty_prostokat {

	sf::RectangleShape prostokat;

public:
	Prosty_prostokat(){}

	void aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Position);
	void poziom_paliwa(float max, float min, float wartosc, float max_width, float height);
	void zmiana_wypelnienia(sf::Color color);
	void rysuj(sf::RenderWindow& window);
};


sf::Color plynna_zmiana_koloru(float wartosc, float maxwartosc, float minwartosc, sf::Color start, sf::Color koniec);