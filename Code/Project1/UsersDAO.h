#pragma once
#include "stdafx.h"

string random_string();

class UsersDAO
{
private:
	static Connection* con;
	static string getPassword(string username);														//TEST OK
public:
	UsersDAO();
	~UsersDAO();

	static bool wink(string zender, string ontvanger);												//TEST OK
	static bool getIsActief(string username);														//TEST OK
	static bool check_beschikbaarheid(string username);												//TEST OK
	static string generate_salt(string);															//TEST OK
	static string getSalt(string username);															//TEST OK
	static int get_aantal_online();																	//TEST OK
	static PremiumStatus premium_overtijd(Users*);													//TEST OK

	static string getUsername(int profileID);														//TEST OK
	static Users * getUser(string username);														//TEST OK
	//static bool logIN(string username, string password);	//UPDATE MET ENCRYPTIE										//NOG TESTEN!
	//static bool logOUT(string username);					//UPDATE MET ENCRYPTIE										//NOG TESTEN!
	static Users* addUser(Users* user);												//TEST OK
	static bool update(Users* user);																//TEST OK
	//in het geval dat de username moet gewijzigd worden.
	static bool update(Users* user /*object met nieuwe naam*/, string huidige_username);			//TEST OK
	static bool removeUser(string username);														//TEST OK
	static vector<string> zoek_geslacht(Geslacht voorkeur);											//TEST OK
};

