#pragma once
#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include "Ladowanie_grafik.h"
#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class All_objects{
public:
    bool tryb_cyfrowy = false;

    Menu opcje;
    Ladowanie_grafik obrotomierz;
    Ladowanie_grafik wskazowka_obrotomierz;

    Ladowanie_grafik predkosciomierz;
    Ladowanie_grafik wskazowka_predkosciomierz;
    Wyswietlanie predkosc;


    Ladowanie_grafik temperatura_oleju;
    Ladowanie_grafik wskazowka_tempoleju;


    Wyswietlanie bieg;

    Wyswietlanie obroty;
    Proste_kolo obramowka_rpm;


    Proste_kolo obramowka_tempoleju;


    Prosty_prostokat ramka; 


    Proste_kolo diody[5];
    int wartosc_obrotow[5] = { 5000, 5500, 6000, 6500, 6900 };
    sf::Color kolory[5] = { { 50, 205, 50 }, { 255, 255, 0 }, { 255, 140, 0 }, { 255, 80, 0 }, { 255, 0, 0 } };


    Wyswietlanie bateria;
    Ladowanie_grafik bateria_zdj;
    Ladowanie_grafik bateria_dead_zdj;


    Wyswietlanie woda;
    Ladowanie_grafik woda_zdj;
    Ladowanie_grafik woda_overheat_zdj;


    Wyswietlanie cisnienie_oleju;
    Ladowanie_grafik cisnienieoleju_zdj;
    Ladowanie_grafik wysokie_cisnienieoleju_zdj;


    Ladowanie_grafik paliwo_zdj;
    Ladowanie_grafik rezerwa_zdj;
    Proste_kolo dioda_rezerwy;
    Prosty_prostokat obramowka_paliwo;
    Prosty_prostokat stan_paliwa;
    bool rezerwa = false;

    //------------------------------------------------------------------------DLA TRYBU CYFROWEGO

    Ladowanie_grafik obrotomierz_cyfrowy;
    Prosty_prostokat obroty_cyfrowy;
    Wyswietlanie l_obroty_cyfrowy;


    Wyswietlanie bieg_cyfrowy;
    Proste_kolo ramka_biegu;
    Tekst napis_biegu;


    Wyswietlanie predkosc_cyfrowy;
    Proste_kolo ramka_predkosci;
    Tekst napis_predkosci;


    Wyswietlanie lap_timer;
    Proste_kolo ramka_lap_timer;
    Tekst napis_lap_timer;


    Wyswietlanie temp_oleju_cyfrowy;
    Tekst napis_olej_cyfrowy;


    bool start_klikniete = false;
    Button start_button;
    bool stop_klikniete = true;
    Button stop_button;

    All_objects(grafiki& grafika) : opcje(grafika.menu_png, grafika.czcionka), obrotomierz(grafika.obrotomierz_png), wskazowka_obrotomierz(grafika.wskazowka_png), obroty(grafika.czcionka),
        predkosciomierz(grafika.predkosciomierz_png), wskazowka_predkosciomierz(grafika.wskazowka_png), predkosc(grafika.czcionka), temperatura_oleju(grafika.olej_png),
        wskazowka_tempoleju(grafika.wskazowka_png), bieg(grafika.czcionka), bateria(grafika.czcionka), bateria_zdj(grafika.bateria_png), bateria_dead_zdj(grafika.bateria_low_png),
        woda(grafika.czcionka), woda_zdj(grafika.woda_png), woda_overheat_zdj(grafika.woda_overheat_png), cisnienie_oleju(grafika.czcionka), cisnienieoleju_zdj(grafika.cisnienieolej_png),
        wysokie_cisnienieoleju_zdj(grafika.wcisnienieolej_png), paliwo_zdj(grafika.paliwo_png), rezerwa_zdj(grafika.rezerwa_png), obrotomierz_cyfrowy(grafika.obrotomierz_cyfrowy_png),
        l_obroty_cyfrowy(grafika.czcionka), bieg_cyfrowy(grafika.czcionka), predkosc_cyfrowy(grafika.czcionka), lap_timer(grafika.czcionka), temp_oleju_cyfrowy(grafika.czcionka),
        start_button(grafika.czcionka), stop_button(grafika.czcionka), napis_biegu(grafika.czcionka), napis_predkosci(grafika.czcionka), napis_lap_timer(grafika.czcionka),
        napis_olej_cyfrowy(grafika.czcionka) {}

    void utworzenie_obiektow();
    void warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania);
    void hover(sf::Vector2i& poz_myszki);
    void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych);
    void rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania);

};