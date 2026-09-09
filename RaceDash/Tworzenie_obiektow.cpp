#include <iostream>
#include <string>
#include "Tworzenie_obiektow.h"

using namespace std;

//DLA WSPOLNYCH OBIEKTOW
void Obiekty_wspolne::utworzenie_obiektow(){

    ramka.aktualizuj_prostokat({ 800.0, 600.0 }, { sf::Color::Transparent }, { 35, 35, 40 }, -5, { 0.0, 0.0 });

    for (int i = 0; i < 5; i++) {
        diody[i].aktualizuj_kolo(10, { 0,0,0 }, { 0,255,0 }, 2, { 320.0f + (i * 40.0f), 100.0f });
    }

    bateria.aktualizuj_prostokat({ 100.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 50.0, 20.0 }, { 130.0, 540.0 });
    bateria.aktualizuj_tekst(20, { 255,255,255 }, { 95.0, 530.0 });
 
    woda.aktualizuj_prostokat({ 100.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 50.0, 20.0 }, { 130.0, 480.0 });
    woda.aktualizuj_tekst(20, { 255,255,255 }, { 95.0, 470.0 });
   
    cisnienie_oleju.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, { 340.0, 480.0 });
    cisnienie_oleju.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 470.0 });

    paliwo_zdj.aktualizuj_polozenie({ 550.0, 550 });
    paliwo_zdj.zmiana_wielkosc(0.1);
    rezerwa_zdj.aktualizuj_polozenie({ 585.0, 510 });
    rezerwa_zdj.zmiana_wielkosc(0.05);
    dioda_rezerwy.aktualizuj_kolo(13, { 0,0,0 }, sf::Color::Transparent, 4, { 587.0, 512 });
    obramowka_paliwo.aktualizuj_prostokat({ 100,30 }, sf::Color::Transparent, { 0,0,0 }, 5, { 600, 535 });
    stan_paliwa.aktualizuj_prostokat({ 100,30 }, { 0,255,0 }, sf::Color::Transparent, 0, { 600, 535 });
    rezerwa = false;
}

//DLA WSPOLNYCH OBIEKTOW WARUNKI
void Obiekty_wspolne::warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
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
    
    // woda.alarm_gorny(AktualnyStan.getTempChlodnicy(), 110.0, 120.0, zegar_dla_migania, woda_overheat_zdj, woda_zdj, window);

    if (AktualnyStan.getTempChlodnicy() >= 120.0) {

        if (zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            woda.zmiana_koloru_obramowki({ 255,0,0 });
        }
        else {
            woda.zmiana_koloru_obramowki({ sf::Color::Transparent });
        }
    }
    else if (AktualnyStan.getTempChlodnicy() >= 110.0) {
        woda.zmiana_koloru_obramowki({ 255,165,0 });
    }
    else {
        woda.zmiana_koloru_obramowki({ 0,255,0 });
    }
}

//DLA WSPOLNYCH OBIEKTOW RYSOWANIE
void Obiekty_wspolne::rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    ramka.rysuj(window);
    for (int i = 0; i < 5; i++) {
        diody[i].rysuj(window);
    }

    woda.rysuj(window, AktualnyStan.getTempChlodnicy(), 1, "C");

    bateria.rysuj(window, AktualnyStan.getBateria(), 1, "V");
    if (AktualnyStan.getBateria() < 12.0) {
        bateria.zmiana_koloru_obramowki({ 255, 0, 0 });
    }
    else {
        bateria.zmiana_koloru_obramowki({ 0, 255, 0 });
    }

    cisnienie_oleju.rysuj(window, AktualnyStan.getCisnienie(), 1, " Bar");
    if (AktualnyStan.getCisnienie() >= 2.5 && AktualnyStan.getCisnienie() < 6.7) {
        cisnienie_oleju.zmiana_koloru_obramowki({ 0,255,0 });
    }
    else if (AktualnyStan.getCisnienie() >= 1.0 && AktualnyStan.getCisnienie() < 2.5) {
        cisnienie_oleju.zmiana_koloru_obramowki({ 255,165,0 });
    }
    else {
        if ((AktualnyStan.getCisnienie() < 1.0 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) ||
            (AktualnyStan.getCisnienie() >= 6.7 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250)) {
            cisnienie_oleju.zmiana_koloru_obramowki({ 255,0,0 });
        }
        else {
            cisnienie_oleju.zmiana_koloru_obramowki({ sf::Color::Transparent });
        }
    }

    paliwo_zdj.rysuj(window);
    obramowka_paliwo.rysuj(window);
    stan_paliwa.rysuj(window);
    dioda_rezerwy.rysuj(window);
    if (rezerwa == true) {
        rezerwa_zdj.rysuj(window);
    }
}

