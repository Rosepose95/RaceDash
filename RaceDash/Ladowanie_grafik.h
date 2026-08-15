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
    sf::Texture bateria_low_png;
    sf::Texture woda_png;
    sf::Texture woda_overheat_png;
    sf::Texture paliwo_png;
    sf::Texture rezerwa_png;

public:

    bool zaladuj_grafike();

};