#include "Extras.h"



Extras::Extras(int ID, Horoscoop horos, Haarkleur haar, Oogkleur ogen, int lengte, LoveStatus love, string muziek)
{
	this->extrasID = ID;
	this->horoscoop = horos;
	this->haar = haar;
	this->ogen = ogen;
	this->lengte = lengte;
	this->status = love;
	this->muziekstijl = muziek;
}

Extras::Extras(int ID, string horos, string haar, string ogen, int lengte, string love, string muziek)
{
	this->extrasID = ID;
	this->lengte = lengte;
	this->muziekstijl = muziek;
	//Om een of andere reden werkt de switch hier niet. 
	//Heb lang gezocht naar een oplossing maar vond het niet, dus heb ik maar met IF's gewerkt.


	//HOROSCOOP
	if (horos == "NULL") this->horoscoop = PRIVE_HO;
	else if (horos == "WAT") this->horoscoop = WAT;
	else if (horos == "VIS") this->horoscoop = VIS;
	else if (horos == "RAM") this->horoscoop = RAM;
	else if (horos == "STI") this->horoscoop = STI;
	else if (horos == "TWE") this->horoscoop = TWE;
	else if (horos == "KRE") this->horoscoop = KRE;
	else if (horos == "LEE") this->horoscoop = LEE;
	else if (horos == "MAA") this->horoscoop = MAA;
	else if (horos == "WEE") this->horoscoop = WEE;
	else if (horos == "SCH") this->horoscoop = SCH;
	else if (horos == "BOO") this->horoscoop = BOO;
	else if (horos == "STE") this->horoscoop = STE;

	//HAARKLEUR
	if (haar == "NULL") this->haar = PRIVE_HK;
	else if (haar == "ZWART") this->haar = ZWART_HAAR;
	else if (haar == "BLOND") this->haar = BLOND_HAAR;
	else if (haar == "BRUIN") this->haar = BRUIN_HAAR;
	else if (haar == "GRIJS") this->haar = GRIJS_HAAR;

	//OOGKLEUR
	if (ogen == "NULL") this->ogen = PRIVE_OK;
	else if (ogen == "ZWART") this->ogen = ZWART;
	else if (ogen == "BLAUW") this->ogen = BLAUW;
	else if (ogen == "GROEN") this->ogen = GROEN;
	else if (ogen == "BRUIN") this->ogen = BRUIN;
	else if (ogen == "GRIJS") this->ogen = GRIJS;

	//LOVE_STATUS
	if (love == "NULL") this->status = PRIVE_LS;
	else if (love == "BEZET") this->status = BEZET;
	else if (love == "OPEN_RELATIE") this->status = OPEN_RELATIE;
	else if (love == "SINGLE") this->status = SINGLE;
	else if (love == "BLIJKBAAR_VERVLOEKT") this->status = BLIJKBAAR_VERVLOEKT;

}

Extras::~Extras()
{
}

double Extras::compare(Extras* potentieel, Extras* myExtras)
{
	double percentage = 0;
	double verhoging = 100 / 5.009; //zo kan het nooit 100% worden, de perfecte koppel bestaat niet.
									//liefdesstatus tel ik niet meer omdat het geen invloed heeft op hoeveel 2 mensen bij elkaar passen (dat vind ik)
	if (potentieel->getHoroscoop() == myExtras->getHoroscoop()) percentage += verhoging;
	if (potentieel->getHaarkleur() == myExtras->getHaarkleur()) percentage += verhoging;
	if (potentieel->getOogKleur() == myExtras->getOogKleur()) percentage += verhoging;
	if (potentieel->getLengte() >= myExtras->getLengte() - 5 && potentieel->getLengte() <= myExtras->getLengte() + 5) percentage += verhoging;
	if (potentieel->getMuziekstijl() == myExtras->getMuziekstijl()) percentage += verhoging;


	return percentage;
}

int Extras::getID()
{
	return extrasID;
}

string Extras::getHoroscoop()
{
	stringstream ss;
	switch (horoscoop) {
	case PRIVE_HO: ss << "--Prive--";
	case WAT: ss << "WAT"; break;
	case VIS: ss << "VIS"; break;
	case RAM: ss << "RAM"; break;
	case STI: ss << "STI"; break;
	case TWE: ss << "TWE"; break;
	case KRE: ss << "KRE"; break;
	case LEE: ss << "LEE"; break;
	case MAA: ss << "MAA"; break;
	case WEE: ss << "WEE"; break;
	case SCH: ss << "SCH"; break;
	case BOO: ss << "BOO"; break;
	case STE: ss << "STE"; break;
	}

	return ss.str();
}

