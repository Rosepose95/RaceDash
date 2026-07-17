#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "RaceDash");       


    sf::Clock zegar;                                                        

    //OPERAJCE NA PLIKACH
    fstream logi;
    logi.open("logi.csv", ios::in);
   
    if (logi.good() == false) {
        cout<<"Brak pliku!!!"<< endl;
        return 0;
    }
    string linia;
    getline(logi, linia);                                                   //pomijamy pierwsza linijke pliku

    bool MoznaCzytac = true;

    //OBIEKT NA KTORYM DZIALAMY
    Pojazd AktualnyStan;

    //WYSWITLANIE PREDKOSCI ORAZ PROSTOKATA W KTORYM JEST TEKST
    Wyswietlanie predkosc;
    predkosc.aktualizuj_ksztalt({20.0, 13.0}, {30,30,30}, {0,255,0}, 2, {100.0,100.0}, {595.0,510.0});
    predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 500.0, 410.0 });

    //WYSWITLANIE OBROTOW ORAZ PROSTOKATA W KTORYM JEST TEKST
    Wyswietlanie obroty;
    obroty.aktualizuj_ksztalt({50.0, 20.0}, {30,30,30}, {0,255,0}, 2, {60.0,60.0}, {280.0,390.0});
    obroty.aktualizuj_tekst(20, { 255, 255, 255 }, { 225.0, 325.0 });

    //RYSOWANIE OBROTOMIERZA
    Ladowanie_grafik obrotomierz;
    obrotomierz.aktualizuj_grafike("obrotomierz.png", { 200.0,300.0 });
    obrotomierz.zmiana_wielkosc(0.5);

    //RYSOWANIE WSKAZOWKI OBROTOMIERZA
    Ladowanie_grafik wskazowka_obrotomierz;
    wskazowka_obrotomierz.aktualizuj_grafike("wskazowka.png", { 200.0,300.0 });
    wskazowka_obrotomierz.aktualizuj_katy(8000.0, 0.0, 270.0);
    wskazowka_obrotomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_obrotomierz.zmiana_wielkosc(0.4);

    //RYSOWANIE PREDKOSCIOMIERAZA
    Ladowanie_grafik predkosciomierz;
    predkosciomierz.aktualizuj_grafike("predkosciomierz.png", {480.0, 300.0});
    predkosciomierz.zmiana_wielkosc(0.2);

    //RYSOWANIE WSKAZOWKI PREDKOSCIOMIERAZA
    Ladowanie_grafik wskazowka_predkosciomierz;
    wskazowka_predkosciomierz.aktualizuj_grafike("wskazowka.png", { 475.0, 310.0 });
    wskazowka_predkosciomierz.aktualizuj_katy(240.0, 0.0, 370.0);
    wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_predkosciomierz.zmiana_wielkosc(0.55);



    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())                              //sprawdzanie czy kliknieto X w oknie
            {
                window.close();
            }
        }

        //PETLA AKTUALIZUJACA DANE AZ DO KONCA DANYCH W PLIKU
        if ((MoznaCzytac==true) && (zegar.getElapsedTime().asMilliseconds() >= 500)) {
            if (odczyt(logi, AktualnyStan) == false) {                              //jesli skoncza sie dane do czytania koniec programu
                cout << "Koniec danych" << endl;
                MoznaCzytac = false;
            }

            wskazowka_obrotomierz.wyliczanie_kata(AktualnyStan.getObroty());
            wskazowka_predkosciomierz.wyliczanie_kata(AktualnyStan.getPredkosc());

            if (AktualnyStan.getPredkosc() >= 0 && AktualnyStan.getPredkosc() <= 50) {
                predkosc.zmiana_koloru_obramowki({ 0, 255, 0 });
            }
            else if (AktualnyStan.getPredkosc() > 50 && AktualnyStan.getPredkosc() <= 90) {
                predkosc.zmiana_koloru_obramowki({ 255, 165, 0 });
            }
            else if (AktualnyStan.getPredkosc() > 90 && AktualnyStan.getPredkosc() <= 140) {
                predkosc.zmiana_koloru_obramowki({ 255, 102, 102 });
            }
            else {
                predkosc.zmiana_koloru_obramowki({ 165, 0, 0 });
            }


            if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
                obroty.zmiana_koloru_obramowki({ 0, 255, 0 });
            }
            else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
                obroty.zmiana_koloru_obramowki({ 255, 165, 0 });
            }
            else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() <= 7000) {
                obroty.zmiana_koloru_obramowki({ 255, 102, 102 });
            }
            else {
                obroty.zmiana_koloru_obramowki({ 165, 0, 0 });
            }

            zegar.restart();
        }

        //TLO CALEGO OKNA
        window.clear(sf::Color(30, 30, 30));

        //WYSWIETLANIE WSZYSTKIEGO
        obrotomierz.rysuj(window);
        wskazowka_obrotomierz.rysuj(window);
        predkosciomierz.rysuj(window);
        wskazowka_predkosciomierz.rysuj(window);
        predkosc.rysuj(window, predkosc, AktualnyStan.getPredkosc());
        obroty.rysuj(window, obroty, AktualnyStan.getObroty());


        window.display();
    }

    logi.close();
    return 0;
}