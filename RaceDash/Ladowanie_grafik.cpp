#include <iostream>
#include <string>
#include "Ladowanie_grafik.h"

using namespace std;

bool grafiki::zaladuj_grafike() {

    if (czcionka.openFromFile("font/Gameplay.ttf") == false) {
        return false;
    }
    if (wskazowka_png.loadFromFile("grafika/wskazowka.png") == false) {
        return false;
    }
    if (obrotomierz_png.loadFromFile("grafika/obrotomierz.png") == false) {
        return false;
    }
     if (obrotomierz_cyfrowy_png.loadFromFile("grafika/obrotomierz_cyfrowy.png") == false) {
            return false;
        }
    if (predkosciomierz_png.loadFromFile("grafika/predkosciomierz.png") == false) {
        return false;
    }
    if (olej_png.loadFromFile("grafika/tempoleju.png") == false) {
        return false;
    }
    if (bateria_png.loadFromFile("grafika/car-battery.png") == false) {
        return false;
    }
    if (woda_png.loadFromFile("grafika/temp-wody.png") == false) {
        return false;
    }
    if (paliwo_png.loadFromFile("grafika/fuel.png")==false) {
        return false;
    }
    if (rezerwa_png.loadFromFile("grafika/rezerwa.png") == false) {
        return false;
    }
    if (bateria_low_png.loadFromFile("grafika/car-battery-low.png") == false) {
        return false;
    }
    if (woda_overheat_png.loadFromFile("grafika/temp-wody-over.png") == false) {
        return false;
    }
    if (cisnienieolej_png.loadFromFile("grafika/cisnienie_oleju.png") == false) {
        return false;
    }
    if (wcisnienieolej_png.loadFromFile("grafika/wcisnienie_oleju.png") == false) {
        return false;
    }
    if (menu_png.loadFromFile("grafika/menu.png") == false) {
        return false;
    }
    if (main_menu_jpg.loadFromFile("grafika/main_menu.jpg") == false) {
        return false;
    }

    return true;
}