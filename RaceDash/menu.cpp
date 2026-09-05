#include <iostream>
#include <string>
#include "menu.h"

using namespace std;

void Menu::aktualizuj_wymiary_ramki(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness){

	ramka.setPosition({ Position });
	ramka.setSize({ Size });
	ramka.setFillColor(Fillcolor );
	ramka.setOutlineColor(Outlinecolor);
	ramka.setOutlineThickness(thickness);
}

void Menu::wymiary_zdj(sf::Vector2f Positon, float skala) {
	zdj.setPosition({ Positon });
	zdj.setScale(sf::Vector2f(skala,skala));
}

void Menu::aktualizuj_wymiary_guzikow(sf::Vector2f Position1, sf::Vector2f Position2, sf::Vector2f Position3, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness) {

	Opcja1.aktualizuj_wymiary({ Position1 }, { Size }, { Fillcolor }, { Outlinecolor }, thickness);
	Opcja2.aktualizuj_wymiary({ Position2 }, { Size }, { Fillcolor }, { Outlinecolor }, thickness);
	Wczytaj.aktualizuj_wymiary({ Position3 }, { Size }, { Fillcolor }, { Outlinecolor }, thickness);

}
void Menu::set_text(string napis1, string napis2, string napis3, string napis4, sf::Vector2f Pozycja1, sf::Vector2f Pozycja2, sf::Vector2f Pozycja3, sf::Vector2f Pozycja4, int charactersize1, int charactersize2) {

	Opcja1.set_napis(napis1, { Pozycja1 }, charactersize1);
	Opcja2.set_napis(napis2, { Pozycja2 }, charactersize1);
	Wczytaj.set_napis(napis4, { Pozycja4 }, charactersize1);

	opis.setString(napis3);
	opis.setPosition({ Pozycja3 });
	opis.setCharacterSize(charactersize2);
}
void Menu::obsluga_najechania(float mysz_x, float mysz_y, bool& tryb){

	if (tryb == false) {
		return;

	}
	Opcja1.obsluga_najechania(mysz_x, mysz_y);
	Opcja2.obsluga_najechania(mysz_x, mysz_y);
	Wczytaj.obsluga_najechania(mysz_x, mysz_y);

}

bool Menu::obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb1, bool& tryb2, bool& tryb3, bool& tryb4) {

	if (tryb4 == false) {
		return false;

	}

	Opcja1.obsluga_klikniecia(mysz_x, mysz_y, tryb1);
	Opcja2.obsluga_klikniecia(mysz_x, mysz_y, tryb2);
	Wczytaj.obsluga_klikniecia(mysz_x, mysz_y, tryb3);

	tryb4 = false;
}




void Menu::wlaczanie_menu(bool& tryb) {
	tryb = !tryb;
}


void Menu::rysuj_zdj(sf::RenderWindow& window) {
		window.draw(zdj);

}

void Menu::rysuj_menu(sf::RenderWindow& window) {
		window.draw(ramka);
		Opcja1.rysuj(window);
		Opcja2.rysuj(window);
		Wczytaj.rysuj(window);
		window.draw(opis);

}
//-------------------------------------------------------------------------

void Button::aktualizuj_wymiary(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness) {
	ramka.setPosition({ Position });
	ramka.setSize({ Size });
	ramka.setFillColor({ Fillcolor });
	ramka.setOutlineColor({ Outlinecolor });
	ramka.setOutlineThickness(thickness);

}

void Button::obsluga_najechania(float mysz_x, float mysz_y) {
	if (ramka.getGlobalBounds().contains({ mysz_x, mysz_y })) {
		ramka.setFillColor({ 0,165,0,50 });
		ramka.setOutlineColor({ 0,255,0 });	
	}
	else {
		ramka.setOutlineColor({ 255,0,0 });
		ramka.setFillColor({30,30,30,200});
	}
}

bool Button::obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb) {
	if (ramka.getGlobalBounds().contains({ mysz_x, mysz_y })) {
		tryb = !tryb;
		return true;
	}
	else {
		return false;

	}
}

void Button::set_napis(string n, sf::Vector2f Pozycja, int charactersize) {
	napis.setString(n);
	napis.setPosition({ Pozycja });
	napis.setCharacterSize(charactersize);

}

void Button::rysuj(sf::RenderWindow& window) {
	window.draw(ramka);
	window.draw(napis);

}

