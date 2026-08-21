#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;


class Menu {
	
	sf::RectangleShape ramka;
	sf::Sprite zdj;
	sf::Text opis;
	sf::Text Opcja1;
	sf::RectangleShape tlo_opcja1;
	sf::Text Opcja2;
	sf::RectangleShape tlo_opcja2;

	bool czy_menu_wysuniete = false;

public:
	Menu() = default;
	Menu(sf::Texture& zdjecie, sf::Font& czcionka) : zdj(zdjecie), Opcja1(czcionka), Opcja2(czcionka), opis(czcionka){}

	void aktualizuj_wymiary(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness);
	void wymiary_zdj(sf::Vector2f Positon, float skala);
	void set_tekst(string tekst_opcja1, sf::Vector2f Pozycja1, string tekst_opcja2, sf::Vector2f Pozycja2, string tekst_opis, sf::Vector2f Pozycja3, int charactersize);
	void aktualizuj_tlo_napisow(sf::Vector2f Position1, sf::Vector2f Position2, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor1, sf::Color Outlinecolor2, int thickness);
	void obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb);
	void animacja_pokazywania();
	void wlaczanie_menu();

	sf::FloatRect GETgranice_zdjecia() { return zdj.getGlobalBounds(); }

	void rysuj_zdj(sf::RenderWindow& window);
	void rysuj_menu(sf::RenderWindow& window);

};