string Extras::getHaarkleur()
{
	stringstream ss;
	switch (haar)
	{
	case PRIVE_HK: ss << "NULL"; break;
	case ZWART_HAAR: ss << "ZWART"; break;
	case BLOND_HAAR: ss << "BLOND"; break;
	case BRUIN_HAAR: ss << "BRUIN"; break;
	case GRIJS_HAAR: ss << "GRIJS"; break;
	default:
		break;
	}

	return ss.str();
}

string Extras::getOogKleur()
{
	stringstream ss;

	switch (ogen)
	{
	case PRIVE_OK: ss << "NULL"; break;
	case ZWART: ss << "ZWART"; break;
	case BLAUW: ss << "BLAUW"; break;
	case GROEN: ss << "GROEN"; break;
	case BRUIN: ss << "BRUIN"; break;
	case GRIJS: ss << "GRIJS"; break;
	default:
		break;
	}

	return ss.str();
}

int Extras::getLengte()
{
	return lengte;
}

string Extras::getStatus()
{
	stringstream ss;

	switch (status)
	{
	case PRIVE_LS: ss << "NULL"; break;
	case BEZET: ss << "BEZET"; break;
	case OPEN_RELATIE: ss << "OPEN_RELATIE"; break;
	case SINGLE: ss << "SINGLE"; break;
	case BLIJKBAAR_VERVLOEKT: ss << "BLIJKBAAR_VERVLOEKT"; break;
	default:
		break;
	}
	return ss.str();
}

string Extras::getMuziekstijl()
{
	return muziekstijl;
}

string Extras::horoscoop_voluit()
{
	stringstream ss;
	switch (horoscoop) {
	case PRIVE_HO: ss << "-Privé-"; break;
	case WAT: ss << "Waterman";	break;
	case VIS: ss << "Vis"; break;
	case RAM: ss << "Ram"; break;
	case STI: ss << "Stier"; break;
	case TWE: ss << "Tweeling"; break;
	case KRE: ss << "Kreeft"; break;
	case LEE: ss << "Leeuw"; break;
	case MAA: ss << "Maagd"; break;
	case WEE: ss << "Weegschaal"; break;
	case SCH: ss << "Schorpioen"; break;
	case BOO: ss << "Boogschutter"; break;
	case STE: ss << "Steenbok"; break;
	}

	return ss.str();
}

string Extras::haarkleur_voluit()
{
	stringstream ss;
	switch (haar)
	{
	case PRIVE_HK: ss << "-Privé-"; break;
	case ZWART_HAAR: ss << "zwart"; break;
	case BLOND_HAAR: ss << "blond"; break;
	case BRUIN_HAAR: ss << "bruin"; break;
	case GRIJS_HAAR: ss << "grijs"; break;
	default:
		break;
	}

	return ss.str();
}

string Extras::oogkleur_voluit()
{
	stringstream ss;

	switch (ogen)
	{
	case PRIVE_OK: ss << "-Privé-"; break;
	case ZWART: ss << "zwart"; break;
	case BLAUW: ss << "blauw"; break;
	case GROEN: ss << "groen"; break;
	case BRUIN: ss << "bruin"; break;
	case GRIJS: ss << "grijs"; break;
	default:
		break;
	}

	return ss.str();
}

string Extras::status_voluit()
{
	stringstream ss;

	switch (status)
	{
	case PRIVE_LS: ss << "-Privé-"; break;
	case BEZET: ss << "bezet"; break;
	case OPEN_RELATIE: ss << "in een open relatie"; break;
	case SINGLE: ss << "single"; break;
	case BLIJKBAAR_VERVLOEKT: ss << "blijkbaar vervloekt"; break;
	default:
		break;
	}
	return ss.str();
}

void Extras::setID(int ID)
{
	this->extrasID = ID;
}

void Extras::setHoroscoop(Horoscoop sterrenbeeld)
{
	this->horoscoop = sterrenbeeld;
}

void Extras::setHaarkleur(Haarkleur kleur)
{
	this->haar = kleur;
}

void Extras::setOogkleur(Oogkleur kleur)
{
	this->ogen = kleur;
}

void Extras::setLengte(int lengte_in_cm)
{
	this->lengte = lengte_in_cm;
}

void Extras::setStatus(LoveStatus liefdesstatus)
{
	this->status = liefdesstatus;
}

void Extras::setMuziekstijl(string muziekGenre)
{
	this->muziekstijl = muziekGenre;
}

