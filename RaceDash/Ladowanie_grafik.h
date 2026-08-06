#pragma once
#include <SFML/Graphics.hpp>

class grafiki {
public:
	sf::Font czcionka;
    sf::Texture wskazowka_png;
    sf::Texture obrotomierz_png;
    sf::Texture predkosciomierz_png;
    sf::Texture olej_png;
    sf::Texture bateria_png;
    sf::Texture woda_png;

public:

    bool zaladuj_grafike();

};