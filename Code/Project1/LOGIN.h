#pragma once
#include "UsersDAO.h"
#include "WishlistDAO.h"
#include "ProfilesDAO.h"
#include "ExtrasDAO.h"

class LOGIN
{
private:
	static string getPass(const char * prompt, bool show_asterisk);
	static string getUsername();
	static bool authenticate(string, string);
	static Users* registratie(Status*);
	static string registreer_Username();
	static string registreer_Wachtwoord(string username);
	static string registreer_Security();
	static string registreer_Antwoord(string security);
	static bool reset_passwoord(Users * user, Status*);
	static bool recovery_Question(Users * user, Status*);	
public:
	//Settings zijn een directe connectie van start naar specifieke instellingen, zo hoef je niet per sé terug naar de hoofdMenu om te updragen
	static Users* startScherm(Settings*, Status*);

	
};

