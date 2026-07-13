#pragma once
#include <SFML/Graphics.hpp>
#include "dane.h"

class Wyswietlanie {
	sf::Font czcionka;
	sf::Text tekst;
	sf::CircleShape ksztalt;

public:
	Wyswietlanie();

	void aktualizuj_ksztalt(float Radius, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position);
	void aktualizuj_tekst(int CharacterSize, sf::Color TextColor, sf::Vector2f Position);
	void aktualizuj_string(float wartosc);
	void rysuj(sf::RenderWindow& window, Wyswietlanie& obiekt, float wartosc);
};
