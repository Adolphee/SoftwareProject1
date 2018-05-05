#pragma once
#include "stdafx.h"

class HobbiesDAO
{
private:
	static Connection* con;
public:
	HobbiesDAO();
	~HobbiesDAO();

	static int getID(string naam);															//TEST OK
	static Hobbies* getHobby(int ID);														//TEST OK
																							//Alle hobbies van een bepaald persoon uit DB halen										
	static vector<string> getAll(int profileID);											//TEST OK
	static bool removeUserHobby(int profileID, int hobbiesID);
	static Hobbies* saveHobby(Hobbies* hobby);												//TEST OK
	static bool exists(string);																//TEST OK
};

