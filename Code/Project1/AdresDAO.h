#pragma once
#include "stdafx.h"
#include "Adres.h"

//#include <iostream>
//using namespace std;

class AdresDAO
{
private:
	static Connection* con;	
public:
	AdresDAO();
	~AdresDAO();

	static bool removeAdres(int profileID, int adresID);//Adres X van Persoon Y verwijderen				//TEST OK
	static vector<Adres*> getAll(int profileID); // ALLE Adressen van persoon X ophalen					//TEST OK
	static Adres* saveAdres(Adres*);// adresID = -1 voor toevoegen nieuw adres aan DB					//TEST OK
	static Adres* getAdres(int adresID);
};