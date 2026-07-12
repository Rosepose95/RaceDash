#pragma once
#include <fstream>

class DaneSilnika {
protected:
	float tempOleju = 0.0;
	float obroty = 0.0;
	float tempChlodnicy = 0.0;

public:
	DaneSilnika(float to, float o, float tc) : tempOleju(to), obroty(o), tempChlodnicy(tc){}
	DaneSilnika() = default;

};

class DanePojazdu {
protected:
	float predkosc = 0.0;
	float bateria = 0.0;

public:
	DanePojazdu(float p, float b) : predkosc(p), bateria(b){}
	DanePojazdu() = default;

};

class Pojazd : private DaneSilnika, private DanePojazdu {

	float czas;

public:
	Pojazd(float t,float to, float o, float tc, float p, float b): czas(t),DaneSilnika(to,o,tc), DanePojazdu(p,b){}
	Pojazd() = default;


	float getTempoleju() { return tempOleju;}
	float getTempChlodnicy() { return tempChlodnicy;}
	float getPredkosc() { return predkosc;}
	float getBateria() { return bateria;}

};


bool odczyt(std::fstream& logi, Pojazd& AktualnyStan);