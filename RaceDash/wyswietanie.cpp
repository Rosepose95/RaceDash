#include <iostream>
#include "wyswietlanie.h"
using namespace std;

Wyswietlanie::Wyswietlanie(): tekst(czcionka){					//ustawiamy czcionke tekstu
		
	if (czcionka.openFromFile("HARLOWSI.ttf") == false) {    //ladujemy czcionke
 		cout << "Blad we wczytywaniu czcionki!!!" << endl;
		//system("pause");
	}

	ksztalt.setRadius(100.0);								//ustawiamy wymiary,kolory, itd naszego kola
	ksztalt.setFillColor(sf::Color(30,30,30));
	ksztalt.setOutlineColor(sf::Color(0, 255, 0));
	ksztalt.setOutlineThickness(15);
	ksztalt.setOrigin({ 100.0, 100.0 });
	ksztalt.setPosition({ 450,320 });

	tekst.setCharacterSize(30);								//ustawiamy dane naszego tekstu
	tekst.setFillColor(sf::Color(0, 255, 0));
	sf::FloatRect wymiary = tekst.getLocalBounds();			//pobieramy polozenie napisu
	tekst.setOrigin(sf::Vector2f((wymiary.position.x + wymiary.size.x)/2.0,(wymiary.position.y + wymiary.size.y)/2.0));
	tekst.setPosition(sf::Vector2f(400, 300 ));

}

void Wyswietlanie::rysuj(sf::RenderWindow& window, Pojazd& AktualnyStan){

	tekst.setString(std::to_string(int(AktualnyStan.getPredkosc())) + "km/h");

	int predkosc_zmiana = static_cast<int>(AktualnyStan.getPredkosc());

	if (predkosc_zmiana >= 50 && predkosc_zmiana <= 90) {
		ksztalt.setOutlineColor(sf::Color(255, 165, 0));
	}
	else if (predkosc_zmiana > 90 && predkosc_zmiana < 140) {
		ksztalt.setOutlineColor(sf::Color(255, 0, 0));
	}

	window.draw(ksztalt);
	window.draw(tekst);
}