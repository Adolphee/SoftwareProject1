#include "MENU.h"
#include <ctype.h>
using namespace std;

Status MENU::showMenu(Users* user, Settings* settings, Status* AppState)
{
	system("cls");
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "Welkom, " << ProfilesDAO::getProfile(user->getUsername())->getVoornaam() << ". Wij wensen u veel plezier toe!." << endl;
	cout << "1. Matches" << endl;
	cout << "2. Wishlist" << endl;
	cout << "3. Eigen profiel weergeven" << endl;
	cout << "4. Inbox openen" << endl;
	cout << "6. Upgrade naar Premium" << endl;
	cout << "7. Log Uit" << endl;
	cout << endl << "Uw keuze:\t";
	int optie; cin >> optie;
	while (optie < 1 || optie > 7) {
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl;
		cout << "Ongeldige invoer. Probeer het nog eens." << endl << endl;
		cout << "1. Matches" << endl;
		cout << "2. Wishlist" << endl;
		cout << "3. Eigen profiel weergeven" << endl;
		cout << "4. Inbox openen" << endl;
		cout << "5. Instellingen" << endl;
		cout << "6. Upgrade naar Premium" << endl;
		cout << "7. Log Uit" << endl;
		cout << endl << "Uw keuze:\t";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> optie;
	}
	char exit;
	switch (optie)
	{
	case 1:*AppState = Status::MATCHES; break;
	case 2:*AppState = Status::WISHLIST; break;
	case 3:*AppState = Status::myPROFIEL; break; 
	case 4:*AppState = Status::BERICHTEN; break;//return *AppState;
	case 5:*AppState = Status::INSTELLINGEN; *settings = OVERALL; break;
	case 6:*AppState = Status::INSTELLINGEN; *settings = UPGRADE; break;
	case 7:
		system("cls");
		cin.clear(); cin.ignore();
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "Weet je zeker dat je wil uitloggen? (J/N)" << endl;
		cout << "Uw keuze:\t";  exit = getchar();
		while (toupper(exit) != 'J' && toupper(exit) != 'N') {
			system("cls");
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============>       LOG UIT?       <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			cout << "Foute invoer." << endl;
			cout << "Druk 'J' om het om uit te loggen of 'N' om te annuleren." << endl;
			cout << "Uw keuze:\t"; exit = getchar();
		}
		if (toupper(exit) == 'J') {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "                  _/_/_/    _/      _/  _/_/_/_/  _/              " << endl;
			cout << "                 _/    _/    _/  _/    _/        _/    		   " << endl;
			cout << "                _/_/_/        _/      _/_/_/    _/     		   " << endl;
			cout << "               _/    _/      _/      _/                		   " << endl;
			cout << "              _/_/_/        _/      _/_/_/_/  _/       		   " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============> We zullen je missen. <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			Sleep(3000);
			cin.clear(); cin.ignore(1000, '\n');
			user->setOnline(false);
			if (UsersDAO::update(user))*AppState = Status::LOGIN;
		}
		else *AppState = Status::MENU; break;
	default:
		break;
	}
	return *AppState;
}

vector<string> MENU::showMatches(Users* user, int* keuze, Status* AppState)
{
	Profiles* profile = ProfilesDAO::getProfile(user->getUsername());

	Extras* extras = ExtrasDAO::getExtras(profile->getID());
	Interests* interests = InterestsDAO::getInterests(profile->getInterestID());
	Profiles* kandidaat;
	vector<string> match_names; vector<string> getFemales =  UsersDAO::zoek_geslacht(profile->getZoekt());
	
	vector<double> match_gravity;
	for (int i = 0; i < getFemales.size(); i++) {
		kandidaat = ProfilesDAO::getProfile(getFemales[i]);
		match_gravity.push_back((Extras::compare(ExtrasDAO::getExtras(kandidaat->getID()), extras)*0.15 +
				Interests::compare(interests, InterestsDAO::getInterests(kandidaat->getInterestID()))*0.85));
		
		delete kandidaat;
		kandidaat = nullptr;
	}
	system("cls");
	//TEXT-Art: NetworkScience.de	
	cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "________________/      _/              _/                _/       " << endl;
    cout << "_______________/_/  _/_/   __/_/_/  _/_/_/_/    _/_/_/  _/_/_/    " << endl;
    cout << "______________/  _/  _/ __/    _/    _/      _/        _/    _/   " << endl;
    cout << "_____________/      _/ __/    _/    _/      _/        _/    _/    " << endl;
	cout << "____________/      _/   __/_/_/      _/_/    _/_/_/  _/    _/     " << endl;
	cout << "                                 by Adolphe M.                    " << endl;
    cout << "________________/      _/            _/                           " << endl; 
    cout << "_______________/_/  _/_/   __/_/_/  _/  _/      _/_/    _/  _/_/  " << endl; 
    cout << "______________/  _/  _/ __/    _/  _/_/      _/_/_/_/  _/_/       " << endl; 
    cout << "_____________/      _/ __/    _/  _/  _/    _/        _/          " << endl; 
    cout << "____________/      _/   __/_/_/  _/    _/    _/_/_/  _/           " << endl;
	cout << "____________________Artwork by Network-Science.de_________________" << endl;
	cout << "=================================================================="<< endl;
	cout << "==================================================================" << endl << endl;
	int j = 0;
	for (int i = 0; i < getFemales.size(); i++) {
		if (match_gravity[i] > 30) {
			match_names.push_back(getFemales[i]);
				cout << j + 1 << ". " << getFemales[i] << "\t\t\t" << floor(match_gravity[i] * 100 + 0.5) / 100 << " %" << endl;
				j++;
		}
	}
	cout << "Kies welke profiel je wil bekijken:\t";
	cin >> *keuze;
	while (!(*keuze >= 0 && *keuze <= match_names.size())) {
		cin.clear(); cin.ignore(1000, '\n');
		if (*keuze == 0) { *AppState = Status::MENU; return match_names; }		
		system("cls");
		cout << "________________/      _/              _/                _/       " << endl;
		cout << "_______________/_/  _/_/   __/_/_/  _/_/_/_/    _/_/_/  _/_/_/    " << endl;
		cout << "______________/  _/  _/ __/    _/    _/      _/        _/    _/   " << endl;
		cout << "_____________/      _/ __/    _/    _/      _/        _/    _/    " << endl;
		cout << "____________/      _/   __/_/_/      _/_/    _/_/_/  _/    _/     " << endl;
		cout << "                                 by Adolphe M.                    " << endl;
		cout << "________________/      _/            _/                           " << endl;
		cout << "_______________/_/  _/_/   __/_/_/  _/  _/      _/_/    _/  _/_/  " << endl;
		cout << "______________/  _/  _/ __/    _/  _/_/      _/_/_/_/  _/_/       " << endl;
		cout << "_____________/      _/ __/    _/  _/  _/    _/        _/          " << endl;
		cout << "____________/      _/   __/_/_/  _/    _/    _/_/_/  _/           " << endl;
		cout << "____________________Artwork by Network-Science.de_________________" << endl;
		cout << "==================================================================" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "            Je hebt ons van foute invoer voorzien." << endl << endl;
		for (int i = 0; i < match_names.size(); i++) {
			cout << i + 1 << ". " << match_names[i] << "\t\t\t" << floor(match_gravity[i] * 100 + 0.5) / 100 << " %" << endl;
		}
		cout << endl << "Kies welke profiel je wil bekijken." << endl;
		cout << " Druk 0 om terug te keren naar het hoofdmenu." << endl;
		cout << "Uw keuze:\t"; cin >> *keuze;
	}
	if (*keuze != 0) { *AppState = PROFIEL; return match_names; }
	else { *AppState = Status::MENU; return match_names; }
}

