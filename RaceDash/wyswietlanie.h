#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "dane.h"

class Wyswietlanie {
	sf::Font czcionka;
	sf::Text tekst;
	sf::RectangleShape ksztalt;

public:
	Wyswietlanie();

	void aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position);
	void aktualizuj_tekst(int CharacterSize, sf::Color TextColor, sf::Vector2f Position);
	void aktualizuj_string(float wartosc);
	void zmiana_koloru_obramowki(sf::Color kolor);
	void rysuj(sf::RenderWindow& window, Wyswietlanie& obiekt, float wartosc);
};

class Ladowanie_grafik {
	sf::Image obraz;
	sf::Texture tekstura;
	sf::Sprite lokalizacja;

	float maxwartosc;
	float minwartosc;
	float katstartowy;
	float katkoncowy;

public:
	Ladowanie_grafik();

	void aktualizuj_grafike(std::string zdjecie, sf::Vector2f pozycja);
	void aktualizuj_katy(float maxw, float minw, float ks, float kk);
	void wyliczanie_kata(float wartosc);
	void zmiana_wielkosc(float skala);
	void ustaw_srodek_obrotu(sf::Vector2f wspolrzedne);
	void rysuj(sf::RenderWindow& window);

};

class Proste_ksztalty {
	sf::RectangleShape prostokat;
	sf::CircleShape kolo;

public:

	void aktualizuj_prostokat(sf::Vector2f SetSize, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position);
	void aktualizuj_kolo(int Radius, sf::Color OutlineColor, sf::Color FillColor, int Thickness, sf::Vector2f Position);
	void zmiana_obramowki(sf::Color color);
	void rysuj(sf::RenderWindow& window);
};