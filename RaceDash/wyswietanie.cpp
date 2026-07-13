#include <iostream>
#include <functional>
#include "wyswietlanie.h"
using namespace std;

Wyswietlanie::Wyswietlanie(): tekst(czcionka){					//ustawiamy czcionke tekstu
		
	if (czcionka.openFromFile("HARLOWSI.ttf") == false) {    //ladujemy czcionke
 		cout << "Blad we wczytywaniu czcionki!!!" << endl;
		//system("pause");
	}
}

void Wyswietlanie::aktualizuj_ksztalt(float Radius, sf::Color FillColor, sf::Color OutlineColor, int Thickness, sf::Vector2f Origin, sf::Vector2f Position) {
	ksztalt.setRadius(Radius);					
	ksztalt.setFillColor(FillColor);
	ksztalt.setOutlineColor(OutlineColor);
	ksztalt.setOutlineThickness(Thickness);
	ksztalt.setOrigin(Origin);
	ksztalt.setPosition(Position);
}

void Wyswietlanie::aktualizuj_tekst(int CharacterSize, sf::Color TextColor, sf::Vector2f Position) {

	tekst.setCharacterSize(CharacterSize);								
	tekst.setFillColor(TextColor);
	sf::FloatRect wymiary = tekst.getLocalBounds();			
	tekst.setOrigin(sf::Vector2f((wymiary.position.x + wymiary.size.x) / 2.0, (wymiary.position.y + wymiary.size.y) / 2.0));
	tekst.setPosition(Position);
}

void Wyswietlanie::aktualizuj_string(float wartosc) {
	
	int metoda = static_cast<int>(wartosc);
	tekst.setString(to_string(metoda));
}

void Wyswietlanie::rysuj(sf::RenderWindow& window, Wyswietlanie& obiekt, float wartosc){

	obiekt.aktualizuj_string(wartosc);

	window.draw(ksztalt);
	window.draw(tekst);
}