//#include "UsersDAO.h"
//#include "WishlistDAO.h"
//#include "ProfilesDAO.h"
//#include "ExtrasDAO.h"
//
//const string currentDateTime();
//

#include "MENU.h"
#include "LOGIN.h"
#include "INBOX.h"

int main() {
	srand(time(0));
	//De volgende 4 lijnen heb ik geGoogle'd. Ze dienen voor het consolevenster formaat aan te passen.
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 1000, TRUE); // 800 width, 100 height
	//bool login = true;
	int* keuze; int k = 2; keuze = &k; //Keuze makkelijk overdragen tussen functies
	vector<string> match_names;			// Namen van Matches met een percentage van 30+
	Settings s = OVERALL;				// Deze initialiseer ik omdat ik een error krijg als ik de lijn hieronder een pointer declareer die ik later wil initialiseren
	Settings *settings = &s;			//Als iemand een bericht wil sturen, en eindelijk de stap wil maken naar Premium. Hoeft hij bijv. niet meer eerst lang de hoofdmenu
										//Settings zegt mij waar precies in de instellingen ik precies nartoe moet springen.
	Status st = LOGIN;					//Er was een status nodig om in te beginnen. Ook hier een pointer zodat de verschillende functies zelf kunnen aangeven in welke schermen de app zich bevindt.
										//Anders is het niet echt haalbaar om dat altijd in de main te controleren vooralleer ik naar de volgende pagina ga.
	Status *AppState = &st;				//De pointer-initialisatie van de Status
	bool *profielUitInbox; bool b = false; profielUitInbox = &b; //Geeft aan of je vanuit je inbox naar een profiel kijkt of niet.(iemand waar je berichten mee hebt uitgewisseld, en je wil nog eens diens info zien
	int* inboxOptie; int g = 0; inboxOptie = &g;
	vector<string> wishlist;
	Users* active_user = nullptr; /*= LOGIN::startScherm(settings, AppState);*/
	if (*AppState == LOGIN && active_user != nullptr) *AppState = MENU; else *AppState = LOGIN;
	while (true) {
		system("cls");
		//if (j > 0) cin.clear(), cin.ignore(1000, '\n');
		switch (*AppState)
		{
		case LOGIN:
		active_user = LOGIN::startScherm(settings, AppState);
		/*if (active_user != nullptr) { current_loggedIN_Username = active_user->getUsername(); *AppState = MENU; }
		else { *AppState = LOGIN; } break;*/
		case MENU:
			*AppState = MENU::showMenu(active_user, settings, AppState); break;
		case MATCHES:
		match_names = MENU::showMatches(active_user, keuze, AppState);
		if (!match_names.empty()) {
			if (*keuze > 0) {
				gekozenGebruiker = match_names[*keuze - 1];
				*AppState = PROFIEL;
			}
			else *AppState = Status::MENU;
		}
		else *AppState = Status::MENU; break; 
		case myPROFIEL:
			*AppState = MENU::getMyProfile(active_user, settings); break;
		case PROFIEL:
		{MENU::viewProfile(active_user, match_names, keuze, settings, AppState);
		*AppState = MATCHES; break; }
		case BERICHTEN:
			*AppState = INBOX::showInbox(active_user, settings, AppState, inboxOptie);
			break;
		case INSTELLINGEN: *settings = OVERALL;	cout << "Hier komen de instellingen." << endl; break;
		case WISHLIST:
			wishlist = MENU::ShowWishlist(active_user, settings, AppState);
			break;
		default:
			break;
		}
		
	}
	/*Users* user = UsersDAO::getUser("Adolphe");
	MENU::viewProfile(user, MENU::showMatches(user, keuze), keuze);*/
	system("pause");
	return 0;
}

