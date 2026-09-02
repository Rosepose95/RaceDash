#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;


class Button {
	sf::RectangleShape ramka;
	sf::Text napis;

public:
	Button(sf::Font& czcionka) : napis(czcionka) {}

	void aktualizuj_wymiary(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness);
	void obsluga_najechania(float mysz_x, float mysz_y);
	bool obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb);
	void set_napis(string napis, sf::Vector2f Pozycja, int charactersize);
	void rysuj(sf::RenderWindow& window);

};

class Menu {
	
	sf::RectangleShape ramka;
	sf::Sprite zdj;
	sf::Text opis;
	Button Opcja1;
	Button Opcja2;


	bool czy_menu_wysuniete = false;

public:
	Menu() = default;
	Menu(sf::Texture& zdjecie, sf::Font& czcionka) : zdj(zdjecie), Opcja1(czcionka), Opcja2(czcionka), opis(czcionka){}

	void aktualizuj_wymiary_ramki(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness);
	void aktualizuj_wymiary_guzikow(sf::Vector2f Position1, sf::Vector2f Position2, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness);
	void set_text(string napis1, string napis2, string napis3, sf::Vector2f Pozycja1, sf::Vector2f Pozycja2, sf::Vector2f Pozycja3, int charactersize);
	void wymiary_zdj(sf::Vector2f Positon, float skala);
	void obsluga_najechania(float mysz_x, float mysz_y);
	bool obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb);
	void wlaczanie_menu();

	sf::FloatRect GETgranice_zdjecia() { return zdj.getGlobalBounds(); }

	void rysuj_zdj(sf::RenderWindow& window);
	void rysuj_menu(sf::RenderWindow& window);

};
