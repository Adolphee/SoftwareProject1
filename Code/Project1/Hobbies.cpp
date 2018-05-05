#include "Hobbies.h"

Hobbies::Hobbies(int ID, string naam)
{
	this->hobbiesID = ID;
	this->naam = naam;
}

Hobbies::~Hobbies()
{
}

int Hobbies::getID()
{
	return hobbiesID;
}

string Hobbies::getNaam()
{
	return naam;
}

void Hobbies::setID(int ID)
{
	this->hobbiesID = ID;
}

void Hobbies::setNaam(string naam)
{
	this->naam = naam;
}