bool MENU::viewProfile(Users* activeUser, vector<string> matches, int* keuze, Settings* settings, Status* AppState)
{
	//vector<Profiles*> profiles;
	if (*keuze <= 0) *keuze = 1;
	gekozenGebruiker = matches[*keuze - 1];
	Profiles* p;
	Users* user;
	Extras*e;
	vector<string> h;
	int count;
	bool returnToProfile = true;
	while (returnToProfile) {
		system("cls");
		p = ProfilesDAO::getProfile(gekozenGebruiker); //Profiel van gekozen persoon ophalen
		user = UsersDAO::getUser(gekozenGebruiker);	//Usergegevens van gekozen persoon ophalen
		e = ExtrasDAO::getExtras(p->getID());			//Extras van gekozen persoon ophalen
		h = HobbiesDAO::getAll(p->getID());		//Hobbies van gekozen persoon ophalen
		count = WishlistDAO::wishlist_count(user->getUsername()); //Wishlist count van de gekozen persoon ophalen
		//TEXT-Art: http://www.network-science.de/ascii/
		cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
		cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
		cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
		cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
		cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
		cout << "==================================================================" << endl;
		if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
		else cout << "||<[*_*[ PREMIUM ]*_*]> " << user->getUsername() << " <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
		cout << "||================================================================" << endl << endl;

		cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
		cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
		cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
		cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
		//[PREMIUM CONTENT]
		if (activeUser->getPremium()) {
			cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
			cout << "||Aantal keren op wishlists_______________________________________" << count << endl; //op hoeveel wishlists staat deze persoon
			cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
			cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
			cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
			cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
			cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl << endl;
			for (int i = 0; i < h.size(); i++) {
				if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
				else       cout << "||                                                                " << h[i] << endl;
			}
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl;
			cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
		}
		cout << "||" << endl << "||" << endl;
		cout << "||================================================================" << endl;
		cout << "||Wat wil je doen?________________________________________________" << endl;
		cout << "||                   _....,_         _,...._                      0. Terugkeren." << endl;
		cout << "||               _.-`       '.     .'       `-._                  1. Bericht versturen." << endl;
		cout << "||                _,                         ,_                   2. Toevoegen aan wishlist." << endl;
		cout << "||                 '-. ___ .-`     `-. ___ .-'                    3. Wink (knipoogje) sturen!" << endl;
		cout << "||                                                                4. Volgende Match" << endl;
		if (*keuze > 1) cout << "||                                                                5. Vorige Match" << endl;
		cout << "||================================================================Uw Keuze:\t";
		
		int optie; cin >> optie;
		//Veilige invoer
		while ((optie > 5 || optie < 0 ) || (optie == 5 && *keuze < 1)) {
			system("cls");
			cin.clear(); cin.ignore(1000, '\n');
			//TEXT-Art: http://www.network-science.de/ascii/
			cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
			cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
			cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
			cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
			cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
			cout << "==================================================================" << endl;
			if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
			else cout << "||<[*_*[ PREMIUM ]*_*]> " << user->getUsername() << " <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
			cout << "||================================================================" << endl << endl;

			cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
			cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
			cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
			cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
			if (activeUser->getPremium()) {
				cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
				cout << "||Aantal keren op wishlists_______________________________________" << count << endl;
				cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
				cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
				cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
				cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
				cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
				cout << "||================================================================" << endl;
				cout << "||================================================================" << endl << endl;
				for (int i = 0; i < h.size(); i++) {
					if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
					else       cout << "||                                                                " << h[i] << endl;
				}
				cout << "||================================================================" << endl;
				cout << "||================================================================" << endl;
				cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
			}	cout << "||" << endl << "||" << endl;
			cout << "||================================================================" << endl;
			cout << "||Wat wil je doen?________________________________________________" << endl;
			cout << "||                   _....,_         _,...._                      0. Terugkeren." << endl;
			cout << "||               _.-` _,..,_'.     .'_,..,_ `-._                  1. Bericht versturen." << endl;
			cout << "||                _,-`/ o \\ '.     .' / o \\`-,_                 2. Toevoegen aan wishlist." << endl;
			cout << "||            jgs  '-.\\___/.-`     `-.\\___/.-'                  3. Wink (knipoogje) sturen!" << endl;
			cout << "||                 Maak a.u.b. een geldige keuze.                 4. Volgende Match" << endl;
			if (*keuze > 1) cout << "||                                                                 5. Vorige Match" << endl;
			cout << "||================================================================Uw Keuze:\t";cin >> optie;
		}
		bool verstuurd = false; //bericht verstuurd?
		string bericht; //Daadwerkelijk bericht
		char emptyMsg; //Voor het bevestigen dat je een leeg bericht wil verzenden
		char prem; //Als je een prem-functie kiest en je bent geen premium. Is dit je keuze of je al dan niet wil upgraden.
		switch (optie) {
		case 1://bericht
			if (activeUser->getPremium()) {
				while (!verstuurd) {
					//system("cls");
					//cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					//cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					//cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					//cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					//cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					//cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					//cout << "==================================================================" << endl;
					//cout << "+oo((X))=============>        Bericht       <=============((X))oo+" << endl;
					//cout << "==================================================================" << endl << endl;
					cout << "Geen uw bericht in:\t"; cin.clear(); cin.ignore(1000, '\n'); getline(cin, bericht, '\n');
					if (bericht == "") {
						cout << "Dit bericht is leeg. Doorgaan? (j/n)\t"; emptyMsg = getchar();
						//Veilige invoer
						while (toupper(emptyMsg) != 'J' && toupper(emptyMsg) != 'N') {
							system("cls");
							cin.clear(); cin.ignore(1000, '\n');
							cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
							cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
							cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
							cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
							cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
							cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
							cout << "==================================================================" << endl;
							cout << "+oo((X))=============>        Bericht       <=============((X))oo+" << endl;
							cout << "==================================================================" << endl << endl;
							cout << "Foute invoer." << endl;
							cout << "Druk 'J' om het leeg bericht naar " << gekozenGebruiker << " te versturen of 'N' om terug te gaan." << endl;
							cout << "Uw keuze:\t"; emptyMsg = getchar();
						}
						if (toupper(emptyMsg) == 'N') break;// Dit brengt hem terug naar de switch, daar wordt hij meteen terug naar de conversatie gestuurd.						
					}
					else {
						Messages msg(-1, activeUser->getUsername(), gekozenGebruiker, bericht); //Bericht object maken
						MessagesDAO::verzend(&msg); cout << "Bericht verstuurd." << endl; //Bericht verzenden naar DB
						verstuurd = true;
						system("pause"); break;
						//cout << "We gaan terug naar het vorig scherm." << endl; Sleep(2500); break;
					}
				}
			}
			else {
				system("cls");
				cin.clear(); cin.ignore(1000,'\n');
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>    PREMIUM CONTENT   <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "U moet een Premium gebruiker zijn om berichten te sturen." << endl;
				cout << "Wenst u te upgraden naar Premium?(J/N)";
				
				cout << "Antwoord:\t"; prem = getchar();
				//Veilige invoer
				while (toupper(prem) != 'J' && toupper(prem) != 'N') {
					system("cls");
					cin.clear(); cin.ignore(1000, '\n');
					cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "================================================================" << endl;
					cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
					cout << "================================================================" << endl << endl;
					cout << "Foute invoer." << endl;
					cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
					cout << "Uw keuze:\t"; prem = getchar();
				}
				if (toupper(prem) == 'N') break;
				else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile = false; break;
			} //verboden voor niet Premium
			break;
		case 3://wink
			if (activeUser->getPremium()) {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>          WINKS       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				if (ProfilesDAO::getProfile(activeUser->getUsername())->getWinksToGive() > 0) {
					if (UsersDAO::wink(activeUser->getUsername(), gekozenGebruiker)) {
						cout << "Wink verzonden.\nWe gaan terug naar het vorig scherm." << endl;
						system("pause");
					}

				}
				else {
					system("cls");
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>     NO MORE WINKS    <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					cout << "Je hebt geen WINKS meer om te versturen." << endl;
					cout << "Aan het begin van de volgende Premium-maand krijg je +15 WINKS cadeau!!!." << endl;
					system("pause");
				}
			}
			else {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/         " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/      " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/     " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/      " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/       " << endl;
				cout << "====================================================================" << endl;
				cout << "+oo((X))=============>     PREMIUM CONTENT    <=============((X))oo+" << endl;
				cout << "====================================================================" << endl << endl;
				cout << "U moet een Premium gebruiker zijn om WINKS te sturen." << endl;
				cout << "Wenst u te upgraden naar Premium?(J/N)" << endl;
				cin.clear(); cin.ignore(1000, '\n');
				cout << "Antwoord:\t"; prem = getchar();
				//Veilige invoer
				while (toupper(prem) != 'J' && toupper(prem) != 'N') {
					system("cls");
					cin.clear(); cin.ignore(1000, '\n');
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "================================================================" << endl;
					cout << "+oo((X))=============>    PREMIUM CONTENT   <=============((X))oo+" << endl;
					cout << "================================================================" << endl << endl;
					cout << "Foute invoer." << endl;
					cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
					cout << "Uw keuze:\t"; prem = getchar();
				}
				if (toupper(prem) == 'N') break;
				else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile = false; break;
			}
			break;
		case 2://Toevoegen aan wishlist meer dan 5 mensen op wishlist = [PREMIUM]
			if (activeUser->getPremium()) {
				if (!(WishlistDAO::exists(activeUser->getWishlistID(), gekozenGebruiker))) {
					if (WishlistDAO::add(activeUser->getWishlistID(), gekozenGebruiker))
						cout << gekozenGebruiker << " staat nu op je wishlist." << endl;
				}
				else cout << gekozenGebruiker << " staat al op je wishlist!" << endl;
				system("pause"); break;
			}
			else {
				if (ProfilesDAO::getProfile(activeUser->getUsername())->getWinksToGive() > 0) {
					if (!(WishlistDAO::exists(activeUser->getWishlistID(), gekozenGebruiker))) {
						if (WishlistDAO::add(activeUser->getWishlistID(), gekozenGebruiker))
							cout << gekozenGebruiker << " staat nu op je wishlist." << endl;
					}
					else cout << gekozenGebruiker << " staat al op je wishlist!" << endl;
					system("pause"); break;
				}
				else {
					system("cls");
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "================================================================" << endl;
					cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
					cout << "================================================================" << endl << endl;
					cout << "U moet een Premium gebruiker zijn om meer dan 5 mensen op je wishlist te zetten." << endl;
					cout << "Wenst u te upgraden naar Premium?(J/N)";
					cout << "Antwoord:\t"; prem = getchar();
					//Veilige invoer
					while (toupper(prem) != 'J' && toupper(prem) != 'N') {
						system("cls");
						cin.clear(); cin.ignore();
						cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
						cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
						cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
						cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
						cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
						cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						cout << "Foute invoer." << endl;
						cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
						cout << "Uw keuze:\t"; prem = getchar();
					}
					if (toupper(prem) == 'N') break;
					else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile == false; break;
				}
			}
			break;
		case 4: //Volgende Match
			if (*keuze <= matches.size() - 2) *keuze = *keuze + 1; else *keuze = 1;
			gekozenGebruiker = matches[*keuze - 1];
			*AppState = PROFIEL; break;
		case 0: returnToProfile = false;
			*AppState = MATCHES; break;
		case 5://Vorige Match
			if (activeUser->getPremium()) {				
				if (gekozenGebruiker == matches[0]) *keuze = matches.size(); else *keuze = *keuze - 1;
				gekozenGebruiker = matches[*keuze - 1];
				*AppState = PROFIEL; break;
			}
			else {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "================================================================" << endl;
				cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
				cout << "================================================================" << endl << endl;
				cout << "U moet een Premium gebruiker zijn om de vorige match te kunnen  " << endl;
				cout << "terughalen." << endl;
				cout << "Wenst u te upgraden naar Premium?(J/N)";
				cin.clear(); cin.ignore(1000, '\n');
				cout << "Antwoord:\t"; prem = getchar();
				//Veilige invoer
				while (toupper(prem) != 'J' && toupper(prem) != 'N') {
					system("cls");
					cin.clear(); cin.ignore();
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					cout << "Foute invoer." << endl;
					cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
					cout << "Uw keuze:\t"; prem = getchar();
				}
				if (toupper(prem) == 'N') break;
				else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile == false; break;
			}
		}		
	}return true;
}