void Obiekty_wspolne::hover(sf::Vector2i& poz_myszki) {}
void Obiekty_wspolne::obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) {}

//---------------------------------------------------------------------------------------------------------------------------

//OBIEKTY CYFROWE
void Obiekty_cyfrowy::utworzenie_obiektow() {
    obrotomierz_cyfrowy.aktualizuj_polozenie({ 400, 200 });
    obrotomierz_cyfrowy.zmiana_wielkosc(0.7);
    obroty_cyfrowy.aktualizuj_prostokat({ 570,60 }, { 0,255,0 }, sf::Color::Transparent, 0, { 100,175 });
    l_obroty_cyfrowy.aktualizuj_tekst(30, { 255, 255, 255 }, { 620.0, 135.0 });

    bieg_cyfrowy.aktualizuj_tekst(60, { 255,255,255 }, { 360.0, 320.0 });
    ramka_biegu.aktualizuj_kolo(65, { 255,255,255 }, sf::Color::Transparent, 5, { 382.0, 340.0 });
    napis_biegu.aktualizuj_napis("GEAR", { 360, 290 }, 15, { 255,255,255 });

    predkosc_cyfrowy.aktualizuj_tekst(30, { 255,255,255 }, { 190.0, 330.0 });
    ramka_predkosci.aktualizuj_kolo(55, { 255,255,255 }, sf::Color::Transparent, 5, { 220, 340 });
    napis_predkosci.aktualizuj_napis("KM/H", { 200, 300 }, 15, { 255,255,255 });

    lap_timer.aktualizuj_tekst(30, { 255,255,255 }, { 500.0, 330.0 });
    ramka_lap_timer.aktualizuj_kolo(60, { 255,255,255 }, sf::Color::Transparent, 5, { 540, 340 });
    napis_lap_timer.aktualizuj_napis("Lap time", { 500, 300 }, 15, { 255,255,255 });

    temp_oleju_cyfrowy.aktualizuj_prostokat({ 130.0, 40.0 }, { 10,10,10 }, { 100,100,100 }, 2, { 65.0, 20.0 }, { 340.0, 540.0 });
    temp_oleju_cyfrowy.aktualizuj_tekst(20, { 255,255,255 }, { 305.0, 530.0 });
    napis_olej_cyfrowy.aktualizuj_napis(" Oil\ntemp.", { 210.0, 525.0 }, 15, { 255,255,255 });

    napis_cisnienie_cyfrowy.aktualizuj_napis("  Oil\nPress.", { 210.0, 460 }, 15, { 255,255,255 });
    
    napis_tempwody_cyfrowy.aktualizuj_napis("Water\ntemp.", { 15, 460 }, 15, { 255,255,255 });

    napis_baterry_cyfrowy.aktualizuj_napis("Batt.", { 15, 530 }, 17, { 255,255,255 });
}
//OBIEKTY CYFROWE WARUNKI
void Obiekty_cyfrowy::warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania){
    obroty_cyfrowy.poziom_paliwa(8000.0, 0.0, AktualnyStan.getObroty(), 570, 60);

    if (AktualnyStan.getPredkosc() >= 0 && AktualnyStan.getPredkosc() <= 50) {
        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 50.0, 0.0, { 50, 205, 50 }, { 255, 255, 0 }));
    }
    else if (AktualnyStan.getPredkosc() > 50 && AktualnyStan.getPredkosc() <= 90) {
        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 90, 50, { 255, 255, 0 }, { 255, 140, 0 }));
    }
    else if (AktualnyStan.getPredkosc() > 90 && AktualnyStan.getPredkosc() <= 140) {
        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 140, 90, { 255, 140, 0 }, { 255, 20, 147 }));
    }
    else {
        ramka_predkosci.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 220, 141, { 255, 0, 0 }, { 180, 0, 0 }));
    }

    if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
    }
    else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
    }
    else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() < 7000) {
        obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
        ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
    }
    else {
        if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            obroty_cyfrowy.zmiana_wypelnienia(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
            ramka_biegu.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
        }
        else {
            obroty_cyfrowy.zmiana_wypelnienia(sf::Color::Transparent);
            ramka_biegu.zmiana_obramowki(sf::Color::Transparent);
        }
    }

    if (AktualnyStan.getTempoleju() >= 0 && AktualnyStan.getTempoleju() < 70) {
        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 0, 255 }, { 0, 150, 255 }));
    }
    else if (AktualnyStan.getTempoleju() >= 70 && AktualnyStan.getTempoleju() < 110) {
        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 150, 255 }, { 50, 205, 50 }));
    }
    else if (AktualnyStan.getTempoleju() >= 110 && AktualnyStan.getTempoleju() < 130) {
        temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 50, 205, 50 }, { 255, 140, 0 }));
    }
    else {
        if (AktualnyStan.getTempoleju() >= 130 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            temp_oleju_cyfrowy.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 255, 0, 0 }, { 255, 0, 0 }));
        }
        else {
            temp_oleju_cyfrowy.zmiana_koloru_obramowki(sf::Color::Transparent);
        }
    }
}
//OBIEKTY CYFROWE RYSOWANIE
void Obiekty_cyfrowy::rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    bieg_cyfrowy.rysuj(window, AktualnyStan.getGear(), 0, "0");
    ramka_biegu.rysuj(window);
    napis_biegu.rysuj(window);
    obroty_cyfrowy.rysuj(window);
    obrotomierz_cyfrowy.rysuj(window);
    l_obroty_cyfrowy.rysuj(window, AktualnyStan.getObroty(), 0, " RPM");
    predkosc_cyfrowy.rysuj(window, AktualnyStan.getPredkosc(), 0, "0");
    ramka_predkosci.rysuj(window);
    napis_predkosci.rysuj(window);
    temp_oleju_cyfrowy.rysuj(window, AktualnyStan.getTempoleju(), 0, " C");
    napis_olej_cyfrowy.rysuj(window);
    lap_timer.rysuj(window, AktualnyStan.getCzas() / 1000.0f, 1, " s");
    napis_lap_timer.rysuj(window);
    ramka_lap_timer.rysuj(window);
    napis_cisnienie_cyfrowy.rysuj(window);
    napis_tempwody_cyfrowy.rysuj(window);
    napis_baterry_cyfrowy.rysuj(window);
}
void Obiekty_cyfrowy::hover(sf::Vector2i& poz_myszki) {}
void Obiekty_cyfrowy::obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) {}

