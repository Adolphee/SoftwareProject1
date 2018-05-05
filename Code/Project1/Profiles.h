#pragma once
#include "stdafx.h"

enum Geslacht { MAN = 1, VROUW, _TRANS_M, _TRANS_F, _UNKNOWN };
enum Sexualiteit { HOMO = 1, LESBISCH, BI, TRANS_M, TRANS_F, UNKNOWN };
int rdn(string);
const string currentDate();

class Profiles
{	
private:
	int profileID;
	string username;
	string naam;
	string voornaam;
	string geboorteDatum = "";
	int interestID;
	int extrasID;
	int winksReceived;
	int winksToGive;
	Geslacht geslacht = _UNKNOWN;
	Geslacht zoekt = _UNKNOWN;
	string beschrijving = "";
	 
public:
	Profiles(int ID, string username, string naam, string voornaam, string geboortedatum);
	~Profiles();

	int leeftijd();
	int getID();
	string getBeschrijving();
	string getUsername();
	string getNaam();
	string getVoornaam();
	string getGeboorteDatum();
	int getInterestID();
	int getExtrasID();
	int getWinksReceived();
	int getWinksToGive();
	Geslacht getGeslacht();
	Geslacht getZoekt();

	string geslacht_voluit();
	string zoekt_voluit();

	void setBeschrijving(string);
	void setID(int);
	void setUsername(string);
	void setNaam(string);
	void setVoornaam(string);
	void setGeboorteDatum(string);
	void setInterestID(int);
	void setExtrasID(int);
	void setWinksReceived(int);
	void setWinksToGive(int);
	void setGeslacht(Geslacht);
	void setZoekt(Geslacht);

	//static int getLeeftijd();
	/*Profiles* vervolledig_Profile(Profiles*)*/;


};

