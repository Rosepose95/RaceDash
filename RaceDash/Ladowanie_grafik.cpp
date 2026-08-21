#include <iostream>
#include <string>
#include "Ladowanie_grafik.h"

using namespace std;

bool grafiki::zaladuj_grafike() {

    if (czcionka.openFromFile("font/Gameplay.ttf") == false) {
        return 0;
    }
    if (wskazowka_png.loadFromFile("grafika/wskazowka.png") == false) {
        return 0;
    }
    if (obrotomierz_png.loadFromFile("grafika/obrotomierz.png") == false) {
        return 0;
    }
    if (predkosciomierz_png.loadFromFile("grafika/predkosciomierz.png") == false) {
        return 0;
    }
    if (olej_png.loadFromFile("grafika/tempoleju.png") == false) {
        return 0;
    }
    if (bateria_png.loadFromFile("grafika/car-battery.png") == false) {
        return 0;
    }
    if (woda_png.loadFromFile("grafika/temp-wody.png") == false) {
        return 0;
    }
    if (paliwo_png.loadFromFile("grafika/fuel.png")==false) {
        return 0;
    }
    if (rezerwa_png.loadFromFile("grafika/rezerwa.png") == false) {
        return 0;
    }
    if (bateria_low_png.loadFromFile("grafika/car-battery-low.png") == false) {
        return 0;
    }
    if (woda_overheat_png.loadFromFile("grafika/temp-wody-over.png") == false) {
        return 0;
    }
    if (cisnienieolej_png.loadFromFile("grafika/cisnienie_oleju.png") == false) {
        return 0;
    }
    if (wcisnienieolej_png.loadFromFile("grafika/wcisnienie_oleju.png") == false) {
        return 0;
    }
    if (menu_png.loadFromFile("grafika/menu.png") == false) {
        return 0;
    }

    return true;
}