Status MENU::getMyProfile(Users* user, Settings* settings)
{
	gekozenGebruiker = user->getUsername();
	Profiles* p = ProfilesDAO::getProfile(gekozenGebruiker); //Profiel van gekozen persoon ophalen
	Extras*e = ExtrasDAO::getExtras(p->getID());			//Extras van gekozen persoon ophalen
	vector<string> h = HobbiesDAO::getAll(p->getID());		//Hobbies van gekozen persoon ophalen
	int count = WishlistDAO::wishlist_count(gekozenGebruiker); //Wishlist count van de gekozen persoon ophalen
	//TEXT-Art: http://www.network-science.de/ascii/
	system("cls");		
	cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
	cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
	cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
	cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
	cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
	cout << "==================================================================" << endl;
	if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
	else cout << "||<[*_*[ PREMIUM ]*_*]> " << user->getUsername() << " <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
	cout << "||================================================================" << endl << endl;

	cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
	cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
	cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
	cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
	//[PREMIUM CONTENT]
	if (user->getPremium()) {
		cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
		cout << "||Aantal keren op wishlists_______________________________________" << count << endl;
		cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
		cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
		cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
		cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
		cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
		cout << "||================================================================" << endl;
		cout << "||================================================================" << endl << endl;
		for (int i = 0; i < h.size(); i++) {
			if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
			else       cout << "||                                                                " << h[i] << endl;
		}
		cout << "||================================================================" << endl;
		cout << "||================================================================" << endl;
		cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
	}
	cout << "||" << endl << "||" << endl;
	cout << "||================================================================" << endl;
	cout << "||Wat wil je doen?________________________________________________" << endl;
	cout << "||                   _....,_         _,...._                      1. Profile basics aanpassen" << endl;
	cout << "||               _.-`       '.     .'       `-._                  2. Interesses aanpassen" << endl;
	cout << "||                _,                         ,_                   3. Extras over mezelf aanpassen" << endl;
	cout << "||                 '-. ___ .-`     `-. ___ .-'                    4. Hobbies aanpassen" << endl;
	cout << "||                                                                0. Afsluiten" << endl;
	cout << "||================================================================Uw Keuze:\t";
	//cin.clear(); cin.ignore(1000, '\n');
	int optie; cin >> optie;
	char prem;
	while (!(optie < 5 && optie >= 0)) {
		system("cls");
		cin.clear(); cin.ignore(1000, '\n');
		//TEXT-Art: http://www.network-science.de/ascii/
		cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
		cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
		cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
		cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
		cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
		cout << "==================================================================" << endl;
		if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
		else cout << "||<[*_*[ PREMIUM ]*_*]> " << user->getUsername() << " <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
		cout << "||================================================================" << endl << endl;
		cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
		cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
		cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
		cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
		//[PREMIUM CONTENT]
		if (user->getPremium()) {
			cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
			cout << "||Aantal keren op wishlists_______________________________________" << count << endl;
			cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
			cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
			cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
			cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
			cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl << endl;
			for (int i = 0; i < h.size(); i++) {
				if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
				else       cout << "||                                                                " << h[i] << endl;
			}
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl;
			cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
		}
		cout << "||" << endl << "||" << endl;
		cout << "||================================================================" << endl;
		cout << "||Wat wil je doen?________________________________________________" << endl;
		cout << "||                   _....,_         _,...._                       0. Profile basics aanpassen" << endl;
		cout << "||               _.-` _,..,_'.     .'_,..,_ `-._                   1. Interesses aanpassen" << endl;
		cout << "||                _,-`/ o \\ '.     .' / o \\`-,_                  2. Extras over mezelf aanpassen" << endl;
		cout << "||            jgs  '-.\\___/.-`     `-.\\___/.-'                   3. Hobbies aanpassen" << endl;
		cout << "||                 Maak a.u.b. een geldige keuze.                  4. Afsluiten" << endl;
		cout << "||================================================================Uw Keuze:\t";
		cin >> optie;
	}


	switch (optie) {
	case 1://Basic Profile info
		 *settings = BASICS; return INSTELLINGEN;		
		break;
	case 2://Interesses
		if (user->getPremium()) {
			 *settings = INTERESTS; return INSTELLINGEN; break;
		}
		else {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "================================================================" << endl;
			cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
			cout << "================================================================" << endl << endl;
			cout << "U moet Premium zijn om de om dergelijke aanpassingen te doen" << endl;
			cout << "terughalen." << endl;
			cout << "Wenst u te upgraden naar Premium?(J/N)";
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Antwoord:\t"; prem = getchar();
			//Veilige invoer
			while (toupper(prem) != 'J' && toupper(prem) != 'N') {
				system("cls");
				cin.clear(); cin.ignore();
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Foute invoer." << endl;
				cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
				cout << "Uw keuze:\t"; prem = getchar();
			}
		}
		if (toupper(prem) == 'N') break;
		else *settings = UPGRADE; return INSTELLINGEN; 
		break;
	case 3://Extras
		if (user->getPremium()) {
			*settings = EXTRAS; return INSTELLINGEN; break;
		}
		else {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "================================================================" << endl;
			cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
			cout << "================================================================" << endl << endl;
			cout << "U moet Premium zijn om de om dergelijke aanpassingen te doen" << endl;
			cout << "terughalen." << endl;
			cout << "Wenst u te upgraden naar Premium?(J/N)";
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Antwoord:\t"; prem = getchar();
			//Veilige invoer
			while (toupper(prem) != 'J' && toupper(prem) != 'N') {
				system("cls");
				cin.clear(); cin.ignore();
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Foute invoer." << endl;
				cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
				cout << "Uw keuze:\t"; prem = getchar();
			}
		}
		if (toupper(prem) == 'N') break;
		else *settings = UPGRADE; return INSTELLINGEN;
		break;
	case 4://Hobbies
		if (user->getPremium()) {
			*settings = HOBBIES; return INSTELLINGEN; 
		}
		else {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "================================================================" << endl;
			cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
			cout << "================================================================" << endl << endl;
			cout << "U moet Premium zijn om de om dergelijke aanpassingen te doen" << endl;
			cout << "terughalen." << endl;
			cout << "Wenst u te upgraden naar Premium?(J/N)";
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Antwoord:\t"; prem = getchar();
			//Veilige invoer
			while (toupper(prem) != 'J' && toupper(prem) != 'N') {
				system("cls");
				cin.clear(); cin.ignore();
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Foute invoer." << endl;
				cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
				cout << "Uw keuze:\t"; prem = getchar();
			}
		}
		if (toupper(prem) == 'N') break;
		else *settings = UPGRADE; return INSTELLINGEN;
		break;
	case 0://Afsluiten
		break;
	}

	return Status::MENU;
}