//---------------------------------------------------------------------------------------------------------------------------

//OBIEKTY ANALOGOWE
void Obiekty_analogowy::utworzenie_obiektow() {

    obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
    obrotomierz.zmiana_wielkosc(0.7);

    wskazowka_obrotomierz.aktualizuj_polozenie({ 400.0,300.0 });
    wskazowka_obrotomierz.aktualizuj_katy(8000.0, 0.0, 0.0, 270.0);
    wskazowka_obrotomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_obrotomierz.zmiana_wielkosc(0.6);

    predkosciomierz.aktualizuj_polozenie({ 650.0, 300.0 });
    predkosciomierz.zmiana_wielkosc(0.45);

    wskazowka_predkosciomierz.aktualizuj_polozenie({ 675.0, 300.0 });
    wskazowka_predkosciomierz.aktualizuj_katy(220.0, 0.0, 0.0, 340.0);
    wskazowka_predkosciomierz.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_predkosciomierz.zmiana_wielkosc(0.5);

    predkosc.aktualizuj_prostokat({ 30.0, 17.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 15.0, 13.5 }, { 735.0, 370.0 });
    predkosc.aktualizuj_tekst(10, { 255,255,255 }, { 725.0, 360.0 });

    temperatura_oleju.aktualizuj_polozenie({ 120.0, 300.0 });
    temperatura_oleju.zmiana_wielkosc(0.4);

    wskazowka_tempoleju.aktualizuj_polozenie({ 145.0, 300.0 });
    wskazowka_tempoleju.aktualizuj_katy(150.0, 50.0, 0.0, 300.0);
    wskazowka_tempoleju.ustaw_srodek_obrotu({ 36.0,38.0 });
    wskazowka_tempoleju.zmiana_wielkosc(0.4);

    bieg.aktualizuj_prostokat({ 30.0, 50.0 }, { 30, 30, 30 }, { 255, 255, 255 }, 2, { 15.0, 25.0 }, { 400.0, 350.0 });
    bieg.aktualizuj_tekst(32, { 255,255,255 }, { 390.0, 330.0 });

    obroty.aktualizuj_prostokat({ 60.0, 30.0 }, { 30,30,30 }, { 0,255,0 }, 2, { 30.0 ,15.0 }, { 470.0, 370.0 });
    obroty.aktualizuj_tekst(15, { 255, 255, 255 }, { 450.0, 360.0 });
  
    obramowka_rpm.aktualizuj_kolo(140, { 0,255,0 }, { 0,0,0,0 }, 12, { 405.0,305.0 });

    obramowka_tempoleju.aktualizuj_kolo(105, { 0, 0, 255 }, { 0,0,0,0 }, 8, { 145.0,310.0 });

    bateria_zdj.aktualizuj_polozenie({ 40.0, 540.0 });
    bateria_zdj.zmiana_wielkosc(0.125);
    bateria_dead_zdj.aktualizuj_polozenie({ 40.0, 540.0 });
    bateria_dead_zdj.zmiana_wielkosc(0.125);

    woda_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
    woda_zdj.zmiana_wielkosc(0.125);
    woda_overheat_zdj.aktualizuj_polozenie({ 40.0, 480.0 });
    woda_overheat_zdj.zmiana_wielkosc(0.125);

    cisnienieoleju_zdj.aktualizuj_polozenie({ 240.0, 480.0 });
    cisnienieoleju_zdj.zmiana_wielkosc(0.125);
    wysokie_cisnienieoleju_zdj.aktualizuj_polozenie({ 240.0, 480.0 });
    wysokie_cisnienieoleju_zdj.zmiana_wielkosc(0.125);

}

