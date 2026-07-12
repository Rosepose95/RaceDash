#pragma once
#include <SFML/Graphics.hpp>
#include "dane.h"

class Wyswietlanie {
	sf::Font czcionka;
	sf::Text tekst;
	sf::CircleShape ksztalt;

public:
	Wyswietlanie();
	void rysuj(sf::RenderWindow& window, Pojazd& AktualnyStan);
};
