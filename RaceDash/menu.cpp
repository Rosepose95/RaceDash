#include <iostream>
#include <string>
#include "menu.h"

using namespace std;

void Menu::aktualizuj_wymiary(sf::Vector2f Position, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness) {

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

void Menu::set_tekst(string tekst_opcja1, sf::Vector2f Pozycja1, string tekst_opcja2, sf::Vector2f Pozycja2, string tekst_opis, sf::Vector2f Pozycja3, int charactersize){

	Opcja1.setString(tekst_opcja1);
	Opcja1.setCharacterSize(charactersize);
	Opcja1.setPosition({ Pozycja1 });

	Opcja2.setString(tekst_opcja2);
	Opcja2.setCharacterSize(charactersize);
	Opcja2.setPosition({ Pozycja2 });

	opis.setString(tekst_opis);
	opis.setCharacterSize(charactersize);
	opis.setPosition({ Pozycja3 });

}

void Menu::aktualizuj_tlo_napisow(sf::Vector2f Position1, sf::Vector2f Position2, sf::Vector2f Size, sf::Color Fillcolor, sf::Color Outlinecolor, int thickness) {

	tlo_opcja1.setPosition({ Position1 });
	tlo_opcja1.setSize({ Size });
	tlo_opcja1.setFillColor(Fillcolor);
	tlo_opcja1.setOutlineColor(Outlinecolor);
	tlo_opcja1.setOutlineThickness(thickness);

	tlo_opcja2.setPosition({ Position2 });
	tlo_opcja2.setSize({ Size });
	tlo_opcja2.setFillColor(Fillcolor);
	tlo_opcja2.setOutlineColor(Outlinecolor);
	tlo_opcja2.setOutlineThickness(thickness);


}

void Menu::obsluga_klikniecia(float mysz_x, float mysz_y, bool& tryb){

	if (czy_menu_wysuniete == false) {
		return;

	}
	else if (tlo_opcja1.getGlobalBounds().contains({ mysz_x, mysz_y })) {
		tryb = false;
		czy_menu_wysuniete = false;
		tlo_opcja1.setOutlineColor({ 0,255,0 });
		tlo_opcja2.setOutlineColor({ 255,0,0 });


	}
	else if (tlo_opcja2.getGlobalBounds().contains({ mysz_x, mysz_y })) {
		tryb = true;
		czy_menu_wysuniete = false;
		tlo_opcja2.setOutlineColor({ 0,255,0 });
		tlo_opcja1.setOutlineColor({ 255,0,0 });
	}
}

void Menu::wlaczanie_menu() {
	czy_menu_wysuniete = !czy_menu_wysuniete;
}


void Menu::rysuj_zdj(sf::RenderWindow& window) {

	if (czy_menu_wysuniete == false) {
		window.draw(zdj);
	}
}

void Menu::rysuj_menu(sf::RenderWindow& window) {
	if (czy_menu_wysuniete == true) {
		window.draw(ramka);
		window.draw(Opcja1);
		window.draw(tlo_opcja1);
		window.draw(Opcja2);
		window.draw(tlo_opcja2);
		window.draw(opis);
	}
}