//OBIEKTY ANALOGOWE WARUNKI
void Obiekty_analogowy::warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania){
    wskazowka_obrotomierz.wyliczanie_kata(AktualnyStan.getObroty());
    wskazowka_predkosciomierz.wyliczanie_kata(AktualnyStan.getPredkosc());
    wskazowka_tempoleju.wyliczanie_kata(AktualnyStan.getTempoleju());

    if (AktualnyStan.getPredkosc() >= 0 && AktualnyStan.getPredkosc() <= 50) {
        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 50.0, 0.0, { 50, 205, 50 }, { 255, 255, 0 }));
    }
    else if (AktualnyStan.getPredkosc() > 50 && AktualnyStan.getPredkosc() <= 90) {
        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 90, 50, { 255, 255, 0 }, { 255, 140, 0 }));
    }
    else if (AktualnyStan.getPredkosc() > 90 && AktualnyStan.getPredkosc() <= 140) {
        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 140, 90, { 255, 140, 0 }, { 255, 20, 147 }));
    }
    else {
        predkosc.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getPredkosc(), 220, 141, { 255, 0, 0 }, { 180, 0, 0 }));
    }

    if (AktualnyStan.getObroty() >= 0 && AktualnyStan.getObroty() <= 3500) {
        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 3500, 0, { 50, 205, 50 }, { 255, 140, 0 }));
    }
    else if (AktualnyStan.getObroty() > 3500 && AktualnyStan.getObroty() <= 6000) {
        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 6000, 3500, { 255, 140, 0 }, { 255, 80, 0 }));
    }
    else if (AktualnyStan.getObroty() > 6000 && AktualnyStan.getObroty() < 7000) {
        obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
        obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 7000, 6000, { 255, 80, 0 }, { 255, 0, 0 }));
    }
    else {
        if (AktualnyStan.getObroty() >= 7000 && AktualnyStan.getObroty() <= 8000 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            obroty.zmiana_koloru_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
            obramowka_rpm.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getObroty(), 8000, 7000, { 255, 0, 0 }, { 255, 0, 0 }));
        }
        else {
            obroty.zmiana_koloru_obramowki(sf::Color::Transparent);
            obramowka_rpm.zmiana_obramowki(sf::Color::Transparent);
        }
    }

    if (AktualnyStan.getTempoleju() >= 0 && AktualnyStan.getTempoleju() < 70) {
        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 0, 255 }, { 0, 150, 255 }));
    }
    else if (AktualnyStan.getTempoleju() >= 70 && AktualnyStan.getTempoleju() < 110) {
        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 110, 70, { 0, 150, 255 }, { 50, 205, 50 }));
    }
    else if (AktualnyStan.getTempoleju() >= 110 && AktualnyStan.getTempoleju() < 130) {
        obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 50, 205, 50 }, { 255, 140, 0 }));
    }
    else {
        if (AktualnyStan.getTempoleju() >= 130 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            obramowka_tempoleju.zmiana_obramowki(plynna_zmiana_koloru(AktualnyStan.getTempoleju(), 130, 110, { 255, 0, 0 }, { 255, 0, 0 }));
        }
        else {
            obramowka_tempoleju.zmiana_obramowki(sf::Color::Transparent);
        }
    }
}

