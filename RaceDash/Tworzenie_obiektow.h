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

//DLA OBIEKTOW NIEZALEZNCYH OD TRYBOW
class Rodzic {
public:
    Rodzic() = default;
    virtual void utworzenie_obiektow() = 0;
    virtual void warunki(Pojazd & AktualnyStan, sf::Clock & zegar_dla_migania) = 0 ;
    virtual void hover(sf::Vector2i & poz_myszki) = 0;
    virtual void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock & zegar_dla_danych) = 0;
    virtual void rysowanie_obiektow(sf::RenderWindow & window, Pojazd & AktualnyStan, sf::Clock & zegar_dla_migania) = 0;

};

class Obiekty_wspolne : public Rodzic {
public:
    Prosty_prostokat ramka;
    Proste_kolo diody[5];
    int wartosc_obrotow[5] = { 5000, 5500, 6000, 6500, 6900 };
    sf::Color kolory[5] = { { 50, 205, 50 }, { 255, 255, 0 }, { 255, 140, 0 }, { 255, 80, 0 }, { 255, 0, 0 } };

    Wyswietlanie bateria;

    Wyswietlanie woda;

    Wyswietlanie cisnienie_oleju;

    Ladowanie_grafik paliwo_zdj;
    Ladowanie_grafik rezerwa_zdj;
    Proste_kolo dioda_rezerwy;
    Prosty_prostokat obramowka_paliwo;
    Prosty_prostokat stan_paliwa;
    bool rezerwa = false;

    Obiekty_wspolne(grafiki& grafika) :
        bateria(grafika.czcionka), woda(grafika.czcionka), cisnienie_oleju(grafika.czcionka), 
        paliwo_zdj(grafika.paliwo_png), rezerwa_zdj(grafika.rezerwa_png){ }

    void utworzenie_obiektow() override;
    void warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
    void hover(sf::Vector2i& poz_myszki) override;
    void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) override;
    void rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
};

//DLA TRYBU CYFROWEGO
class Obiekty_cyfrowy : public Rodzic {
public:
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
    Tekst napis_cisnienie_cyfrowy;
    Tekst napis_tempwody_cyfrowy;
    Tekst napis_baterry_cyfrowy;


    Obiekty_cyfrowy(grafiki& grafika) :
        obrotomierz_cyfrowy(grafika.obrotomierz_cyfrowy_png), l_obroty_cyfrowy(grafika.czcionka), bieg_cyfrowy(grafika.czcionka),
        predkosc_cyfrowy(grafika.czcionka), lap_timer(grafika.czcionka), temp_oleju_cyfrowy(grafika.czcionka),
        napis_biegu(grafika.czcionka), napis_predkosci(grafika.czcionka), napis_lap_timer(grafika.czcionka), napis_olej_cyfrowy(grafika.czcionka), 
        napis_cisnienie_cyfrowy(grafika.czcionka), napis_tempwody_cyfrowy(grafika.czcionka), napis_baterry_cyfrowy(grafika.czcionka){  }

    void utworzenie_obiektow() override;
    void warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
    void hover(sf::Vector2i& poz_myszki) override;
    void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) override;
    void rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
};

//DLA TRYBU ANALOGOWEGO
class Obiekty_analogowy : public Rodzic {
public:
    Ladowanie_grafik obrotomierz;
    Ladowanie_grafik wskazowka_obrotomierz;
    Wyswietlanie predkosc;
    Ladowanie_grafik predkosciomierz;
    Ladowanie_grafik wskazowka_predkosciomierz;
    Ladowanie_grafik temperatura_oleju;
    Ladowanie_grafik wskazowka_tempoleju;
    Wyswietlanie bieg;
    Wyswietlanie obroty;
    Proste_kolo obramowka_rpm;
    Proste_kolo obramowka_tempoleju;
    Ladowanie_grafik bateria_zdj;
    Ladowanie_grafik bateria_dead_zdj;
    Ladowanie_grafik woda_zdj;
    Ladowanie_grafik woda_overheat_zdj;
    Ladowanie_grafik cisnienieoleju_zdj;
    Ladowanie_grafik wysokie_cisnienieoleju_zdj;

Obiekty_analogowy(grafiki& grafika) :
    obrotomierz(grafika.obrotomierz_png), wskazowka_obrotomierz(grafika.wskazowka_png), obroty(grafika.czcionka),
    predkosciomierz(grafika.predkosciomierz_png), wskazowka_predkosciomierz(grafika.wskazowka_png), predkosc(grafika.czcionka),
    temperatura_oleju(grafika.olej_png), wskazowka_tempoleju(grafika.wskazowka_png), bieg(grafika.czcionka), bateria_zdj(grafika.bateria_png), 
    bateria_dead_zdj(grafika.bateria_low_png), woda_zdj(grafika.woda_png), woda_overheat_zdj(grafika.woda_overheat_png), 
    cisnienieoleju_zdj(grafika.cisnienieolej_png), wysokie_cisnienieoleju_zdj(grafika.wcisnienieolej_png) {}

void utworzenie_obiektow() override;
void warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
void hover(sf::Vector2i& poz_myszki) override;
void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) override;
void rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) override;
};

class Obiekty_logiczne  {
public:
    bool tryb_cyfrowy = false;
    bool czy_menu_wysuniete = false;
    Menu opcje;

    bool main_menu_otwarte = true;
    bool start_na_testowym = false;
    bool wczytaj_plik = false;
    bool exit = false;
    Menu main_menu;

    bool start_klikniete = false;
    Button start_button;
    bool stop_klikniete = true;
    Button stop_button;

    Rodzic* Aktualny_obiekt;
    Obiekty_wspolne wspolne;
    Obiekty_analogowy analogowy;
    Obiekty_cyfrowy cyfrowy;

   Obiekty_logiczne(grafiki& grafika) :
        opcje(grafika.menu_png, grafika.czcionka), start_button(grafika.czcionka), stop_button(grafika.czcionka),
        main_menu(grafika.main_menu_jpg, grafika.czcionka), wspolne(grafika), analogowy(grafika), cyfrowy(grafika) {}

    void utworzenie_obiektow();
    void warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania);
    void hover(sf::Vector2i& poz_myszki);
    void obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych);
    void rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania);
};