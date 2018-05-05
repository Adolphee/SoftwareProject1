#pragma once
#include "stdafx.h"

enum Horoscoop { PRIVE_HO, WAT, VIS, RAM, STI, TWE, KRE, LEE, MAA, WEE, SCH, BOO, STE };
enum Haarkleur { PRIVE_HK, ZWART_HAAR, BLOND_HAAR, BRUIN_HAAR, GRIJS_HAAR, };
enum Oogkleur { PRIVE_OK, ZWART, BLAUW, GROEN, BRUIN, GRIJS };
enum LoveStatus { PRIVE_LS, BEZET, OPEN_RELATIE, SINGLE, BLIJKBAAR_VERVLOEKT };

class Extras
{
private:
	int extrasID;
	int lengte;
	string muziekstijl;
	Horoscoop horoscoop = PRIVE_HO;
	Haarkleur haar = PRIVE_HK;
	Oogkleur ogen = PRIVE_OK;
	LoveStatus status = PRIVE_LS;
public:
	Extras(int ID, Horoscoop horos, Haarkleur haar, Oogkleur ogen, int lengte, LoveStatus love, string muziek);
	Extras(int ID, string horos, string haar, string ogen, int lengte, string love, string muziek);

	~Extras();
	//Deze methode is deel van mijn MatchMaking algoritme
	static double compare(Extras*, Extras*);
	//getters as usual
	int getID();
	int getLengte();
	// Deze volgende getters returnen een string die meteen in de database kan geschreven worden.
	string getHoroscoop();
	string getHaarkleur();
	string getOogKleur();
	string getStatus();
	string getMuziekstijl();

	//Om de enums te gebruiken in een zin.
	string horoscoop_voluit();
	string haarkleur_voluit();
	string oogkleur_voluit();
	string status_voluit();

	//klassieke setters, I guess...
	void setID(int);
	void setHoroscoop(Horoscoop);
	void setHaarkleur(Haarkleur);
	void setOogkleur(Oogkleur);
	void setLengte(int);
	void setStatus(LoveStatus);
	void setMuziekstijl(string);

};

