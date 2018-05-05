#pragma once
#include "stdafx.h"

class Interests
{
private:
	int interestsID;
	bool sport, natuur, kunst, games, technologie, wetenschap, cultuur, reizen, filosofie, samenzweringstheori�n, socialeMedia, muziek, fotografie, dieren;
public:
	Interests(int ID, bool sport, bool natuur, bool kunst, bool games, bool technologie, bool wetenschap, bool cultuur, bool reizen, bool filosofie, bool samenzweringstheori�n, bool socialeMedia, bool muziek, bool fotografie, bool dieren);
	~Interests();

	//Deze methode is deel van mijn MatchMaking algoritme
	static double compare(Interests*, Interests *);

	int getID();
	bool getSport();
	bool getNatuur();
	bool getKunst();
	bool getGames();
	bool getTechnologie();
	bool getWetenschap();
	bool getCultuur();
	bool getReizen();
	bool getFilosofie();
	bool getSamenzweringstheori�n();
	bool getSocialeMedia();
	bool getMuziek();
	bool getFotografie();
	bool getDieren();

	void setID(int);
	void setSport(bool);
	void setNatuur(bool);
	void setKunst(bool);
	void setGames(bool);
	void setTechnologie(bool);
	void setWetenschap(bool);
	void setCultuur(bool);
	void setReizen(bool);
	void setFilosofie(bool);
	void setSamenzweringstheori�n(bool);
	void setSocialeMedia(bool);
	void setMuziek(bool);
	void setFotografie(bool);
	void setDieren(bool);

	string toString();
};

