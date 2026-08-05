#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "RaceDash");
    window.setFramerateLimit(60);

    sf::Clock zegar_dla_danych;                 //dla odswiezania danych
    sf::Clock zegar_dla_migania;                //dla migania obrotomierza


        //OPERAJCE NA PLIKACH
        fstream logi;
        logi.open("logi.csv", ios::in);

        if (logi.good() == false) {
            cout << "Brak pliku!!!" << endl;
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
        obroty.aktualizuj_prostokat({ 60.0, 30.0 }, { 30,30,30 }, { 0,255,0 }, 2, {30.0 ,15.0}, { 470.0, 370.0 });
        obroty.aktualizuj_tekst(15, { 255, 255, 255 }, { 450.0, 360.0 });

        //RYSOWANIE PREDKOSCIOMIERAZA
        Ladowanie_grafik predkosciomierz;
        predkosciomierz.aktualizuj_grafike("grafika/predkosciomierz.png", { 650.0, 300.0 });
        predkosciomierz.zmiana_wielkosc(0.45);

        //RYSOWANIE WSKAZOWKI PREDKOSCIOMIERAZA
        Ladowanie_grafik wskazowka_predkosciomierz;
        wskazowka_predkosciomierz.aktualizuj_grafike("grafika/wskazowka.png", { 675.0, 300.0 });
        wskazowka_predkosciomierz.aktualizuj_katy(220.0, 0.0, 0.0, 340.0);
        wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
        wskazowka_predkosciomierz.zmiana_wielkosc(0.5);

        //WYSWITLANIE PREDKOSCI ORAZ PROSTOKATA W KTORYM JEST TEKST
        Wyswietlanie predkosc;
        predkosc.aktualizuj_prostokat({ 30.0, 17.0 }, { 30,30,30 }, { 0,255,0 }, 2, {15.0, 13.5},  { 735.0, 370.0 });
        predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 725.0, 360.0 });

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

        //RYSOWANIE BIEGU ORAZ JEGO OBRAMOWKI
        Wyswietlanie bieg;
        bieg.aktualizuj_prostokat({ 30.0, 50.0 }, { 30, 30, 30 }, { 255, 255, 255 }, 2, {15.0, 25.0}, { 400.0, 350.0 });
        bieg.aktualizuj_tekst(32, {255,255,255}, { 390.0, 330.0 });

        //RYSOWANIE OBRAMOWKI OBROTOMIERZA
        Proste_kolo obramowka_rpm;
        obramowka_rpm.aktualizuj_kolo(140, { 0,255,0 }, { 0,0,0,0 }, 10, { 405.0,305.0 });

        //RYSOWANIE RAMKI CALEGO LICZNIKA
        Prosty_prostokat ramka;
        ramka.aktualizuj_prostokat({800.0, 600.0}, {sf::Color::Transparent}, { 35, 35, 40 }, -5, {0.0, 0.0});


        //ALA DIODY NA GORZE EKRANU (dla oborotow)
        Proste_kolo diody[5];
        for (int i = 0; i < 5; i++) {
            diody[i].aktualizuj_kolo(10, { 0,0,0 }, { 0,255,0 }, 2, { 320.0f + (i * 40.0f), 100.0f });
        }

        //PROGI DLA ZMIANY KOLOROW DIOD
        int wartosc_obrotow[5] = { 5000, 5500, 6000, 6500, 6900 };
        sf::Color kolory[5] = { { 50, 205, 50 }, { 255, 255, 0 }, { 255, 140, 0 }, { 255, 80, 0 }, { 255, 0, 0 } };

        //WYSWIETLANIE DANYCH O BATERII
        Wyswietlanie bateria;
        bateria.aktualizuj_prostokat({95.0, 40.0}, {10,10,10}, {100,100,100}, 2, {30.0, 20.0}, {110.0, 540.0});
        bateria.aktualizuj_tekst(20, { 255,255,255 }, {95.0, 530.0});
        
        //LADOWANIE GRAFIKI BATERII
        Ladowanie_grafik bateria_zdj;
        bateria_zdj.aktualizuj_grafike("grafika/car-battery.png", {40.0, 540.0});
        bateria_zdj.zmiana_wielkosc(0.125);

        //WYSWIETLANIE TEMP WODY
        Wyswietlanie woda;
        woda.aktualizuj_prostokat({95.0, 40.0}, {10,10,10}, {100,100,100}, 2, {30.0, 20.0}, {110.0, 480.0});
        woda.aktualizuj_tekst(20, { 255,255,255 }, {95.0, 470.0});

        //LADOWANIE GRAFIKI WODY
        Ladowanie_grafik woda_zdj;
        woda_zdj.aktualizuj_grafike("grafika/temp-wody.png", { 40.0, 480.0 });
        woda_zdj.zmiana_wielkosc(0.125);
        



        while (window.isOpen()) {
            while (const auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())                              //sprawdzanie czy kliknieto X w oknie
                {
                    window.close();
                }
            }

            //PETLA AKTUALIZUJACA DANE AZ DO KONCA DANYCH W PLIKU
            if ((MoznaCzytac == true) && (zegar_dla_danych.getElapsedTime().asMilliseconds() >= 100)) {
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
                    predkosc.plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 50, 0, { 50, 205, 50 }, { 255, 255, 0 });
                }

                else if (AktualnyStan.getPredkosc() > 50 && AktualnyStan.getPredkosc() <= 90) {
                    predkosc.plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 90, 50, { 255, 255, 0 }, { 255, 140, 0 });
                }

                else if (AktualnyStan.getPredkosc() > 90 && AktualnyStan.getPredkosc() <= 140) {
                    predkosc.plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 140, 90, { 255, 140, 0 }, { 255, 20, 147 });
                }

                else {
                    predkosc.plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 220, 141, { 255, 0, 0 }, { 180, 0, 0 });
                }


                //ZMIANA KOLORU OBRAMOWKI DLA OBROTOW
                if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
                    obroty.plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 });
                    obramowka_rpm.plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 });
                }

                else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
                    obroty.plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 });
                    obramowka_rpm.plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 });
                }

                else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() < 7000) {
                    obroty.plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 });
                    obramowka_rpm.plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 });
                }

                else {
                    if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
                        obroty.plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 });
                        obramowka_rpm.plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 });
                    }

                    else {
                        obroty.zmiana_koloru_obramowki(sf::Color::Transparent);
                        obramowka_rpm.zmiana_obramowki(sf::Color::Transparent);
                    }
                }

                //ZMIANA KOLOROW DIOD
                for (int i = 0; i < 5; i++) {
                    if (AktualnyStan.getObroty() >= wartosc_obrotow[i] && AktualnyStan.getObroty() < 7000.0) {
                        diody[i].zmiana_wypelnienia(kolory[i]);
                    }
                    else if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
                        diody[i].zmiana_wypelnienia({ 255,0,0 });
                    }
                    else {
                        diody[i].zmiana_wypelnienia({ 40,40,40 });
                    }
                }


                zegar_dla_danych.restart();
            }

            //TLO CALEGO OKNA
            window.clear(sf::Color(30, 30, 30));

            //WYSWIETLANIE WSZYSTKIEGO
            obrotomierz.rysuj(window);
            bieg.rysuj(window, bieg, AktualnyStan.getGear(), 0, "0");
            obroty.rysuj(window, obroty, AktualnyStan.getObroty(), 0, "0");
            wskazowka_obrotomierz.rysuj(window);

            predkosciomierz.rysuj(window);
            predkosc.rysuj(window, predkosc, AktualnyStan.getPredkosc(), 0, "0");
            wskazowka_predkosciomierz.rysuj(window);

            temperatura_oleju.rysuj(window);
            wskazowka_tempoleju.rysuj(window);

            bateria.rysuj(window, bateria, AktualnyStan.getBateria(), 2, "V");
            bateria_zdj.rysuj(window);

            woda.rysuj(window, woda, AktualnyStan.getTempChlodnicy(), 2, "C");
            woda_zdj.rysuj(window);


            obramowka_rpm.rysuj(window);

            for (int i = 0; i < 5; i++) {
                diody[i].rysuj(window);
            }

            ramka.rysuj(window);

            window.display();
        }

        logi.close();
        return 0;
    }