bool MENU::Msg_Profile(Users * activeUser, string username, Settings *settings, Status* AppState)
{
	
	gekozenGebruiker = username;
	Profiles* p;
	Users* user;
	Extras*e;
	vector<string> h;
	int count;
	bool returnToProfile = true;
	while (returnToProfile) {
		system("cls");
		p = ProfilesDAO::getProfile(gekozenGebruiker); //Profiel van gekozen persoon ophalen
		user = UsersDAO::getUser(gekozenGebruiker);	//Usergegevens van gekozen persoon ophalen
		e = ExtrasDAO::getExtras(p->getID());			//Extras van gekozen persoon ophalen
		h = HobbiesDAO::getAll(p->getID());		//Hobbies van gekozen persoon ophalen
		count = WishlistDAO::wishlist_count(user->getUsername()); //Wishlist count van de gekozen persoon ophalen
																  //TEXT-Art: http://www.network-science.de/ascii/
		cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
		cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
		cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
		cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
		cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
		cout << "==================================================================" << endl;
		if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
		else cout << "||<[*_*[ PREMIUM ]*_*]>        " << user->getUsername() << "       <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
		cout << "||================================================================" << endl << endl;

		cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
		cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
		cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
		cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
		//[PREMIUM CONTENT]
		if (activeUser->getPremium()) {
			cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
			cout << "||Aantal keren op wishlists_______________________________________" << count << endl; //op hoeveel wishlists staat deze persoon
			cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
			cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
			cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
			cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
			cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl << endl;
			for (int i = 0; i < h.size(); i++) {
				if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
				else       cout << "||                                                                " << h[i] << endl;
			}
			cout << "||================================================================" << endl;
			cout << "||================================================================" << endl;
			cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
		}
		cout << "||" << endl << "||" << endl;
		cout << "||================================================================" << endl;
		cout << "||Wat wil je doen?________________________________________________" << endl;
		cout << "||                   _....,_         _,...._                      " << endl;
		cout << "||               _.-`       '.     .'       `-._                  0. Terugkeren." << endl;
		cout << "||                _,                         ,_                   1. Toevoegen aan wishlist." << endl;
		cout << "||                 '-. ___ .-`     `-. ___ .-'                    2. Wink (knipoogje) sturen!" << endl;
		cout << "||================================================================Uw Keuze:\t";

		int optie; cin >> optie;
		//Veilige invoer
		while ((optie > 3 || optie < 0)) {
			system("cls");
			cin.clear(); cin.ignore(1000, '\n');
			//TEXT-Art: http://www.network-science.de/ascii/
			cout << "||Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "||_______________/_/_/    _/      _/    _/                _/      " << endl;
			cout << "||____________/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/   " << endl;
			cout << "||_____________/_/      _/      _/    _/      _/        _/    _/  " << endl;
			cout << "||________________/    _/      _/    _/      _/        _/    _/   " << endl;
			cout << "||_________/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/    " << endl;
			cout << "==================================================================" << endl;
			if (!user->getPremium()) { cout << "                      " << user->getUsername() << "               " << endl << endl; }
			else cout << "||<[*_*[ PREMIUM ]*_*]>       " << user->getUsername() << "     <[*_*[ PREMIUM ]*_*]>" << endl << "||" << endl;//Premium
			cout << "||================================================================" << endl << endl;

			cout << "||Voornaam________________________________________________________" << p->getVoornaam() << endl;
			cout << "||Naam____________________________________________________________" << p->getNaam() << endl;
			cout << "||Leeftijd________________________________________________________" << p->leeftijd() << endl;
			cout << "||Geslacht________________________________________________________" << p->geslacht_voluit() << endl;
			if (activeUser->getPremium()) {
				cout << "||Relatiestatus___________________________________________________" << e->status_voluit() << endl;
				cout << "||Aantal keren op wishlists_______________________________________" << count << endl;
				cout << "||Haarkleur_______________________________________________________" << e->haarkleur_voluit() << endl;
				cout << "||OogKleur________________________________________________________" << e->oogkleur_voluit() << endl;
				cout << "||Lengte__________________________________________________________" << double(floor((double(e->getLengte()) / 100) * 100 + 0.5) / 100) << "m" << endl;
				cout << "||Horoscoop_______________________________________________________" << e->horoscoop_voluit() << endl;
				cout << "||Muziekstijl_____________________________________________________" << e->getMuziekstijl() << endl << endl;
				cout << "||================================================================" << endl;
				cout << "||================================================================" << endl << endl;
				for (int i = 0; i < h.size(); i++) {
					if (i == 0)cout << "||Hobbies:________________________________________________________" << h[i] << endl;
					else       cout << "||                                                                " << h[i] << endl;
				}
				cout << "||================================================================" << endl;
				cout << "||================================================================" << endl;
				cout << endl << "||Bechrijving: " << p->getBeschrijving() << endl;
			}	cout << "||" << endl << "||" << endl;
			cout << "||================================================================" << endl;
			cout << "||Wat wil je doen?________________________________________________" << endl;
			cout << "||                   _....,_         _,...._                      0. Terugkeren." << endl;
			cout << "||               _.-` _,..,_'.     .'_,..,_ `-._                  1. Bericht versturen." << endl;
			cout << "||                _,-`/ o \\ '.     .' / o \\`-,_                 2. Toevoegen aan wishlist." << endl;
			cout << "||            jgs  '-.\\___/.-`     `-.\\___/.-'                  3. Wink (knipoogje) sturen!" << endl;
			cout << "||                 Maak a.u.b. een geldige keuze.                 " << endl;
			cout << "||================================================================Uw Keuze:\t"; cin >> optie;
		}
		bool verstuurd = false; //bericht verstuurd?
		string bericht; //Daadwerkelijk bericht
		char emptyMsg; //Voor het bevestigen dat je een leeg bericht wil verzenden
		char prem; //Als je een prem-functie kiest en je bent geen premium. Is dit je keuze of je al dan niet wil upgraden.
		switch (optie) {
		case 2://wink
			if (activeUser->getPremium()) {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>          WINKS       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				if (ProfilesDAO::getProfile(activeUser->getUsername())->getWinksToGive() > 0) {
					if (UsersDAO::wink(activeUser->getUsername(), gekozenGebruiker)) {
						cout << "Wink verzonden.\nWe gaan terug naar het vorig scherm." << endl;
						system("pause");
					}

				}
				else {
					system("cls");
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>     NO MORE WINKS    <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					cout << "Je hebt geen WINKS meer om te versturen." << endl;
					cout << "Aan het begin van de volgende Premium-maand krijg je +15 WINKS cadeau!!!." << endl;
					system("pause");
				}
			}
			else {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/         " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/      " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/     " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/      " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/       " << endl;
				cout << "====================================================================" << endl;
				cout << "+oo((X))=============>     PREMIUM CONTENT    <=============((X))oo+" << endl;
				cout << "====================================================================" << endl << endl;
				cout << "U moet een Premium gebruiker zijn om WINKS te sturen." << endl;
				cout << "Wenst u te upgraden naar Premium?(J/N)" << endl;
				cin.clear(); cin.ignore(1000, '\n');
				cout << "Antwoord:\t"; prem = getchar();
				//Veilige invoer
				while (toupper(prem) != 'J' && toupper(prem) != 'N') {
					system("cls");
					cin.clear(); cin.ignore(1000, '\n');
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "================================================================" << endl;
					cout << "+oo((X))=============>    PREMIUM CONTENT   <=============((X))oo+" << endl;
					cout << "================================================================" << endl << endl;
					cout << "Foute invoer." << endl;
					cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
					cout << "Uw keuze:\t"; prem = getchar();
				}
				if (toupper(prem) == 'N') break;
				else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile = false; break;
			}
			break;
		case 1://Toevoegen aan wishlist meer dan 5 mensen op wishlist = [PREMIUM]
			if (activeUser->getPremium()) {
				if (!(WishlistDAO::exists(activeUser->getWishlistID(), gekozenGebruiker))) {
					if (WishlistDAO::add(activeUser->getWishlistID(), gekozenGebruiker))
						cout << gekozenGebruiker << " staat nu op je wishlist." << endl;
				}
				else cout << gekozenGebruiker << " staat al op je wishlist!" << endl;
				system("pause"); break;
			}
			else {
				if (ProfilesDAO::getProfile(activeUser->getUsername())->getWinksToGive() > 0) {
					if (!(WishlistDAO::exists(activeUser->getWishlistID(), gekozenGebruiker))) {
						if (WishlistDAO::add(activeUser->getWishlistID(), gekozenGebruiker))
							cout << gekozenGebruiker << " staat nu op je wishlist." << endl;
					}
					else cout << gekozenGebruiker << " staat al op je wishlist!" << endl;
					system("pause"); break;
				}
				else {
					system("cls");
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "================================================================" << endl;
					cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
					cout << "================================================================" << endl << endl;
					cout << "U moet een Premium gebruiker zijn om meer dan 5 mensen op je wishlist te zetten." << endl;
					cout << "Wenst u te upgraden naar Premium?(J/N)";
					cout << "Antwoord:\t"; prem = getchar();
					//Veilige invoer
					while (toupper(prem) != 'J' && toupper(prem) != 'N') {
						system("cls");
						cin.clear(); cin.ignore();
						cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
						cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
						cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
						cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
						cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
						cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						cout << "Foute invoer." << endl;
						cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
						cout << "Uw keuze:\t"; prem = getchar();
					}
					if (toupper(prem) == 'N') break;
					else *AppState = INSTELLINGEN; *settings = UPGRADE; returnToProfile == false; break;
				}
			}
			break;
		case 0: returnToProfile = false;
			/**AppState = BERICHTEN*/; break;
		}
	}
	return true;
}

