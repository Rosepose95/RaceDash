#include <iostream>
#include <string>
#include "Tworzenie_obiektow.h"

using namespace std;

void All_objects::Utworzenie_obiektow() {

    if (grafika.zaladuj_grafike() == false) {
        cout << "Blad w plikach grafik" << endl;
    }

    tryb_cyfrowy = false;

    opcje = Menu(grafika.menu_png, grafika.czcionka);
    opcje.wymiary_zdj({ 730,30 }, 0.07);
    opcje.aktualizuj_wymiary_ramki({ 630,10 }, { 160,150 }, { 0,0,0,125 }, { 255,0,0 }, 5);
    opcje.aktualizuj_wymiary_guzikow({ 645,70 }, { 645, 120 }, { 130,30 }, sf::Color::Transparent, { 255,0,0 }, 2);
    opcje.set_text("Zegary analogowe", "Zegary cyfrowe", "Menu", { 650,80 }, { 650, 130 }, { 635,20 }, 10);

    //RYSOWANIE OBROTOMIERZA
    obrotomierz = Ladowanie_grafik(grafika.obrotomierz_png);
    obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
    obrotomierz.zmiana_wielkosc(0.7);

    //RYSOWANIE WSKAZOWKI OBROTOMIERZA
    wskazowka_obrotomierz = Ladowanie_grafik(grafika.wskazowka_png);
    wskazowka_obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
    wskazowka_obrotomierz.aktualizuj_katy(8000.0, 0.0, 0.0, 270.0);
    wskazowka_obrotomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_obrotomierz.zmiana_wielkosc(0.6);

    //WYSWITLANIE OBROTOW ORAZ PROSTOKATA W KTORYM JEST TEKST
    obroty = Wyswietlanie(grafika.czcionka);
    obroty.aktualizuj_prostokat({ 60.0, 30.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 30.0 ,15.0 }, { 470.0, 370.0 });
    obroty.aktualizuj_tekst(15, { 255, 255, 255 }, { 450.0, 360.0 });

    //RYSOWANIE PREDKOSCIOMIERAZA
    predkosciomierz = Ladowanie_grafik(grafika.predkosciomierz_png);
    predkosciomierz.aktualizuj_polozenie({ 650.0, 300.0 });
    predkosciomierz.zmiana_wielkosc(0.45);

    //RYSOWANIE WSKAZOWKI PREDKOSCIOMIERAZA
    wskazowka_predkosciomierz = Ladowanie_grafik(grafika.wskazowka_png);
    wskazowka_predkosciomierz.aktualizuj_polozenie({ 675.0, 300.0 });
    wskazowka_predkosciomierz.aktualizuj_katy(220.0, 0.0, 0.0, 340.0);
    wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_predkosciomierz.zmiana_wielkosc(0.5);

    //WYSWITLANIE PREDKOSCI ORAZ PROSTOKATA W KTORYM JEST TEKST
    predkosc = Wyswietlanie(grafika.czcionka);
    predkosc.aktualizuj_prostokat({ 30.0, 17.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 15.0, 13.5 }, { 735.0, 370.0 });
    predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 725.0, 360.0 });

    //RYSOWANIE TEMPERATURY OLEJU
    temperatura_oleju = Ladowanie_grafik(grafika.olej_png);
    temperatura_oleju.aktualizuj_polozenie({ 120.0, 300.0 });
    temperatura_oleju.zmiana_wielkosc(0.4);

    //RYSOWANIE WSKAZOWKI TEMPERATURY OLEJU
    wskazowka_tempoleju = Ladowanie_grafik(grafika.wskazowka_png);
    wskazowka_tempoleju.aktualizuj_polozenie({ 145.0, 300.0 });
    wskazowka_tempoleju.aktualizuj_katy(150.0, 50.0, 0.0, 300.0);
    wskazowka_tempoleju.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_tempoleju.zmiana_wielkosc(0.4);

    //RYSOWANIE BIEGU ORAZ JEGO OBRAMOWKI
    bieg = Wyswietlanie(grafika.czcionka);
    bieg.aktualizuj_prostokat({ 30.0, 50.0 }, { 30, 30, 30 }, { 255, 255, 255 }, 2, { 15.0, 25.0 }, { 400.0, 350.0 });
    bieg.aktualizuj_tekst(32, { 255,255,255 }, { 390.0, 330.0 });

    //RYSOWANIE OBRAMOWKI OBROTOMIERZA
    obramowka_rpm.aktualizuj_kolo(140, { 0,255,0 }, { 0,0,0,0 }, 12, { 405.0,305.0 });

    //RYSOWANIE OBRAMOWKI TEMP OLEJU
    obramowka_tempoleju.aktualizuj_kolo(105, { 0, 0, 255 }, { 0,0,0,0 }, 8, { 145.0,310.0 });

    //RYSOWANIE OBRAMOWKI CALEGO OKNA
    ramka.aktualizuj_prostokat({ 800.0, 600.0 }, { sf::Color::Transparent }, { 35, 35, 40 }, -5, { 0.0, 0.0 });

    //ALA DIODY NA GORZE EKRANU (dla oborotow)
    for (int i = 0; i < 5; i++) {
        diody[i].aktualizuj_kolo(10, { 0,0,0 }, { 0,255,0 }, 2, { 320.0f + (i * 40.0f), 100.0f });
    }

    //PROGI DLA ZMIANY KOLOROW DIOD
    wartosc_obrotow[0] = 5000;
    wartosc_obrotow[1] = 5500;
    wartosc_obrotow[2] = 6000;
    wartosc_obrotow[3] = 6500;
    wartosc_obrotow[4] = 6900;
    sf::Color kolory[5] = { { 50, 205, 50 }, { 255, 255, 0 }, { 255, 140, 0 }, { 255, 80, 0 }, { 255, 0, 0 } };

    //WYSWIETLANIE DANYCH O BATERII
    bateria = Wyswietlanie(grafika.czcionka);
    bateria.aktualizuj_prostokat({ 100.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 50.0, 20.0 }, { 130.0, 540.0 });
    bateria.aktualizuj_tekst(20, { 255,255,255 }, { 95.0, 530.0 });

    //LADOWANIE GRAFIKI BATERII
    bateria_zdj = Ladowanie_grafik(grafika.bateria_png);
    bateria_zdj.aktualizuj_polozenie({ 40.0, 540.0 });
    bateria_zdj.zmiana_wielkosc(0.125);

    bateria_dead_zdj = Ladowanie_grafik(grafika.bateria_low_png);
    bateria_dead_zdj.aktualizuj_polozenie({ 40.0, 540.0 });
    bateria_dead_zdj.zmiana_wielkosc(0.125);

    //WYSWIETLANIE TEMP WODY
    woda = Wyswietlanie(grafika.czcionka);
    woda.aktualizuj_prostokat({ 100.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 50.0, 20.0 }, { 130.0, 480.0 });
    woda.aktualizuj_tekst(20, { 255,255,255 }, { 95.0, 470.0 });

    //LADOWANIE GRAFIKI WODY
    woda_zdj = Ladowanie_grafik(grafika.woda_png);
    woda_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
    woda_zdj.zmiana_wielkosc(0.125);

    //LADOWANIE GRAFIKI PRZEGRZANIA WODY
    woda_overheat_zdj = Ladowanie_grafik(grafika.woda_overheat_png);
    woda_overheat_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
    woda_overheat_zdj.zmiana_wielkosc(0.125);

    //LADOWANIE CISNIENIA OLEJU
    cisnienie_oleju = Wyswietlanie(grafika.czcionka);
    cisnienie_oleju.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, { 340.0, 480.0 });
    cisnienie_oleju.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 470.0 });

    //LADOWANIE GRAFIKI CISNIENIE OLEJU
    cisnienieoleju_zdj = Ladowanie_grafik(grafika.cisnienieolej_png);
    cisnienieoleju_zdj.aktualizuj_polozenie({ 240.0, 480.0 });
    cisnienieoleju_zdj.zmiana_wielkosc(0.125);

    //LADOWANIE GRAFIKI ZA WYSOKIE CISNIENIE OLEJU 
    wysokie_cisnienieoleju_zdj = Ladowanie_grafik(grafika.wcisnienieolej_png);
    wysokie_cisnienieoleju_zdj.aktualizuj_polozenie({ 240.0, 480.0 });
    wysokie_cisnienieoleju_zdj.zmiana_wielkosc(0.125);

    //WYSWIETLANIE GRAFIKI PALIWA
    paliwo_zdj = Ladowanie_grafik(grafika.paliwo_png);
    paliwo_zdj.aktualizuj_polozenie({ 550.0, 550 });
    paliwo_zdj.zmiana_wielkosc(0.1);

    //KOLKO DLA REZERWY
    rezerwa_zdj = Ladowanie_grafik(grafika.rezerwa_png);
    rezerwa_zdj.aktualizuj_polozenie({ 585.0, 510 });
    rezerwa_zdj.zmiana_wielkosc(0.05);

    //OBRAMOWKA DLA REZERWY
    dioda_rezerwy.aktualizuj_kolo(13, { 0,0,0 }, sf::Color::Transparent, 4, { 587.0, 512 });

    //PROSTOKAT OBRAMOWKA POZIOMU PALIWA
    obramowka_paliwo.aktualizuj_prostokat({ 100,30 }, sf::Color::Transparent, { 0,0,0 }, 5, { 600, 535 });

    //PROSTOKAT WSKAZUJACY POZIOM PALIWA
    stan_paliwa.aktualizuj_prostokat({ 100,30 }, { 0,255,0 }, sf::Color::Transparent, 0, { 600, 535 });

    //ZAPALANIE DIODY OD REZERWY
    rezerwa = false;

    //------------------------------------------------------------------------DLA TRYBU CYFROWEGO
    //OBROTOMIERZ
    obrotomierz_cyfrowy = Ladowanie_grafik(grafika.obrotomierz_cyfrowy_png);
    obrotomierz_cyfrowy.aktualizuj_polozenie({ 400, 200 });
    obrotomierz_cyfrowy.zmiana_wielkosc(0.7);

    //PASEK OBROTOW
    obroty_cyfrowy.aktualizuj_prostokat({ 570,60 }, { 0,255,0 }, sf::Color::Transparent, 0, { 100,175 });

    //WYSWIETLANIE OBROTOW
    l_obroty_cyfrowy = Wyswietlanie(grafika.czcionka);
    l_obroty_cyfrowy.aktualizuj_tekst(30, { 255, 255, 255 }, { 620.0, 135.0 });

    //BIEG 
    bieg_cyfrowy = Wyswietlanie(grafika.czcionka);
    bieg_cyfrowy.aktualizuj_tekst(60, { 255,255,255 }, { 360.0, 320.0 });

    ramka_biegu.aktualizuj_kolo(65, { 255,255,255 }, sf::Color::Transparent, 5, { 382.0, 340.0 });

    napis_biegu = Tekst(grafika.czcionka);
    napis_biegu.aktualizuj_napis("GEAR", { 360, 290 }, 15, { 255,255,255 });

    //PREDKOSC
    predkosc_cyfrowy = Wyswietlanie(grafika.czcionka);
    predkosc_cyfrowy.aktualizuj_tekst(30, { 255,255,255 }, { 190.0, 330.0 });
    ramka_predkosci.aktualizuj_kolo(55, { 255,255,255 }, sf::Color::Transparent, 5, { 220, 340 });
    napis_predkosci = Tekst(grafika.czcionka);
    napis_predkosci.aktualizuj_napis("KM/H", { 200, 300 }, 15, { 255,255,255 });

    //LAP TIMER
    lap_timer = Wyswietlanie(grafika.czcionka);
    lap_timer.aktualizuj_tekst(30, { 255,255,255 }, { 500.0, 330.0 });
    ramka_lap_timer.aktualizuj_kolo(60, { 255,255,255 }, sf::Color::Transparent, 5, { 540, 340 });
    napis_lap_timer = Tekst(grafika.czcionka);
    napis_lap_timer.aktualizuj_napis("Lap time", { 500, 300 }, 15, { 255,255,255 });

    //TEMP OLEJU
    temp_oleju_cyfrowy = Wyswietlanie(grafika.czcionka);
    temp_oleju_cyfrowy.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, { 340.0, 540.0 });
    temp_oleju_cyfrowy.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 530.0 });
    napis_olej_cyfrowy = Tekst(grafika.czcionka);
    napis_olej_cyfrowy.aktualizuj_napis(" Oil\ntemp", { 220.0, 525.0 }, 15, { 255,255,255 });

    //GUZIK STARTU
    start_klikniete = false;
    start_button = Button(grafika.czcionka);
    start_button.aktualizuj_wymiary({ 20,30 }, { 90,40 }, sf::Color::Transparent, { 165,0,0,200 }, 5);
    start_button.set_napis("Start", { 30,40 }, 20);

    //GUZIK STOP
    stop_klikniete = true;
    stop_button = Button(grafika.czcionka);
    stop_button.aktualizuj_wymiary({ 20,30 }, { 90,40 }, sf::Color::Transparent, { 165,0,0,200 }, 5);
    stop_button.set_napis("Stop", { 30,40 }, 20);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
