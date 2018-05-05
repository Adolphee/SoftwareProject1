#pragma once
#include "UsersDAO.h"
#include "WishlistDAO.h"
#include "ProfilesDAO.h"
#include "ExtrasDAO.h"
#include "InterestsDAO.h"
#include "HobbiesDAO.h"
#include "MessagesDAO.h"
class MENU
{
private:
	
public:
	static Status showMenu(Users*, Settings*, Status*); //Settings om meteen te hoppen naar de settings zonder langs de hoofdmenu te gaan.
	static vector<string> showMatches(Users*, int*, Status*);
	static bool viewProfile(Users* activeuser, vector<string> matches, int* keuze, Settings* settings, Status*); //ALs de active user wil upgraden is *settings de directe link om te springen van deze functie via da main naar de instellingen
	static Status getMyProfile(Users*, Settings* settings); //Uw eigen profiel kan je alleen maar aanpassen
	static bool Msg_Profile(Users* user, string username, Settings *settings, Status* AppState );
	static vector<string> ShowWishlist(Users* user, Settings* settings, Status* AppState);
};
