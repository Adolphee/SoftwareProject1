#include "Profiles.h"



const string currentDate() {
	//credits: http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	//Ik heb deze aangepast.
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	return buf;
}



int rdn(string datum) {
	//Datum omzetten in een int zodat aantal dagen berekenen tussen 2 datums mogelijk is.
	//Ik heb de methode van StackOverflow getransformeerd zodat het met een string werkt ipv 3 integers als parameters.
	//Inspiratie: http://stackoverflow.com
	int y = atoi(datum.substr(0, 4).c_str());
	int m = atoi(datum.substr(5, 2).c_str());
	int d = atoi(datum.substr(8, 2).c_str());

	if (m < 3)
		y--, m += 12;
	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}



Profiles::Profiles(int ID, string username, string naam, string voornaam, string geboortedatum)
{
	this->profileID = ID;
	this->username = username;
	this->naam = naam;
	this->voornaam = voornaam;
	this->geboorteDatum = geboortedatum;
}

Profiles::~Profiles()
{
}

int Profiles::leeftijd()
{
	if (geboorteDatum != "") { return ((rdn(currentDate()) - rdn(geboorteDatum)) / 365.25); } // .25 --> schrikkeljaren meetellen, just in case.
	return 0;
}

int Profiles::getID()
{
	return profileID;
}

string Profiles::getBeschrijving()
{
	return beschrijving;
}


string Profiles::getUsername()
{
	return username;
}

string Profiles::getNaam()
{
	return naam;
}

string Profiles::getVoornaam()
{
	return voornaam;
}

string Profiles::getGeboorteDatum()
{
	return geboorteDatum;
}

int Profiles::getInterestID()
{
	return interestID;
}

int Profiles::getExtrasID()
{
	return extrasID;
}

int Profiles::getWinksReceived()
{
	return winksReceived;
}

int Profiles::getWinksToGive()
{
	return winksToGive;
}

Geslacht Profiles::getGeslacht()
{
	return geslacht;
}

Geslacht Profiles::getZoekt()
{
	return zoekt;
}

string Profiles::geslacht_voluit()
{
	stringstream ss;
	switch (geslacht)
	{
	case MAN: ss << "Man";
		break;
	case VROUW: ss << "Vrouw";
		break;
	case _TRANS_M: ss << "Transgender Mannelijk";
		break;
	case _TRANS_F: ss << "Transgender Vrouwelijk";
		break;
	case _UNKNOWN: ss << "Onbekend";
		break;
	default:
		break;
	}
	return ss.str();
}

string Profiles::zoekt_voluit()
{
	stringstream ss;
	switch (geslacht)
	{
	case MAN: ss << "Man";
		break;
	case VROUW: ss << "Vrouw";
		break;
	case _TRANS_M: ss << "Transgender Mannelijk";
		break;
	case _TRANS_F: ss << "Transgender Vrouwelijk";
		break;
	case _UNKNOWN: ss << "Onbekend";
		break;
	default:
		break;
	}
	return ss.str();
}

void Profiles::setBeschrijving(string aboutMe)
{
	this->beschrijving = aboutMe;
}

void Profiles::setID(int id)
{
	this->profileID = id;
}

void Profiles::setUsername(string name)
{
	this->username = name;
}

void Profiles::setNaam(string naam)
{
	this->naam = naam;
}

void Profiles::setVoornaam(string voornaam)
{
	this->voornaam = voornaam;
}

void Profiles::setGeboorteDatum(string datum)
{
	this->geboorteDatum = datum;
}

void Profiles::setInterestID(int ID)
{
	this->interestID = ID;
}

void Profiles::setExtrasID(int ID)
{
	this->extrasID = ID;
}

void Profiles::setWinksReceived(int aantal)
{
	this->winksReceived = aantal;
}

void Profiles::setWinksToGive(int aantal)
{
	this->winksToGive = aantal;
}

void Profiles::setGeslacht(Geslacht geslacht)
{
	this->geslacht = geslacht;
}

void Profiles::setZoekt(Geslacht geslacht)
{
	this->zoekt = geslacht;
}
