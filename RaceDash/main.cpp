#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "RaceDash");       //ustawienie rozmiaru okna
    sf::Clock zegar;                                                        //zmienna do odswiezania danych z pliku

    fstream logi;
    logi.open("logi.csv", ios::in);
   
    if (logi.good() == false) {
        cout<<"Brak pliku!!!"<< endl;
        return 0;
    }
    string linia;
    getline(logi, linia);                                                   //pomijamy pierwsza linijke pliku
    bool MoznaCzytac = true;


    Pojazd AktualnyStan;
    Wyswietlanie pulpit;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())                              //sprawdzanie czy kliknieto X w oknie
            {
                window.close();
            }
        }


        if ((MoznaCzytac==true) && (zegar.getElapsedTime().asMilliseconds() >= 1000)) {
            if (odczyt(logi, AktualnyStan) == false) {                              //jesli skoncza sie dane do czytania koniec programu
                cout << "Koniec danych" << endl;
                MoznaCzytac = false;
            }
            odczyt(logi, AktualnyStan);

            zegar.restart();
        }

        window.clear(sf::Color(30, 30, 30));
        pulpit.rysuj(window, AktualnyStan);
        window.display();
    }

    logi.close();
    return 0;
}