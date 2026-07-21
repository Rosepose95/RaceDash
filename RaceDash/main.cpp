#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "RaceDash");       


    sf::Clock zegar_dla_danych;                 //dla odswiezania danych
    sf::Clock zegar_dla_migania;                //dla migania obrotomierza


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

    //RYSOWANIE OBROTOMIERZA
    Ladowanie_grafik obrotomierz;
    obrotomierz.aktualizuj_grafike("grafika/obrotomierz.png", { 400.0,300.0 });
    obrotomierz.zmiana_wielkosc(0.7);

    //RYSOWANIE WSKAZOWKI OBROTOMIERZA
    Ladowanie_grafik wskazowka_obrotomierz;
    wskazowka_obrotomierz.aktualizuj_grafike("grafika/wskazowka.png", { 400.0,300.0 });
    wskazowka_obrotomierz.aktualizuj_katy(8000.0, 0.0, 0.0, 270.0);
    wskazowka_obrotomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_obrotomierz.zmiana_wielkosc(0.6);

    //WYSWITLANIE OBROTOW ORAZ PROSTOKATA W KTORYM JEST TEKST
    Wyswietlanie obroty;
    obroty.aktualizuj_prostokat({ 60.0, 30.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 60.0,60.0 }, { 500.0,410.0 });
    obroty.aktualizuj_tekst(15, { 255, 255, 255 }, { 450.0, 360.0 });

    //RYSOWANIE PREDKOSCIOMIERAZA
    Ladowanie_grafik predkosciomierz;
    predkosciomierz.aktualizuj_grafike("grafika/predkosciomierz.png", {650.0, 300.0});
    predkosciomierz.zmiana_wielkosc(0.45);

    //RYSOWANIE WSKAZOWKI PREDKOSCIOMIERAZA
    Ladowanie_grafik wskazowka_predkosciomierz;
    wskazowka_predkosciomierz.aktualizuj_grafike("grafika/wskazowka.png", { 675.0, 300.0 });
    wskazowka_predkosciomierz.aktualizuj_katy(220.0, 0.0, 0.0, 340.0);
    wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_predkosciomierz.zmiana_wielkosc(0.5);

    //WYSWITLANIE PREDKOSCI ORAZ PROSTOKATA W KTORYM JEST TEKST
    Wyswietlanie predkosc;
    predkosc.aktualizuj_prostokat({ 30.0, 17.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 100.0,100.0 }, { 830.0,460.0 });
    predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 735.0, 365.0 });

    //RYSOWANIE TEMPERATURY OLEJU
    Ladowanie_grafik temperatura_oleju;
    temperatura_oleju.aktualizuj_grafike("grafika/tempoleju.png", { 120.0, 300.0 });
    temperatura_oleju.zmiana_wielkosc(0.4);

    //RYSOWANIE WSKAZOWKI TEMPERATURY OLEJU
    Ladowanie_grafik wskazowka_tempoleju;
    wskazowka_tempoleju.aktualizuj_grafike("grafika/wskazowka.png", { 145.0, 300.0 });
    wskazowka_tempoleju.aktualizuj_katy(150.0, 50.0, 0.0, 300.0);
    wskazowka_tempoleju.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_tempoleju.zmiana_wielkosc(0.4);

    //RYSOWANIE OBRAMOWKI OBROTOMIERZA
    Proste_ksztalty obramowka_rpm;
    obramowka_rpm.aktualizuj_kolo(140, { 0,255,0 }, {0,0,0,0}, 12, { 405.0,305.0 });



    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())                              //sprawdzanie czy kliknieto X w oknie
            {
                window.close();
            }
        }

        //PETLA AKTUALIZUJACA DANE AZ DO KONCA DANYCH W PLIKU
        if ((MoznaCzytac==true) && (zegar_dla_danych.getElapsedTime().asMilliseconds() >= 100)) {
            if (odczyt(logi, AktualnyStan) == false) {                              //jesli skoncza sie dane do czytania koniec programu
                cout << "Koniec danych" << endl;
                MoznaCzytac = false;
            }
           
            //UAKTUALNIENIE DANYCH DLA WSKAZOWKI
            wskazowka_obrotomierz.wyliczanie_kata(AktualnyStan.getObroty());
            wskazowka_predkosciomierz.wyliczanie_kata(AktualnyStan.getPredkosc());
            wskazowka_tempoleju.wyliczanie_kata(AktualnyStan.getTempoleju());
       

            //ZMIANA KOLORU OBRAMOWKI DLA PREDKOSCI
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

            //ZMIANA KOLORU OBRAMOWKI DLA OBROTOW
            if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
                obroty.zmiana_koloru_obramowki({ 0, 255, 0 });
                obramowka_rpm.zmiana_obramowki({ 0, 255, 0 });
            }
            else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
                obroty.zmiana_koloru_obramowki({ 255, 165, 0 });
                obramowka_rpm.zmiana_obramowki({ 255, 165, 0 });
            }
            else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() < 7000) {
                obroty.zmiana_koloru_obramowki({ 255, 102, 102 });
                obramowka_rpm.zmiana_obramowki({ 255, 102, 102 });
            }
            else {
            if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
                obroty.zmiana_koloru_obramowki({ 165, 0, 0 });
                obramowka_rpm.zmiana_obramowki({ 165, 0, 0 });
            }
            else {
                obroty.zmiana_koloru_obramowki(sf::Color::Transparent);
                obramowka_rpm.zmiana_obramowki(sf::Color::Transparent);
            }
            }



            zegar_dla_danych.restart();
        }

        //TLO CALEGO OKNA
        window.clear(sf::Color(30, 30, 30));

        //WYSWIETLANIE WSZYSTKIEGO
        obrotomierz.rysuj(window);
        wskazowka_obrotomierz.rysuj(window);

        predkosciomierz.rysuj(window);
        wskazowka_predkosciomierz.rysuj(window);

        temperatura_oleju.rysuj(window);
        wskazowka_tempoleju.rysuj(window);

        predkosc.rysuj(window, predkosc, AktualnyStan.getPredkosc());
        obroty.rysuj(window, obroty, AktualnyStan.getObroty());

        obramowka_rpm.rysuj(window);



        window.display();
    }

    logi.close();
    return 0;
}