//OBIEKTY ANALOGOWE RYSOWANIE
void Obiekty_analogowy::rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    bieg.rysuj(window, AktualnyStan.getGear(), 0, "0");
    obrotomierz.rysuj(window);
    wskazowka_obrotomierz.rysuj(window);
    obramowka_rpm.rysuj(window);
    obroty.rysuj(window, AktualnyStan.getObroty(), 0, "0");
    predkosciomierz.rysuj(window);
    predkosc.rysuj(window, AktualnyStan.getPredkosc(), 0, "0");
    wskazowka_predkosciomierz.rysuj(window);
    temperatura_oleju.rysuj(window);
    wskazowka_tempoleju.rysuj(window);
    obramowka_tempoleju.rysuj(window);

    if (AktualnyStan.getBateria() < 12.0) {
        bateria_dead_zdj.rysuj(window);
    }
    else {
        bateria_zdj.rysuj(window);
    }

    if (AktualnyStan.getCisnienie() >= 2.5 && AktualnyStan.getCisnienie() < 6.7) {
        cisnienieoleju_zdj.rysuj(window);
    }
    else if (AktualnyStan.getCisnienie() >= 1.0 && AktualnyStan.getCisnienie() < 2.5) {
        wysokie_cisnienieoleju_zdj.rysuj(window);
    }
    else {
        if ((AktualnyStan.getCisnienie() < 1.0 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) ||
            (AktualnyStan.getCisnienie() >= 6.7 && zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250)) {
            wysokie_cisnienieoleju_zdj.rysuj(window);
        }
        else {
            cisnienieoleju_zdj.rysuj(window);
        }
    }

    if (AktualnyStan.getTempChlodnicy() >= 120.0) {

        if (zegar_dla_migania.getElapsedTime().asMilliseconds() % 500 > 250) {
            woda_overheat_zdj.rysuj(window);
        }
        else {
            woda_zdj.rysuj(window);
        }
    }
    else if (AktualnyStan.getTempChlodnicy() >= 110.0) {
        woda_overheat_zdj.rysuj(window);
    }
    else {
        woda_zdj.rysuj(window);
    }
}


void Obiekty_analogowy::hover(sf::Vector2i& poz_myszki){}
void Obiekty_analogowy::obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych){}
//---------------------------------------------------------------------------------------------------------------------------

