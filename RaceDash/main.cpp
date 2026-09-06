#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include "Ladowanie_grafik.h"
#include "menu.h"
#include "Tworzenie_obiektow.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "RaceDash");
    window.setFramerateLimit(60);

    sf::Clock zegar_dla_danych;                 //dla odswiezania danych
    sf::Clock zegar_dla_migania;                //dla migania obrotomierza

    //ZALADOWANIE GRAFIK
    grafiki grafika;
    if (grafika.zaladuj_grafike() == false) {
        cout << "Blad w plikach grafik" << endl;
        return 0;
    }

    Wspolne_obiekty obiekty(grafika);

    //OPERAJCE NA PLIKACH
    fstream logi;
    string linia;

    // logi.open("logi.csv", ios::in);

     //if (logi.good() == false) {
       //  cout << "Brak pliku!!!" << endl;
         //return 0;
     //}
     //getline(logi, linia);                                         //pomijamy pierwsza linijke pliku


    bool MoznaCzytac = true;

    //OBIEKT NA KTORYM DZIALAMY
    Pojazd AktualnyStan;

    //UTWORZENIE WSZYSTKICH OBIEKTOW
    obiekty.utworzenie_obiektow();


    //GLOWNA PETLA PROGRAMU
    while (window.isOpen()) {

        // POZYCJA MYSZKI
        sf::Vector2i poz_myszki = sf::Mouse::getPosition(window);

        // NAJECHANIE NA GUZIKI
        obiekty.hover(poz_myszki);

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { // sprawdzanie czy kliknieto X w oknie
                window.close();
            }

            //OBSLUGA KLIKNIECIA W GUZIKI
            if (const auto* mousevent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousevent->button == sf::Mouse::Button::Left) {

                    float position_x = (float)mousevent->position.x;
                    float position_y = (float)mousevent->position.y;

                    bool czy_bylo_menu = obiekty.main_menu_otwarte;

                    //OBSLUGA KLIKNIECIA GUZIKOW
                    obiekty.obsluga_klikniecia(position_x, position_y, zegar_dla_danych);

                    if (czy_bylo_menu == true && obiekty.start_na_testowym == true) {
                        logi.close();
                        logi.clear();

                        logi.open("logi.csv", ios::in);

                        if (logi.good() == false) {
                            cout << "Brak pliku, sproboj zaladowac swoj!!!" << endl;
                            obiekty.start_na_testowym = false;
                        }
                        getline(logi, linia);

                        MoznaCzytac = true;
                        obiekty.start_na_testowym = false;
                        zegar_dla_danych.restart();
                    }

                    if (obiekty.start_na_testowym == false && czy_bylo_menu == true && obiekty.wczytaj_plik == true) {
                        //JESLI UZYTKOWNIK WYBIERZE ZALADOWANIE SWOJEGO PLIKU
                        string wczytany_plik = wybierz_plik();
                        if (wczytany_plik != "") {
                            logi.close();
                            logi.clear();

                            logi.open(wczytany_plik, ios::in);
                            getline(logi, linia);

                            MoznaCzytac = true;
                            obiekty.main_menu_otwarte = false;
                            obiekty.wczytaj_plik = false;
                            obiekty.start_na_testowym = false;
                        }
                        zegar_dla_danych.restart();
                    }
                    //ZAMYKANIE PROGRAMU JESLI EXIT KLIKNIETE
                    if (obiekty.exit == true) {
                        window.close();
                    }
                    if (obiekty.main_menu_otwarte == true) {
                        obiekty.start_klikniete = false;
                    }
                }
            }
        }
        
         // PETLA AKTUALIZUJACA DANE AZ DO KONCA DANYCH W PLIKU
        if (obiekty.start_klikniete == true) {
            if ((MoznaCzytac == true) && (zegar_dla_danych.getElapsedTime().asMilliseconds() >= 100)) {
                if (odczyt(logi, AktualnyStan) == false) {              // jesli skoncza sie dane do czytania koniec programu
                    cout << "Koniec danych" << endl;
                    MoznaCzytac = false;

                }

                //WYWOLANIE WARUNKOW OD ZMIANY KOLOROW ITD
                obiekty.warunki(AktualnyStan, zegar_dla_migania);

                zegar_dla_danych.restart();
            }
        }

        // WYWO£ANIE G£ÓWNEGO RYSOWANIA
        obiekty.rysowanie_obiektow(window, AktualnyStan, zegar_dla_migania);

    }
    logi.close();
    return 0;
}