void All_objects::rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    window.clear(sf::Color(30, 30, 30));

    //WYSWIETLANIE DLA TRYBU ANALAGOWEOG
    if (tryb_cyfrowy == false) {
        //WYSWIETLANIE BIEGU
        bieg.rysuj(window, AktualnyStan.getGear(), 0, "0");

        //OBROTY DLA ANALOGOWEGO
        obrotomierz.rysuj(window);
        obroty.rysuj(window, AktualnyStan.getObroty(), 0, "0");
        wskazowka_obrotomierz.rysuj(window);
        obramowka_rpm.rysuj(window);
        obroty.rysuj(window, AktualnyStan.getObroty(), 0, "0");

        //PREDKOSCIOMIERZ
        predkosciomierz.rysuj(window);
        predkosc.rysuj(window, AktualnyStan.getPredkosc(), 0, "0");
        wskazowka_predkosciomierz.rysuj(window);

        //TEMP OLEJU
        temperatura_oleju.rysuj(window);
        wskazowka_tempoleju.rysuj(window);
        obramowka_tempoleju.rysuj(window);
    }
    //WYSWIETLANIE DLA TRYBU CYFROWEGO
    else {
        //WYSWIETLANIE BIEGU
        bieg_cyfrowy.rysuj(window, AktualnyStan.getGear(), 0, "0");
        ramka_biegu.rysuj(window);
        napis_biegu.rysuj(window);

        //OBROTY DLA CYFROWEGO
        obroty_cyfrowy.rysuj(window);
        obrotomierz_cyfrowy.rysuj(window);

        //LICZBA OBROTOW
        l_obroty_cyfrowy.rysuj(window, AktualnyStan.getObroty(), 0, " RPM");

        //PREDKOSC
        predkosc_cyfrowy.rysuj(window, AktualnyStan.getPredkosc(), 0, "0");
        ramka_predkosci.rysuj(window);
        napis_predkosci.rysuj(window);

        //TEMP OLEJU
        temp_oleju_cyfrowy.rysuj(window, AktualnyStan.getTempoleju(), 0, " C");
        napis_olej_cyfrowy.rysuj(window);

        //LAP TIMER
        lap_timer.rysuj(window, AktualnyStan.getCzas() / 1000.0f, 1, " s");
        napis_lap_timer.rysuj(window);
        ramka_lap_timer.rysuj(window);
    }

    //DIODY OBROTOW
    for (int i = 0; i < 5; i++) {
        diody[i].rysuj(window);
    }

    //CZESC WSPOLNA DLA OBU TRYBOW WYSWIETLANIA
    ramka.rysuj(window);

    //MENU/OPCJE
    opcje.rysuj_zdj(window);
    opcje.rysuj_menu(window);

    //TEMP WODY
    woda.rysuj(window, AktualnyStan.getTempChlodnicy(), 1, "C");
    woda.alarm_gorny(AktualnyStan.getTempChlodnicy(), 110.0, 120.0, zegar_dla_migania, woda_overheat_zdj, woda_zdj, window);

    //BATERIA
    bateria.rysuj(window, AktualnyStan.getBateria(), 1, "V");
    if (AktualnyStan.getBateria() < 12.0) {
        bateria_dead_zdj.rysuj(window);
        bateria.zmiana_koloru_obramowki({ 255, 0, 0 });
    }
    else {
        bateria_zdj.rysuj(window);
        bateria.zmiana_koloru_obramowki({ 0, 255, 0 });
    }

    //CISNIENIE OLEJU
    cisnienie_oleju.rysuj(window, AktualnyStan.getCisnienie(), 1, " Bar");
    if (AktualnyStan.getCisnienie() >= 2.5 && AktualnyStan.getCisnienie() < 6.7) {
        cisnienieoleju_zdj.rysuj(window);
        cisnienie_oleju.zmiana_koloru_obramowki({ 0,255,0 });
    }
    else if (AktualnyStan.getCisnienie() >= 1.0 && AktualnyStan.getCisnienie() < 2.5) {
        wysokie_cisnienieoleju_zdj.rysuj(window);
        cisnienie_oleju.zmiana_koloru_obramowki({ 255,165,0 });
    }
    else {
        if ((AktualnyStan.getCisnienie() < 1.0 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) || (AktualnyStan.getCisnienie() >= 6.7 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250)) {
            wysokie_cisnienieoleju_zdj.rysuj(window);
            cisnienie_oleju.zmiana_koloru_obramowki({ 255,0,0 });
        }
        else {
            cisnienieoleju_zdj.rysuj(window);
            cisnienie_oleju.zmiana_koloru_obramowki({ sf::Color::Transparent });
        }
    }

    //PALIWO, REZERWA
    paliwo_zdj.rysuj(window);
    obramowka_paliwo.rysuj(window);
    stan_paliwa.rysuj(window);
    dioda_rezerwy.rysuj(window);

    if (rezerwa == true) {
        rezerwa_zdj.rysuj(window);
    }

    if (start_klikniete == false) {
        start_button.rysuj(window);
    }

    if (stop_klikniete == false) {
        stop_button.rysuj(window);
    }

    window.display();
}