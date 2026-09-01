#include <SFML/Graphics.hpp>
#include "dane.h"
#include "wyswietlanie.h"
#include "Ladowanie_grafik.h"
#include "menu.h"

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

        //ZALADOWANIE GRAFIK

        grafiki grafika;
        if (grafika.zaladuj_grafike() == false) {
            cout << "Blad w plikach grafik"<<endl;
            return 0;
        }

        //MENU
        bool tryb_cyfrowy=false;

        Menu opcje(grafika.menu_png, grafika.czcionka);
        opcje.wymiary_zdj({ 730,30 }, 0.07);
        opcje.aktualizuj_wymiary({ 630,10 }, { 160,150 }, { 0,0,0,125 }, { 255,0,0 }, 5);
        opcje.set_tekst("Zegary analogowe", { 645,70 }, "Zegary cyfrowe", { 645, 120 }, "Menu", { 635,20 }, 10);
        opcje.aktualizuj_tlo_napisow({ 640,60 }, { 640, 110 }, { 130,30 }, sf::Color::Transparent, { 0,255,0 }, {255,0,0}, 2);


        //RYSOWANIE OBROTOMIERZA
        Ladowanie_grafik obrotomierz(grafika.obrotomierz_png);
        obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
        obrotomierz.zmiana_wielkosc(0.7);

        //RYSOWANIE WSKAZOWKI OBROTOMIERZA
        Ladowanie_grafik wskazowka_obrotomierz(grafika.wskazowka_png);
        wskazowka_obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
        wskazowka_obrotomierz.aktualizuj_katy(8000.0, 0.0, 0.0, 270.0);
        wskazowka_obrotomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
        wskazowka_obrotomierz.zmiana_wielkosc(0.6);

        //WYSWITLANIE OBROTOW ORAZ PROSTOKATA W KTORYM JEST TEKST
        Wyswietlanie obroty(grafika.czcionka);
        obroty.aktualizuj_prostokat({ 60.0, 30.0 }, { 30,30,30 }, { 0,255,0 }, 2, {30.0 ,15.0}, { 470.0, 370.0 });
        obroty.aktualizuj_tekst(15, { 255, 255, 255 }, { 450.0, 360.0 });

        //RYSOWANIE PREDKOSCIOMIERAZA
        Ladowanie_grafik predkosciomierz(grafika.predkosciomierz_png);
        predkosciomierz.aktualizuj_polozenie({ 650.0, 300.0 });
        predkosciomierz.zmiana_wielkosc(0.45);

        //RYSOWANIE WSKAZOWKI PREDKOSCIOMIERAZA
        Ladowanie_grafik wskazowka_predkosciomierz(grafika.wskazowka_png);
        wskazowka_predkosciomierz.aktualizuj_polozenie({ 675.0, 300.0 });
        wskazowka_predkosciomierz.aktualizuj_katy(220.0, 0.0, 0.0, 340.0);
        wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
        wskazowka_predkosciomierz.zmiana_wielkosc(0.5);

        //WYSWITLANIE PREDKOSCI ORAZ PROSTOKATA W KTORYM JEST TEKST
        Wyswietlanie predkosc(grafika.czcionka);
        predkosc.aktualizuj_prostokat({ 30.0, 17.0 }, { 30,30,30 }, { 0,255,0 }, 2, {15.0, 13.5},  { 735.0, 370.0 });
        predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 725.0, 360.0 });

        //RYSOWANIE TEMPERATURY OLEJU
        Ladowanie_grafik temperatura_oleju(grafika.olej_png);
        temperatura_oleju.aktualizuj_polozenie({ 120.0, 300.0 });
        temperatura_oleju.zmiana_wielkosc(0.4);

        //RYSOWANIE WSKAZOWKI TEMPERATURY OLEJU
        Ladowanie_grafik wskazowka_tempoleju(grafika.wskazowka_png);
        wskazowka_tempoleju.aktualizuj_polozenie({ 145.0, 300.0 });
        wskazowka_tempoleju.aktualizuj_katy(150.0, 50.0, 0.0, 300.0);
        wskazowka_tempoleju.ustaw_srodek_obrotu({ 36.0,38.0 });
        wskazowka_tempoleju.zmiana_wielkosc(0.4);

        //RYSOWANIE BIEGU ORAZ JEGO OBRAMOWKI
        Wyswietlanie bieg(grafika.czcionka);
        bieg.aktualizuj_prostokat({ 30.0, 50.0 }, { 30, 30, 30 }, { 255, 255, 255 }, 2, { 15.0, 25.0 }, { 400.0, 350.0 });
        bieg.aktualizuj_tekst(32, { 255,255,255 }, { 390.0, 330.0 });
            

        //RYSOWANIE OBRAMOWKI OBROTOMIERZA
        Proste_kolo obramowka_rpm;
        obramowka_rpm.aktualizuj_kolo(140, { 0,255,0 }, { 0,0,0,0 }, 12, { 405.0,305.0 });

        //RYSOWANIE OBRAMOWKI TEMP OLEJU
        Proste_kolo obramowka_tempoleju;
        obramowka_tempoleju.aktualizuj_kolo(105, { 0, 0, 255 }, { 0,0,0,0 }, 8, { 145.0,310.0 });

        //RYSOWANIE OBRAMOWKI CALEGO OKNA
        Prosty_prostokat ramka;
        ramka.aktualizuj_prostokat({800.0, 600.0}, {sf::Color::Transparent}, {35, 35, 40}, -5, {0.0, 0.0});


        //ALA DIODY NA GORZE EKRANU (dla oborotow)
        Proste_kolo diody[5];
        for (int i = 0; i < 5; i++) {
            diody[i].aktualizuj_kolo(10, { 0,0,0 }, { 0,255,0 }, 2, { 320.0f + (i * 40.0f), 100.0f });
        }

        //PROGI DLA ZMIANY KOLOROW DIOD
        int wartosc_obrotow[5] = { 5000, 5500, 6000, 6500, 6900 };
        sf::Color kolory[5] = { { 50, 205, 50 }, { 255, 255, 0 }, { 255, 140, 0 }, { 255, 80, 0 }, { 255, 0, 0 } };

        //WYSWIETLANIE DANYCH O BATERII
        Wyswietlanie bateria(grafika.czcionka);
        bateria.aktualizuj_prostokat({100.0, 40.0}, {10,10,10}, {100,100,100}, 2, {50.0, 20.0}, {130.0, 540.0});
        bateria.aktualizuj_tekst(20, { 255,255,255 }, {95.0, 530.0});
        
        //LADOWANIE GRAFIKI BATERII
        Ladowanie_grafik bateria_zdj(grafika.bateria_png);
        bateria_zdj.aktualizuj_polozenie({40.0, 540.0});
        bateria_zdj.zmiana_wielkosc(0.125);

        Ladowanie_grafik bateria_dead_zdj(grafika.bateria_low_png);
        bateria_dead_zdj.aktualizuj_polozenie({ 40.0, 540.0 });
        bateria_dead_zdj.zmiana_wielkosc(0.125);

        //WYSWIETLANIE TEMP WODY
        Wyswietlanie woda(grafika.czcionka);
        woda.aktualizuj_prostokat({100.0, 40.0}, {10,10,10}, {100,100,100}, 2, {50.0, 20.0}, {130.0, 480.0});
        woda.aktualizuj_tekst(20, { 255,255,255 }, {95.0, 470.0});

        //LADOWANIE GRAFIKI WODY
        Ladowanie_grafik woda_zdj(grafika.woda_png);
        woda_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
        woda_zdj.zmiana_wielkosc(0.125);

        //LADOWANIE GRAFIKI PRZEGRZANIA WODY
        Ladowanie_grafik woda_overheat_zdj(grafika.woda_overheat_png);
        woda_overheat_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
        woda_overheat_zdj.zmiana_wielkosc(0.125);

        //LADOWANIE CISNIENIA OLEJU
        Wyswietlanie cisnienie_oleju(grafika.czcionka);
        cisnienie_oleju.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, {340.0, 480.0});
        cisnienie_oleju.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 470.0 });

        //LADOWANIE GRAFIKI CISNIENIE OLEJU
        Ladowanie_grafik cisnienieoleju_zdj(grafika.cisnienieolej_png);
        cisnienieoleju_zdj.aktualizuj_polozenie({240.0, 480.0});
        cisnienieoleju_zdj.zmiana_wielkosc(0.125);

        //LADOWANIE GRAFIKI ZA WYSOKIE CISNIENIE OLEJU 
        Ladowanie_grafik wysokie_cisnienieoleju_zdj(grafika.wcisnienieolej_png);
        wysokie_cisnienieoleju_zdj.aktualizuj_polozenie({ 240.0, 480.0 });
        wysokie_cisnienieoleju_zdj.zmiana_wielkosc(0.125);
        

        //WYSWIETLANIE GRAFIKI PALIWA
        Ladowanie_grafik paliwo_zdj(grafika.paliwo_png);
        paliwo_zdj.aktualizuj_polozenie({550.0, 550});
        paliwo_zdj.zmiana_wielkosc(0.1);

        //KOLKO DLA REZERWY
        Ladowanie_grafik rezerwa_zdj(grafika.rezerwa_png);
        rezerwa_zdj.aktualizuj_polozenie({ 585.0, 510 });
        rezerwa_zdj.zmiana_wielkosc(0.05);

        //OBRAMOWKA DLA REZERWY
        Proste_kolo dioda_rezerwy;
        dioda_rezerwy.aktualizuj_kolo(13, {0,0,0}, sf::Color::Transparent, 4, { 587.0, 512 });

        //PROSTOKAT OBRAMOWKA POZIOMU PALIWA
        Prosty_prostokat obramowka_paliwo;
        obramowka_paliwo.aktualizuj_prostokat({ 100,30 }, sf::Color::Transparent, { 0,0,0 }, 5, { 600, 535 });

        //PROSTOKAT WSKAZUJACY POZIOM PALIWA
        Prosty_prostokat stan_paliwa;
        stan_paliwa.aktualizuj_prostokat({ 100,30 }, { 0,255,0 }, sf::Color::Transparent, 0, { 600, 535 });

        //ZAPALANIE DIODY OD REZERWY
        bool rezerwa = false;

        //------------------------------------------------------------------------DLA TRYBU CYFROWEGO
        //OBROTOMIERZ
        Ladowanie_grafik obrotomierz_cyfrowy(grafika.obrotomierz_cyfrowy_png);
        obrotomierz_cyfrowy.aktualizuj_polozenie({400, 200});
        obrotomierz_cyfrowy.zmiana_wielkosc(0.7);

        //PASEK OBROTOW
        Prosty_prostokat obroty_cyfrowy;
        obroty_cyfrowy.aktualizuj_prostokat({570,60}, {0,255,0}, sf::Color::Transparent, 0, {100,175});

        //WYSWIETLANIE OBROTOW
        Wyswietlanie l_obroty_cyfrowy(grafika.czcionka);
        l_obroty_cyfrowy.aktualizuj_tekst(30, { 255, 255, 255 }, { 620.0, 135.0 });

        //BIEG 
        Wyswietlanie bieg_cyfrowy(grafika.czcionka);
        bieg_cyfrowy.aktualizuj_tekst(60, { 255,255,255 }, { 360.0, 320.0 });
        Proste_kolo ramka_biegu;
        ramka_biegu.aktualizuj_kolo(65, { 255,255,255 }, sf::Color::Transparent, 5, { 382.0, 340.0 });
        Tekst napis_biegu(grafika.czcionka);
        napis_biegu.aktualizuj_napis("GEAR", { 360, 290 }, 15, { 255,255,255 });
     
        //PREDKOSC
        Wyswietlanie predkosc_cyfrowy(grafika.czcionka);
        predkosc_cyfrowy.aktualizuj_tekst(30, { 255,255,255 }, { 190.0, 330.0 });
        Proste_kolo ramka_predkosci;
        ramka_predkosci.aktualizuj_kolo(55, { 255,255,255 }, sf::Color::Transparent, 5, { 220, 340 });
        Tekst napis_predkosci(grafika.czcionka);
        napis_predkosci.aktualizuj_napis("KM/H", { 200, 300 }, 15, { 255,255,255 });

        //LAP TIMER
        Wyswietlanie lap_timer(grafika.czcionka);
        lap_timer.aktualizuj_tekst(30, { 255,255,255 }, { 500.0, 330.0 });
        Proste_kolo ramka_lap_timer;
        ramka_lap_timer.aktualizuj_kolo(60, { 255,255,255 }, sf::Color::Transparent, 5, { 540, 340 });
        Tekst napis_lap_timer(grafika.czcionka);
        napis_lap_timer.aktualizuj_napis("Lap time", { 500, 300 }, 15, { 255,255,255 });


        //TEMP OLEJU
        Wyswietlanie temp_oleju_cyfrowy(grafika.czcionka);
        temp_oleju_cyfrowy.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, { 340.0, 540.0 });
        temp_oleju_cyfrowy.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 530.0 });
        Tekst napis_olej_cyfrowy(grafika.czcionka);
        napis_olej_cyfrowy.aktualizuj_napis(" Oil\ntemp", { 220.0, 525.0 }, 15, { 255,255,255 });

        //GUZIK STARTU
        bool start_klikniete = false;

        Button start_button(grafika.czcionka);
        start_button.aktualizuj_wymiary({20,30}, {90,40}, sf::Color::Transparent, {165,0,0,200}, 5);
        start_button.set_napis("Start", { 30,40 }, 20);

        //GUZIK STOP
        bool stop_klikniete = true;

        Button stop_button(grafika.czcionka);
        stop_button.aktualizuj_wymiary({ 20,30 }, { 90,40 }, sf::Color::Transparent, { 165,0,0,200 }, 5);
        stop_button.set_napis("Stop", { 30,40 }, 20);


        while (window.isOpen()) {

            //POZCYCJA MYSZKI
            sf::Vector2i poz_myszki = sf::Mouse::getPosition(window);
            //NAJECHANIE NA GUZIKI
            opcje.obsluga_najechania(poz_myszki.x, poz_myszki.y);
            start_button.obsluga_najechania(poz_myszki.x, poz_myszki.y);
            stop_button.obsluga_najechania(poz_myszki.x, poz_myszki.y);

            while (const auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())                              //sprawdzanie czy kliknieto X w oknie
                {
                    window.close();
                }


                if (const auto* mousevent = event->getIf<sf::Event::MouseButtonPressed>()) {    //mousevent = przycisniecie myszki
                    if (mousevent->button == sf::Mouse::Button::Left) {                         //jesli zostal klikniety lewy przycisk to uzyskujemy dostep do position x,y

                        float position_x = mousevent->position.x;
                        float position_y = mousevent->position.y;

                        if (stop_klikniete == false && stop_button.obsluga_klikniecia(position_x, position_y, stop_klikniete)) {
                            start_klikniete = false;
                        }
                        else if (start_klikniete == false && start_button.obsluga_klikniecia(position_x, position_y, start_klikniete)) {
                            stop_klikniete = false;
                            zegar_dla_danych.restart();
                        }

                        else if (opcje.GETgranice_zdjecia().contains({ position_x, position_y })) {           //sprawdzamy czy myszka zostala kliknieta na granicach zdjecia opcji

                            opcje.wlaczanie_menu();

                        }
                        else {
                            opcje.obsluga_klikniecia(position_x, position_y, tryb_cyfrowy);

                        }

                    }
                }
            }
            //PETLA AKTUALIZUJACA DANE AZ DO KONCA DANYCH W PLIKU
            if (start_klikniete == true) {
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
                        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 50.0, 0.0, { 50, 205, 50 }, { 255, 255, 0 }));
                        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 50.0, 0.0, { 50, 205, 50 }, { 255, 255, 0 }));

                    }

                    else if (AktualnyStan.getPredkosc() > 50 && AktualnyStan.getPredkosc() <= 90) {
                        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 90, 50, { 255, 255, 0 }, { 255, 140, 0 }));
                        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 90, 50, { 255, 255, 0 }, { 255, 140, 0 }));

                    }

                    else if (AktualnyStan.getPredkosc() > 90 && AktualnyStan.getPredkosc() <= 140) {
                        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 140, 90, { 255, 140, 0 }, { 255, 20, 147 }));
                        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 140, 90, { 255, 140, 0 }, { 255, 20, 147 }));

                    }

                    else {
                        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 220, 141, { 255, 0, 0 }, { 180, 0, 0 }));
                        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 220, 141, { 255, 0, 0 }, { 180, 0, 0 }));

                    }

                    //WYSWIETLANIE AKTUALNUCH OBROTOW
                    obroty_cyfrowy.poziom_paliwa(8000.0, 0.0, AktualnyStan.getObroty(), 570, 60);

                    //ZMIANA KOLORU OBRAMOWKI DLA OBROTOW
                    if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
                        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
                        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));

                        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
                        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));

                    }

                    else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
                        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
                        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));

                        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
                        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));




                    }

                    else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() < 7000) {
                        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
                        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));

                        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
                        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));


                    }

                    else {
                        if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
                            obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
                            obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));

                            obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
                            ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));

                        }

                        else {
                            obroty.zmiana_koloru_obramowki(sf::Color::Transparent);
                            obramowka_rpm.zmiana_obramowki(sf::Color::Transparent);

                            obroty_cyfrowy.zmiana_wypelnienia(sf::Color::Transparent);
                            ramka_biegu.zmiana_obramowki(sf::Color::Transparent);

                        }
                    }

                    //ZMIANA KOLORU OBRAMOWKI DLA TEMPERATURY OLEJU
                    if (AktualnyStan.getTempoleju() >= 0 && AktualnyStan.getTempoleju() < 70) {
                        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 0, 255 }, { 0, 150, 255 }));
                        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 0, 255 }, { 0, 150, 255 }));
                    }
                    else if (AktualnyStan.getTempoleju() >= 70 && AktualnyStan.getTempoleju() < 110) {
                        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 150, 255 }, { 50, 205, 50 }));
                        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 150, 255 }, { 50, 205, 50 }));

                    }
                    else if (AktualnyStan.getTempoleju() >= 110 && AktualnyStan.getTempoleju() < 130) {
                        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 50, 205, 50 }, { 255, 140, 0 }));
                        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 50, 205, 50 }, { 255, 140, 0 }));

                    }
                    else {
                        if (AktualnyStan.getTempoleju() >= 130 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
                            obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 255, 0, 0 }, { 255, 0, 0 }));
                            temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 255, 0, 0 }, { 255, 0, 0 }));

                        }
                        else {
                            obramowka_tempoleju.zmiana_obramowki(sf::Color::Transparent);
                            temp_oleju_cyfrowy.zmiana_koloru_obramowki(sf::Color::Transparent);
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

                    //WYSWIETLANIE POZIOMU PALIWA
                    stan_paliwa.poziom_paliwa(100.0, 0.0, AktualnyStan.getFuel(), 100.0, 30.0);

                    if (AktualnyStan.getFuel() >= 0.0 && AktualnyStan.getFuel() < 15.0) {
                        stan_paliwa.zmiana_wypelnienia({ 255,0,0 });
                        rezerwa = true;


                    }
                    else if (AktualnyStan.getFuel() >= 15.0 && AktualnyStan.getFuel() < 40.0) {
                        stan_paliwa.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getFuel(), 40.0, 15.0, { 255,0,0 }, { 255, 220, 0 }));
                        rezerwa = false;
                    }
                    else if (AktualnyStan.getFuel() >= 40.0) {
                        stan_paliwa.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getFuel(), 100.0, 40.0, { 255, 220, 0 }, { 50, 205, 50 }));
                        rezerwa = false;
                    }

                    zegar_dla_danych.restart();
                }
            }

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
                lap_timer.rysuj(window, AktualnyStan.getCzas()/1000.0f, 1, " s");
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

        logi.close();
        return 0;
    }