//OBIEKTY LOGICZNE 
void Obiekty_logiczne::utworzenie_obiektow() {

    opcje.wymiary_zdj({ 730,30 }, 0.07);
    opcje.aktualizuj_wymiary_ramki({ 630,10 }, { 160,200 }, { 0,0,0,125 }, { 255,0,0 }, 5);
    opcje.aktualizuj_wymiary_guzikow({ 645,70 }, { 645, 120 }, { 645, 170 }, { 130, 30 }, sf::Color::Transparent, { 255,0,0 }, 2);
    opcje.set_text("Zegary analogowe", "Zegary cyfrowe", "Menu", "Powrot do menu", { 650, 80 }, { 650, 130 }, { 635,20 }, { 650, 180 }, 10, 15);

    main_menu.wymiary_zdj({ 0,0 }, 1);
    main_menu.aktualizuj_wymiary_ramki({ 0,0 }, { 800,600 }, sf::Color::Transparent, { 255,0,255 }, -10);
    main_menu.aktualizuj_wymiary_guzikow({ 330,300 }, { 330, 390 }, { 330, 510 }, { 175, 50 }, { 30,30,30,200 }, { 255,0,0 }, 7);
    main_menu.set_text("       Start na \n testowym pliku ", "Wczytaj plik...", "RaceDash", "Exit", { 330, 305 }, { 340, 405 }, { 170,130 }, { 390, 525 }, 17, 85);

    start_klikniete = false;
    start_button.aktualizuj_wymiary({ 20,30 }, { 90,40 }, sf::Color::Transparent, { 165,0,0,200 }, 5);
    start_button.set_napis("Start", { 30,40 }, 20);

    stop_klikniete = true;
    stop_button.aktualizuj_wymiary({ 20,30 }, { 90,40 }, sf::Color::Transparent, { 165,0,0,200 }, 5);
    stop_button.set_napis("Stop", { 30,40 }, 20);

    wspolne.utworzenie_obiektow();
    analogowy.utworzenie_obiektow();
    cyfrowy.utworzenie_obiektow();

    //NA START ZAWSZE LADUJEMY ANALOGOWY TRYB
    Aktualny_obiekt = &analogowy;
}

void Obiekty_logiczne::warunki(Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    wspolne.warunki(AktualnyStan, zegar_dla_migania);
    Aktualny_obiekt->warunki(AktualnyStan, zegar_dla_migania);
}

//OBIEKTY LOGICZNE OBLSUGA NAJECHANIA MYSZKA NA GUZIK LUB MENU 
void Obiekty_logiczne::hover(sf::Vector2i& poz_myszki) {
    opcje.obsluga_najechania(poz_myszki.x, poz_myszki.y, czy_menu_wysuniete);
    main_menu.obsluga_najechania(poz_myszki.x, poz_myszki.y, main_menu_otwarte);
    start_button.obsluga_najechania(poz_myszki.x, poz_myszki.y);
    stop_button.obsluga_najechania(poz_myszki.x, poz_myszki.y);
}

//OBIEKTY LOGICZNE OBLSUGA KLIKNIECIA
void Obiekty_logiczne::obsluga_klikniecia(float& position_x, float& position_y, sf::Clock& zegar_dla_danych) {

    if (main_menu_otwarte == true && main_menu.obsluga_klikniecia(position_x, position_y, start_na_testowym, wczytaj_plik, exit, main_menu_otwarte)) {

    }
    else if (stop_klikniete == false && stop_button.obsluga_klikniecia(position_x, position_y, stop_klikniete)) {
        start_klikniete = false;

    }
    else if (start_klikniete == false && start_button.obsluga_klikniecia(position_x, position_y, start_klikniete)) {
        stop_klikniete = false;
        zegar_dla_danych.restart();

    }
    else if (opcje.GETgranice_zdjecia().contains({ position_x, position_y })) {           //sprawdzamy czy myszka zostala kliknieta na granicach zdjecia opcji
        opcje.wlaczanie_menu(czy_menu_wysuniete);

    }
    else {
        opcje.obsluga_klikniecia(position_x, position_y, tryb_cyfrowy, tryb_cyfrowy, main_menu_otwarte, czy_menu_wysuniete);
    
        if (tryb_cyfrowy == true) {
            Aktualny_obiekt = &cyfrowy;
        }
        else {
            Aktualny_obiekt = &analogowy;
        }
    }
}

//OBIEKTY LOGICZNE RYSOWANIE OBIEKTOW
void Obiekty_logiczne::rysowanie_obiektow(sf::RenderWindow& window, Pojazd& AktualnyStan, sf::Clock& zegar_dla_migania) {
    window.clear(sf::Color(30, 30, 30));

    if (main_menu_otwarte == true) {
        main_menu.rysuj_zdj(window);
        main_menu.rysuj_menu(window);
    }
    else {
        wspolne.rysowanie_obiektow(window, AktualnyStan, zegar_dla_migania);

        Aktualny_obiekt->rysowanie_obiektow(window, AktualnyStan, zegar_dla_migania);

        if (czy_menu_wysuniete == false) {
            opcje.rysuj_zdj(window);
        }
        else {
            opcje.rysuj_menu(window);
        }

        if (start_klikniete == false) {
            start_button.rysuj(window);
        }

        if (stop_klikniete == false) {
            stop_button.rysuj(window);
        }
    }
    window.display();
}