vector<string> MENU::ShowWishlist(Users * user, Settings* settings, Status* AppState)
{
	vector<string> nameList;
	system("cls");
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "0. Terugkeren" << endl;
	vector<Users*> list = WishlistDAO::getList(user->getWishlistID());
	for (int i = 0; i < list.size(); i++) {
		nameList.push_back(list[i]->getUsername());
		cout << i + 1 << ". " << list[i]->getUsername() << endl;
	}

	cout << "==================================================================" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "Kies persoon:\t"; int persoon; cin >> persoon;
	if (persoon == 0) {*AppState = Status::MENU; return nameList; }
	while (persoon < 0 || persoon > list.size()) {
		system("cls");
		cin.clear(); cin.ignore(1000, '\n');
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "0. Terugkeren" << endl;
		list = WishlistDAO::getList(user->getWishlistID());
		for (int i = 0; i < list.size(); i++) {
			nameList.push_back(list[i]->getUsername());
			cout << i + 1 << ". " << list[i]->getUsername() << endl;
		}

		cout << "==================================================================" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "Kies persoon:\t"; int persoon; cin >> persoon;
	}
	if (persoon == 0) { *AppState = Status::MENU; return nameList; }
	system("cls");
	cin.clear(); cin.ignore(1000, '\n');
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "              Wat wil je doen met "<< list[persoon-1]->getUsername() << "?" << endl;
	cout << "					1. Verdijwderen" << endl;
	cout << "					2. Bericht versturen" << endl;
	cout << "					3. Wink Sturen" << endl;
	cout << "					4. Profiel Bekijken" << endl;
	cout << "					5. Terugkeren" << endl;
	cout << "				----- Uw keuze:\t"; int listKeuze; cin >> listKeuze;
	
	while (listKeuze < 1 || listKeuze > 5) {
		system("cls");
		cin.clear(); cin.ignore(1000, '\n');
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>          MENU        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "			Maak nu eens een geldige keuze aub ;-)" << endl;
		cout << "              Wat wil je doen met " << list[persoon - 1]->getUsername() << "?" << endl;
		cout << "					1. Verdijwderen" << endl;
		cout << "					2. Bericht versturen" << endl;
		cout << "					3. Wink Sturen" << endl;
		cout << "					4. Profiel Bekijken" << endl;
		cout << "					5. Terugkeren" << endl;
		cout << "				----- Uw keuze:\t"; int listKeuze; cin >> listKeuze;

	}
	
	bool verstuurd = false;
	char prem;
	char emptyMsg;
	string bericht;
	switch (listKeuze)
	{
	case 2://bericht
		if (user->getPremium()) {
			while (!verstuurd) {
				//system("cls");
				//cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				//cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
				//cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				//cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				//cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
				//cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				//cout << "==================================================================" << endl;
				//cout << "+oo((X))=============>        Bericht       <=============((X))oo+" << endl;
				//cout << "==================================================================" << endl << endl;
				cout << "Geen uw bericht in:\t"; cin.clear(); cin.ignore(1000, '\n'); getline(cin, bericht, '\n');
				if (bericht == "") {
					cout << "Dit bericht is leeg. Doorgaan? (j/n)\t"; emptyMsg = getchar();
					//Veilige invoer
					while (toupper(emptyMsg) != 'J' && toupper(emptyMsg) != 'N') {
						system("cls");
						cin.clear(); cin.ignore(1000, '\n');
						cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
						cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
						cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
						cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
						cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
						cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))=============>        Bericht       <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						cout << "Foute invoer." << endl;
						cout << "Druk 'J' om het leeg bericht naar " << gekozenGebruiker << " te versturen of 'N' om terug te gaan." << endl;
						cout << "Uw keuze:\t"; emptyMsg = getchar();
					}
					if (toupper(emptyMsg) == 'N') break;// Dit brengt hem terug naar de switch, daar wordt hij meteen terug naar de conversatie gestuurd.						
				}
				else {
					Messages msg(-1, user->getUsername(), list[persoon-1]->getUsername(), bericht); //Bericht object maken
					MessagesDAO::verzend(&msg); cout << "Bericht verstuurd." << endl; //Bericht verzenden naar DB
					verstuurd = true;
					system("pause"); break;
					//cout << "We gaan terug naar het vorig scherm." << endl; Sleep(2500); break;
				}
			}
		}
		else {
			system("cls");
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============>    PREMIUM CONTENT   <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			cout << "U moet een Premium gebruiker zijn om berichten te sturen." << endl;
			cout << "Wenst u te upgraden naar Premium?(J/N)";

			cout << "Antwoord:\t"; prem = getchar();
			//Veilige invoer
			while (toupper(prem) != 'J' && toupper(prem) != 'N') {
				system("cls");
				cin.clear(); cin.ignore(1000, '\n');
				cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "================================================================" << endl;
				cout << "+oo((X))=============>   PREMIUM CONTENT  <=============((X))oo+" << endl;
				cout << "================================================================" << endl << endl;
				cout << "Foute invoer." << endl;
				cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
				cout << "Uw keuze:\t"; prem = getchar();
			}
			if (toupper(prem) == 'N') break;
			else *AppState = INSTELLINGEN; *settings = UPGRADE; break;
		} //verboden voor niet Premium
		break;
	case 3://wink
		if (user->getPremium()) {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============>          WINKS       <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			if (ProfilesDAO::getProfile(user->getUsername())->getWinksToGive() > 0) {
				if (UsersDAO::wink(user->getUsername(), gekozenGebruiker)) {
					cout << "Wink verzonden.\nWe gaan terug naar het vorig scherm." << endl;
					system("pause");
				}

			}
			else {
				system("cls");
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>     NO MORE WINKS    <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Je hebt geen WINKS meer om te versturen." << endl;
				cout << "Aan het begin van de volgende Premium-maand krijg je +15 WINKS cadeau!!!." << endl;
				system("pause");
			}
		}
		else {
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "               _/_/_/    _/      _/    _/                _/         " << endl;
			cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/      " << endl;
			cout << "             _/_/      _/      _/    _/      _/        _/    _/     " << endl;
			cout << "                _/    _/      _/    _/      _/        _/    _/      " << endl;
			cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/       " << endl;
			cout << "====================================================================" << endl;
			cout << "+oo((X))=============>     PREMIUM CONTENT    <=============((X))oo+" << endl;
			cout << "====================================================================" << endl << endl;
			cout << "U moet een Premium gebruiker zijn om WINKS te sturen." << endl;
			cout << "Wenst u te upgraden naar Premium?(J/N)" << endl;
			cin.clear(); cin.ignore(1000, '\n');
			cout << "Antwoord:\t"; prem = getchar();
			//Veilige invoer
			while (toupper(prem) != 'J' && toupper(prem) != 'N') {
				system("cls");
				cin.clear(); cin.ignore(1000, '\n');
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "================================================================" << endl;
				cout << "+oo((X))=============>    PREMIUM CONTENT   <=============((X))oo+" << endl;
				cout << "================================================================" << endl << endl;
				cout << "Foute invoer." << endl;
				cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
				cout << "Uw keuze:\t"; prem = getchar();
			}
			if (toupper(prem) == 'N') break;
			else *AppState = INSTELLINGEN; *settings = UPGRADE; break;
		}
		break;
	case 4://Profile
		MENU::Msg_Profile(user, list[persoon - 1]->getUsername(), settings, AppState); break;
	case 5: *AppState = Status::WISHLIST; break;
	case 1:
		WishlistDAO::removeUser(user->getWishlistID(), list[persoon - 1]->getUsername()); break;
		system("cls");
		cin.clear(); cin.ignore(1000, '\n');
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>          WISHLIST        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "						Voldooid. " << list[persoon - 1] << "?" << endl;
		cout << "		"<< list[persoon-1]->getUsername() << " werd verwijderd." << endl;
		cout << endl << endl << endl; system("pause");
		*AppState = Status::WISHLIST; break;
	
	default:
		break;
	}

	return nameList;
}
