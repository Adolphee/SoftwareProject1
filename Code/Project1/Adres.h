#pragma once
#include "stdafx.h"

class Adres
{
public:
	Adres(int adresID, string land, string provincie, int postcode, string gemeente, string  straatnaam, int huisnummer, int bus);
	~Adres();

	int adresID, postcode, huisnummer, bus;
	string land, provincie, gemeente, straat;
	
	int getID(), getPostcode(), getHuisnummer(), getBus();
	string getLand(), getProvincie(), getGemeente(), getStraat();

	void setID(int), setPostcode(int), setHuisnummer(int), setBus(int),
		setLand(string), setProvincie(string), setGemeente(string), setStraat(string);
};

