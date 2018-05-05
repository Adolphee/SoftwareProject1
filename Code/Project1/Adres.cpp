#include "Adres.h"


Adres::Adres(int adresID, string land, string provincie, int postcode, string gemeente, string straatnaam, int huisnummer, int bus)
{
	this->adresID = adresID;
	this->land = land;
	this->provincie = provincie;
	this->postcode = postcode;
	this->gemeente = gemeente;
	this->straat = straatnaam;
	this->huisnummer = huisnummer;
	this->bus = bus;
}

Adres::~Adres()
{
}

int Adres::getID()
{
	return adresID;
}

int Adres::getPostcode()
{
	return postcode;
}

int Adres::getHuisnummer()
{
	return huisnummer;
}

int Adres::getBus()
{
	return bus;
}

string Adres::getGemeente()
{
	return gemeente;
}

string Adres::getStraat()
{
	return straat;
}

string Adres::getProvincie()
{
	return provincie;
}

string Adres::getLand()
{
	return land;
}

void Adres::setID(int ID)
{
	this->adresID = ID;
}

void Adres::setBus(int nummer)
{
	this->bus = nummer;
}

void Adres::setStraat(string naam)
{
	this->straat = naam;
}

void Adres::setProvincie(string naam)
{
	this->provincie = naam;
}

void Adres::setGemeente(string naam)
{
	this->gemeente = naam;
}

void Adres::setLand(string naam)
{
	this->land = naam;
}

void Adres::setHuisnummer(int nummer)
{
	this->huisnummer = nummer;
}

void Adres::setPostcode(int code)
{
	this->postcode = code;
}
