#include "Interests.h"


Interests::Interests(int ID, bool sport, bool natuur, bool kunst, bool games, bool technologie, bool wetenschap, bool cultuur, bool reizen, bool filosofie, bool samenzweringstheoriën, bool socialeMedia, bool muziek, bool fotografie, bool dieren)
{

	this->interestsID = ID;
	this->sport = sport;
	this->natuur = natuur;
	this->kunst = kunst;
	this->games = games;
	this->technologie = technologie;
	this->wetenschap = wetenschap;
	this->cultuur = cultuur;
	this->reizen = reizen;
	this->filosofie = filosofie;
	this->samenzweringstheoriën = samenzweringstheoriën;
	this->socialeMedia = socialeMedia;
	this->muziek = muziek;
	this->fotografie = fotografie;
	this->dieren = dieren;
}

Interests::~Interests()
{
}

double Interests::compare(Interests * potentieel, Interests *myInterests)
{
	double percentage = 0;
	double verhoging = 100 / 14.009; // +.009 omdat perfectie niet bestaat als het over relaties gaat

	if (potentieel->getSport() == myInterests->getSport()) percentage += verhoging;
	if (potentieel->getNatuur() == myInterests->getNatuur()) percentage += verhoging;
	if (potentieel->getKunst() == myInterests->getKunst()) percentage += verhoging;
	if (potentieel->getGames() == myInterests->getGames()) percentage += verhoging;
	if (potentieel->getTechnologie() == myInterests->getTechnologie()) percentage += verhoging;
	if (potentieel->getWetenschap() == myInterests->getWetenschap()) percentage += verhoging;
	if (potentieel->getCultuur() == myInterests->getCultuur()) percentage += verhoging;
	if (potentieel->getReizen() == myInterests->getReizen()) percentage += verhoging;
	if (potentieel->getFilosofie() == myInterests->getFilosofie()) percentage += verhoging;
	if (potentieel->getSamenzweringstheoriën() == myInterests->getSamenzweringstheoriën()) percentage += verhoging;
	if (potentieel->getSocialeMedia() == myInterests->getSocialeMedia()) percentage += verhoging;
	if (potentieel->getMuziek() == myInterests->getMuziek()) percentage += verhoging;
	if (potentieel->getFotografie() == myInterests->getFotografie()) percentage += verhoging;
	if (potentieel->getDieren() == myInterests->getDieren()) percentage += verhoging;

	return percentage;
}


int Interests::getID()
{
	return interestsID;
}

bool Interests::getSport()
{
	return sport;
}

bool Interests::getNatuur()
{
	return natuur;
}

bool Interests::getKunst()
{
	return kunst;
}

bool Interests::getGames()
{
	return games;
}

bool Interests::getTechnologie()
{
	return technologie;
}

bool Interests::getWetenschap()
{
	return wetenschap;
}

bool Interests::getCultuur()
{
	return cultuur;
}

bool Interests::getReizen()
{
	return reizen;
}

bool Interests::getFilosofie()
{
	return filosofie;
}

bool Interests::getSamenzweringstheoriën()
{
	return samenzweringstheoriën;
}

bool Interests::getSocialeMedia()
{
	return socialeMedia;
}

bool Interests::getMuziek()
{
	return muziek;
}

bool Interests::getFotografie()
{
	return fotografie;
}

bool Interests::getDieren()
{
	return dieren;
}




void Interests::setID(int ID)
{
	this->interestsID = ID;
}

void Interests::setSport(bool sport)
{
	this->sport = sport;
}

void Interests::setNatuur(bool natuur)
{
	this->natuur = natuur;
}

void Interests::setKunst(bool kunst)
{
	this->kunst = kunst;
}

void Interests::setGames(bool games)
{
	this->games = games;
}

void Interests::setTechnologie(bool technologie)
{
	this->technologie = technologie;
}

void Interests::setWetenschap(bool wetenschap)
{
	this->wetenschap = wetenschap;
}

void Interests::setCultuur(bool cultuur)
{
	this->cultuur = cultuur;
}

void Interests::setReizen(bool reizen)
{
	this->reizen = reizen;
}

void Interests::setFilosofie(bool filosofie)
{
	this->filosofie = filosofie;
}

void Interests::setSamenzweringstheoriën(bool Samenzweringstheoriën)
{
	this->samenzweringstheoriën = samenzweringstheoriën;
}

void Interests::setSocialeMedia(bool socialeMedia)
{
	this->socialeMedia = socialeMedia;
}

void Interests::setMuziek(bool muziek)
{
	this->muziek = muziek;
}

void Interests::setFotografie(bool fotografie)
{
	this->fotografie = fotografie;
}

void Interests::setDieren(bool dieren)
{
	this->dieren = dieren;
}

string Interests::toString()
{
	stringstream ss;
	ss << "Sport: "; if (sport) ss << "\t\t\tJa." << endl; else ss << "\t\t\tNee." << endl;
	ss << "Natuur: "; if (natuur) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Kunst: "; if (kunst) ss << "\t\t\tJa." << endl; else ss << "\t\t\tNee." << endl;
	ss << "Games: "; if (games) ss << "\t\t\tJa." << endl; else ss << "\t\t\tNee." << endl;
	ss << "Technologie: "; if (technologie) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Wetenschap: "; if (wetenschap) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Cultuur: "; if (cultuur) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Reizen: "; if (reizen) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Filosofie: "; if (filosofie) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Samenzweringstheorien: "; if (samenzweringstheoriën) ss << "\tJa." << endl; else ss << "\tNee." << endl;
	ss << "Sociale Media: "; if (socialeMedia) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Muziek: "; if (muziek) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Fotografie: "; if (fotografie) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;
	ss << "Dieren: "; if (dieren) ss << "\t\tJa." << endl; else ss << "\t\tNee." << endl;


	return ss.str();
}
