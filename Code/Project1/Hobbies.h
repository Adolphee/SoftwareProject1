#pragma once
#include "stdafx.h"

class Hobbies
{
private:
	int hobbiesID;
	string naam;
public:
	Hobbies(int ID, string naam);
	~Hobbies();

	int getID();
	string getNaam();

	void setID(int);
	void setNaam(string);

};

