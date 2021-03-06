#include "INBOX.h"
#include "MENU.h"
using namespace std;


INBOX::INBOX()
{
}


INBOX::~INBOX()
{
}

Status INBOX::showInbox(Users* activeUser, Settings* settings, Status* AppState, int* inboxOptie)
{
	//inboxOptie is voor opties binnen een inbox
	int convOptie;//opties binnen een conversatie
	bool inbox = true; //Om te bepalen wanneer de inboxfunctie mag stoppen
	bool con = false; //om te bepalen wanneer de conversatie mag geopend worden
	while (inbox == true) {
		system("cls");
		vector<string> conversaties = MessagesDAO::getContacten(activeUser->getUsername());
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>         INBOX        <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		for (int i = 0; i < conversaties.size(); i++) cout << i + 1 << ". " << conversaties[i] << endl;
		cout << "\nSelecteer conversatienummer of kies '0' om terug te gaan naar het hoofdmenu." << endl;
		cout << "Uw keuze:\t"; cin >> *inboxOptie;
		if (*inboxOptie < 1) inbox = false, *AppState = Status::MENU; else con = true;
		while (!cin>>*inboxOptie || *inboxOptie < 0 || *inboxOptie > conversaties.size()) {
			system("cls");
			cin.clear(); cin.ignore(1000, '\n');
			cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "==========================================================================================" << endl;
			cout << "==========================================INBOX===========================================" << endl << endl;
			for (int i = 0; i < conversaties.size(); i++) {
				cout << i + 1 << ". " << conversaties[i] << endl;
			}
			cout << "Kies een bestaande conversatie a.u.b. (0 = stop)" << endl;
			cout << "\nSelecteer conversatienummer:\t"; cin >> *inboxOptie;
		}
		if (*inboxOptie == 0) { *AppState = Status::MENU; break; }
		
		if(*inboxOptie >0) gekozenGebruiker = conversaties[*inboxOptie - 1]; //Dit maakt het voor mij gemakkelijker om te typen over wie het gaat. + leesbaarheid
		while (con) {
			system("cls");
			//cin.clear(); cin.ignore();
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============>         " << gekozenGebruiker << "        <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			vector<Messages*> convo = MessagesDAO::getConversation(activeUser->getUsername(), gekozenGebruiker);
			for (int i = 0; i < convo.size(); i++) {
				cout << convo[i]->toString();
			}
			cout << endl << endl;
			if (gekozenGebruiker == "Admin") {
				cout << "===================================================================" << endl;
				cout << "+oo((X))=============> 	        SLUIT         <=============((X))oo+" << endl;
				cout << "===================================================================" << endl;
				system("pause"); break;
			}
			else {
				cout << "===================================================================" << endl;
				cout << " 1. Antwoord    2. Wink   3. Wishlist   4. Profile   0. Terugkeren " << endl;
				cout << "===================================================================" << endl;
				cout << "Uw keuze:\t" << endl; cin >> convOptie;
				//veilige invoer
				while (!(convOptie >= 0 && convOptie < 5)) {
					system("cls");
					cin.clear(); cin.ignore(1000, '\n');
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "==================================================================" << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>         " << gekozenGebruiker << "        <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					for (int i = 0; i < convo.size(); i++) {
						cout << convo[i]->toString();
					}
					cout << endl << endl; // Als het bericht van een Admin komt is het onmogelijk om op dit scherm te komen dus hier geen if-controle
					cout << "==================================================================" << endl;
					cout << "1. Antwoord\t2. Wink\t3. Wishlist\t4. Profile\t0. Terugkeren" << endl;
					cout << "Maakt a.u.b. een gelidige keuze deze keer." << endl;
					cout << "==================================================================" << endl;
					cout << "Uw keuze:\t"; cin >> convOptie;
				}
				string bericht; //...
				char emptyMsg; //leeg bericht versturen?
				bool verstuurd = false; //...
				char prem; //Just in case iemand plots wil premium worden
				switch (convOptie) {
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
									cout << "Druk 'J' om het leeg bericht naar " << gekozenGebruiker << "te versturen of 'N' om terug te gaan." << endl;
									cout << "Uw keuze:\t"; emptyMsg = getchar();
								}
								if (toupper(emptyMsg) == 'N') break;// Dit brengt hem terug naar de switch, daar wordt hij meteen terug naar de conversatie gestuurd.						
							}
							else {
								Messages msg(-1, activeUser->getUsername(), gekozenGebruiker, bericht); //Bericht object maken
								MessagesDAO::verzend(&msg); cout << "Bericht verstuurd." << endl; //Bericht verzenden naar DB
								verstuurd = true; break;
								//cout << "We gaan terug naar het vorig scherm." << endl; Sleep(2500); break;
							}
						}
					}
					else {
						system("cls");
						cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
						cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
						cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
						cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
						cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
						cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))ΞΞΞΞΞΞΞΞΞΞΞΞΞ>   Premium  Content   <ΞΞΞΞΞΞΞΞΞΞΞΞΞ((X))oo+" << endl;
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
							cout << "+oo((X))ΞΞΞΞΞΞΞΞΞΞΞΞΞ>  Premium  Content  <ΞΞΞΞΞΞΞΞΞΞΞΞΞ((X))oo+" << endl;
							cout << "================================================================" << endl << endl;
							cout << "Foute invoer." << endl;
							cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
							cout << "Uw keuze:\t"; prem = getchar();
						}
						if (toupper(prem) == 'N') break;
						else *settings = UPGRADE; *AppState =  Status::INSTELLINGEN;
					} //verboden voor niet Premium
					break;
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
						cout << "+oo((X))=============>        WINKS         <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						if (ProfilesDAO::getProfile(activeUser->getUsername())->getWinksToGive() > 0) {
							if (UsersDAO::wink(activeUser->getUsername(), gekozenGebruiker)) {
								cout << "Wink verzonden.\nWe gaan terug naar het vorig scherm." << endl;
								Sleep(2000);
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
						cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
						cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
						cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
						cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
						cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						cout << "U moet een Premium gebruiker zijn om WINKS te sturen." << endl;
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
						else *settings = UPGRADE; *AppState = Status::INSTELLINGEN;
					}
					break;
				case 3://Toevoegen aan wishlist meer dan 5 mensen op wishlist = [PREMIUM]
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
									cout << conversaties[*inboxOptie - 1] << " staat nu op je wishlist." << endl;
							}
							else cout << gekozenGebruiker << " staat al op je wishlist!" << endl; break;
						}
						else {
							system("cls");
							cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
							cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
							cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
							cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
							cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
							cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
							cout << "==================================================================" << endl;
							cout << "+oo((X))=============>   Premium  Content   <=============((X))oo+" << endl;
							cout << "==================================================================" << endl << endl;
							cout << "U moet een Premium gebruiker zijn om meer dan 5 mensen op je wishlist te zetten." << endl;
							cout << "Wenst u te upgraden naar Premium?(J/N)";
							cout << "Antwoord:\t"; prem = getchar();
							//Veilige invoer
							while (toupper(prem) != 'J' && toupper(prem) != 'N') {
								system("cls");
								cin.clear(); cin.ignore();
								cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
								cout << "               _/_/_/    _/      _/    _/                _/     " << endl;
								cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
								cout << "             _/_/      _/      _/    _/      _/        _/    _/ " << endl;
								cout << "                _/    _/      _/    _/      _/        _/    _/  " << endl;
								cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
								cout << "================================================================" << endl;
								cout << "+oo((X))ΞΞΞΞΞΞΞΞΞΞΞΞΞ>  Premium  Content  <ΞΞΞΞΞΞΞΞΞΞΞΞΞ((X))oo+" << endl;
								cout << "================================================================" << endl << endl;
								cout << "Foute invoer." << endl;
								cout << "Druk 'J' om het om te upgraden naar Premium of 'N' om terug te gaan." << endl;
								cout << "Uw keuze:\t"; prem = getchar();
							}
							if (toupper(prem) == 'N') break;
							else *settings = UPGRADE; *AppState = Status::INSTELLINGEN;
						}
					}
					break;
				case 4:	//Profile bekijken
					MENU::Msg_Profile(activeUser, gekozenGebruiker, settings, AppState);
					break;
				case 0: con = false; break;
				}
			}
		}
	}
	return *AppState;
}
