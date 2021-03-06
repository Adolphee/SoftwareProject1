#include "LOGIN.h"
#include <windows.h>
#include <cstdlib> 
using namespace std;

string LOGIN::getUsername()
{
	string username;
	cout << endl << "Username:\t";
	getline(cin, username);
	cin.clear();
	return username;
}
string LOGIN::getPass(const char *prompt, bool show_asterisk = true)
{
	//http://www.cplusplus.com/articles/E6vU7k9E/#WIN
	const char BACKSPACE = 8;
	const char RETURN = 13;

	string password;
	unsigned char ch = 0;

	cout << endl << prompt;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (password.length() != 0)
			{
				if (show_asterisk)
					cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch;
			if (show_asterisk)
				cout << '^';
		}
	}
	cout << endl;
	return password;
}
bool LOGIN::authenticate(string username, string passwoord)
{
	Users* user = UsersDAO::getUser(username);
	if (user != nullptr) {
		if (Encrypt(string(passwoord + user->getSalt())) + PEPPER == user->getPassword()) {
			return true;
		}
	} return false;
}
Users* LOGIN::startScherm(Settings* settings, Status* AppState)
{
	int j = 0;
	string username = "#", passwoord = "#";
	Users* user = nullptr;
	//om te bepalen hoeveel keer dat de while loopt
	int keer37 = 0;//idem
	bool login_attempt = true;
	char prem;int keer = 0;
	bool ingelogd = false; //om te bapalen wanneer de login mag worden weggeschreven naar DB
	while (login_attempt) {		
		if (keer37 > 0) cin.clear(),  cin.ignore();
		while (passwoord == "" || username == "" || !authenticate(username, passwoord)) {
			if (passwoord != "" && username != "") {
				cin.clear();
				system("cls");
				cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>        STITCH       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl ;
				cout << "Registratie: Beide velden openlaten" << endl;
				cout << "Watchwoord vergeten? Enkel wachtwoord openlaten." << endl<< endl;
				if (keer > 0) { cout << "Fout. Probeer opnieuw." << endl;  }
				if (keer > 1) cout << "Laat ENKEL je wachtwoord leeg indien je deze vergeten bent. (username leeg = registratie)" << endl;
				cout << "Username:\t";
				getline(cin, username, '\n');
				passwoord = getPass("Passwoord:\t", true);
				bool alnum = true;
				for (int i = 0; i < username.size(); i++) {
					if (!isalnum(username[i])) alnum = false; break;
				}
				while (!alnum) {
					system("cls");
					cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>        LOGIN         <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					cout << "Registratie: Beide velden openlaten" << endl;
					cout << "Watchwoord vergeten? Enkel wachtwoord openlaten." << endl;
					cout << "Speciale tekens zijn niet toegestaan. Probeer opnieuw.		       " << endl;
					cout << "Username:\t";
					getline(cin, username, '\n');
					passwoord = getPass("Passwoord:\t", true);
					alnum = true;
					for (int i = 0; i < username.size(); i++) {
						if (!isalnum(username[i])) alnum = false; break;
					}
				}
				ingelogd = authenticate(username, passwoord);
				if (ingelogd) {
					login_attempt = false;
					current_loggedIN_Username = username;
					break;
				}
			}
			else if (passwoord == "" && username != "") {
				system("cls");
				cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>        HERSTEL       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Proces voor wachtwoord herstel geactiveerd." << endl; Sleep(2000); system("cls");
				cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>        HERSTEL       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				cout << "Weet je jouw Username nog? \t\t\t--Ja (J) / Nee (N) / Exit (X)--" << endl;
				cout << "Antwoord:\t"; 
				char antw = toupper(getchar());
				int keer2 = 0;
				//veilige invoer
				while (antw != 'J' && antw != 'N' && antw != 'X') {
					system("cls");
					cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
					cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
					cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
					cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
					cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
					cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
					cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
					cout << "==================================================================" << endl;
					cout << "+oo((X))=============>        HERSTEL       <=============((X))oo+" << endl;
					cout << "==================================================================" << endl << endl;
					cout << "Foutieve invoer. Druk 'J'(ja) als je je username nog weet, anders 'N'(Nee)." << endl;
					if (keer2 > 3) cout << "Druk 'X' om te stoppen." << endl;
					cout << "Uw keuze:\t";  
					cin.clear(); cin.ignore(1000, '\n'); 
					antw = toupper(getchar());
					keer2++;
				}
				system("cls");
				cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
				cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
				cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
				cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
				cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
				cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
				cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
				cout << "==================================================================" << endl;
				cout << "+oo((X))=============>        HERSTEL       <=============((X))oo+" << endl;
				cout << "==================================================================" << endl << endl;
				switch (antw) {
				case 'J'://Wachtwoord vergeten
					cout << "Username:\t"; cin.clear(), cin.ignore(1000, '\n'); getline(cin, username, '\n');
					user = UsersDAO::getUser(username);
					//veilige invoer
					while (user == nullptr && username != "") {
						system("cls");
						cout << "Welkom op STITCH, uw GPS naar je verlangens_______________________" << endl;
						cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
						cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
						cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
						cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
						cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
						cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
						cout << "==================================================================" << endl;
						cout << "+oo((X))=============>        HERSTEL       <=============((X))oo+" << endl;
						cout << "==================================================================" << endl << endl;
						cout << "Deze gebruiker bestaat niet. Probeer opnieuw." << endl;
						cout << "Geef een lege username in om te stoppen." << endl << endl;
						cout << "Username:\t"; getline(cin, username, '\n');
						user = UsersDAO::getUser(username);
					}
					if (user != nullptr && recovery_Question(user, AppState)) break;
				case 'N'://Watchwoord en username vergeten.
					cout << "Contacteer de systeembeheerder (Admin@domainname.com) voor nader onderzoek." << endl;
					username = "#"; passwoord = "#";
					system("pause");
				case 'X': cin.clear(); cin.ignore(1000, '\n'); return user;
				}
			}
			else return registratie(AppState);
			keer++;
		}
		keer37++;
	}
	user = UsersDAO::getUser(username);
	if (user != nullptr) {
		user->setOnline(true); //Aangeven dat de user online is (voor de teller)
		current_loggedIN_Username = user->getUsername();
		*AppState = Status::MENU;
	}	
	ingelogd = true;
	PremiumStatus p = UsersDAO::premium_overtijd(user);
	switch (p) {
	case OK: *AppState = MENU;
		break;
	case LAATSTE_DAG:
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "               _/_/_/    _/      _/    _/                _/       " << endl;
		cout << "            _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/    " << endl;
		cout << "             _/_/      _/      _/    _/      _/        _/    _/   " << endl;
		cout << "                _/    _/      _/    _/      _/        _/    _/    " << endl;
		cout << "         _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/     " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))ΞΞΞΞΞΞΞΞΞΞΞΞΞ>    !  OPGELET  !     <ΞΞΞΞΞΞΞΞΞΞΞΞΞ((X))oo+" << endl;
		cout << "==================================================================" << endl;
		cout << "OPGELET: Vandaag is uw laatste premiumdag. " << endl;
		cout << "Verlengt u vandaag niet, dan zal u vanaf morgen alle voordelen van een premium-lidmaatschap verliezen." << endl<< endl;
		cout << "Wenst u te een verlenging aan te schaffen?(J/N)";
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
			cout << "+oo((X))ΞΞΞΞΞΞΞΞΞΞΞΞΞ>   !  OPGELET  !    <ΞΞΞΞΞΞΞΞΞΞΞΞΞ((X))oo+" << endl;
			cout << "================================================================" << endl << endl;
			cout << "Foute invoer." << endl;
			cout << "Druk 'J' om het om Premium te verlengen of 'N' om gewoon door te gaan." << endl;
			cout << "Uw keuze:\t"; prem = getchar();
		}
		if (toupper(prem) == 'N') break;
		else { *AppState = INSTELLINGEN; *settings = UPGRADE; login_attempt = false; break; }
		break;
	case OVERTIJD:
		user->setPremium(false);
		break;
	}
	if(UsersDAO::update(user)) *AppState = MENU; return user;
	return nullptr;
}

Users * LOGIN::registratie(Status* AppState)
{
	string username, passwoord, bevestiging, security, antwoord;
	system("cls");
	username = registreer_Username();
	if (username == "") return nullptr;
	system("cls"); cout << "Uw username is " << username << "." << endl;
	passwoord = registreer_Wachtwoord(username);
	if (passwoord == "") return nullptr;
	system("cls"); cout << "Wachtwoord opgeslaan." << endl << endl;
	security = registreer_Security();
	if (security == "") return nullptr;
	system("cls"); 
	antwoord = registreer_Antwoord(security);
	if (antwoord == "") return nullptr;
	string salt = random_string();
	Users *nieuwGebruiker = new Users(username, Encrypt(string(passwoord + salt))+PEPPER, security, Encrypt(string(antwoord + salt)) + PEPPER);
	nieuwGebruiker->setWishlistID(WishlistDAO::createList());
	nieuwGebruiker->setSalt(salt);
	nieuwGebruiker = UsersDAO::addUser(nieuwGebruiker);	
	*AppState = Status::LOGIN;
	return nieuwGebruiker;
}

string LOGIN::registreer_Username()
{
	string username;
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>  REGISTER  USERNAME  <=============((X))oo+" << endl;
	cout << "==================================================================" << endl;
	cout << "Registratie-procedure gestart." << endl << endl;
	cout << "Kies een username:\t"; getline(cin, username, '\n');
	bool alnum = true;
	for (int i = 0; i < username.size(); i++) {
		if (!isalnum(username[i])) alnum = false; break;
	}
	while (!UsersDAO::check_beschikbaarheid(username) || username.size() < 5 || username == "" || !alnum) {
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>  REGISTER  USERNAME  <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		if (username == "X") username = ""; return "";
		if (username.size() >= 5 && username != "")
			cout << username << " wordt helaas al gebruikt door iemand. Kies een andere." << endl;			
		else if (username.size() < 5) {
			if (username == "X" || username == "x") return "";
			cout << "De username hoort minimum 5 characters lang te zijn." << endl;
		}
		else if(username == "") cout << "De username mag niet leeg zijn." << endl;
		else if(!alnum) {
			cout << "Speciale tekens zijn verboden. Probeer opnieuw." << endl;
		}
		cout << "Geef 'X' in om terug te keren." << endl;
		cout << "Username:\t"; getline(cin, username, '\n');
		alnum = true;
		for (int i = 0; i < username.size(); i++) {
			if (!isalnum(username[i])) alnum = false; break;
		}
	}
	return username;
}

string LOGIN::registreer_Wachtwoord(string username)
{
	string passwoord;
	string bevestiging;
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>  REGISTER  PASSWORD  <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	passwoord = getPass("Kies een wachtwoord:\t", true);
	bevestiging = getPass("Bevestig wachtwoord:\t", true);
	int keer4 = 0;
	while (passwoord != bevestiging || (passwoord == "" && bevestiging == "") || passwoord.size() < 8 || passwoord == "X") {
		system("cls"); 
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>  REGISTER  PASSWORD  <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
			if (passwoord == "X" || passwoord == "x") return "";
			if (passwoord == "") cout << "Wachtwoord mag niet leeg zijn." << endl;
			else if(passwoord.size() < 8) cout << "Het wachtwoord moet minstens 8 character lang zijn." << endl;
			else cout << "Wachtwoorden komen niet overeen. Probeer opnieuw." << endl;
			if (keer4 > 2) cout << "Geef 'X' in om terug te gaan." << endl;
		passwoord = getPass("Nieuw wachtwoord:\t", true);
		bevestiging = getPass("Nieuw wachtwoord:\t", true);
		keer4++;
	}
	return passwoord;
}

string LOGIN::registreer_Security()
{
	string security;
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>  SECURITY  QUESTION  <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "Kies een 'Security Question'." << endl;
	cout << "Als je ooit je wachtwoord vergeet, dan kan je die door deze vraag te beantwoorden gemakkelijk resetten." << endl;
	cout << "Security Question:\t"; /*cin.clear(); cin.ignore(1000, '\n');*/ getline(cin, security, '\n');
	while (security == "" || security.size() < 10) {
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>  SECURITY  QUESTION  <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		if (security == "X") return "";
		if (security == "") {
			cout << "De Security Question mag niet leeg zijn." << endl;
			cout << "Geef 'X' in om de registratie te annuleren." << endl;
			cout << "Security Question:\t"; getline(cin, security, '\n');
		}
		else {
			cout << "De Security Question mag niet kleiner dan 10 tekens zijn." << endl;
			cout << "Geef 'X' in om de registratie te annuleren." << endl;
			cout << "Security Question:\t"; getline(cin, security, '\n');
		}
	}
	return security;
}

string LOGIN::registreer_Antwoord(string security)
{
	string antwoord;
	string antw_Bevestiging;
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>   REGISTER  ANSWER   <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "Uw vraag is: " << security << endl;
	antwoord = getPass("Wat is het antwoord op je vraag?:\t", true);
	antw_Bevestiging = getPass("Bevestiging:\t", true);
	while (antwoord == "" || antwoord.size() < 2 || antwoord != antw_Bevestiging || antwoord == "X") {
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>   REGISTER  ANWER    <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		if (antwoord == "X") return "";
		if (antwoord.size() < 2) {
			cout << "Het antwoord moet langer zijn dan 1 teken." << endl;
			cout << "Geef 'X' in om te stoppen." << endl;
			cout << "De vraag is: " << security << endl;
			antwoord = getPass("Geef een langer antwoord:\t", true);
			antw_Bevestiging = getPass("Bevestiging:\t", true);
		}
		else if (antwoord == antw_Bevestiging && antwoord == "") {
			cout << "Je hebt geen antwoord gegeven." << endl;
			cout << "Doe dit a.u.b. of geef 'X' in om te stoppen." << endl;
			cout << "De vraag is: " << security << endl;
			antwoord = getPass("Antwoord:\t", true);
			antw_Bevestiging = getPass("Bevestiging:\t", true);
		}
		else if (antwoord != antw_Bevestiging) {
			cout << "Wachtwoorden komen niet overeen. Probeer opnieuw." << endl;
			cout << "Geef 'X' in om te stoppen." << endl;
			cout << "De vraag is: " << security << endl;
			antwoord = getPass("Antwoord:\t", true);
			antw_Bevestiging = getPass("Bevestiging:\t", true);
		}
	}
	return antwoord;
}

bool LOGIN::reset_passwoord(Users* user, Status* AppState) {
	string nieuwPass = "X", bevestiging = "Y";
	int keer3 = 0;
	while (nieuwPass != bevestiging || (nieuwPass == "" && bevestiging == "") || nieuwPass.size() < 8) {
		system("cls");
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>    RESET  PASSWORD   <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		if (keer3 > 0) {
			if (nieuwPass == bevestiging && nieuwPass == "") cout << "Wachtwoord mag niet leeg zijn." << endl;
			else cout << "Wachtwoorden komen niet overeen. Probeer opnieuw." << endl;
			if(nieuwPass == bevestiging && nieuwPass.size() < 8)
			if (keer3 > 2) cout << "Geef een lege bevestiging in om terug te gaan. (Wachtwoord moet ingevuld zijn)" << endl;
		}
		nieuwPass = getPass("Nieuw wachtwoord:\t",true);
		bevestiging = getPass("Bevestiging:\t", true);
		keer3++;
	}
	if (nieuwPass == bevestiging) {
		user->setPassword(Encrypt(string(nieuwPass + user->getSalt())) + PEPPER); UsersDAO::update(user);
		cout << "Wachtwoord bijgewerkt." << endl;
		cout << "We breng je terug naar het begin." << endl;
		Sleep(3000);
	}
	*AppState = Status::LOGIN;
	return false;
}

bool LOGIN::recovery_Question(Users* user, Status* AppState) {

	*AppState = Status::LOGIN;
	system("cls");
	cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
	cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
	cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
	cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
	cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
	cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
	cout << "==================================================================" << endl;
	cout << "+oo((X))=============>  SECURITY  QUESTION  <=============((X))oo+" << endl;
	cout << "==================================================================" << endl << endl;
	string antwoord;
	if (user->getQuestion() != "") {
		system("cls"); 
		cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
		cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
		cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
		cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
		cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
		cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
		cout << "==================================================================" << endl;
		cout << "+oo((X))=============>  SECURITY  QUESTION  <=============((X))oo+" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "De security vraag moet juist beantwoord worden om je wachtwoord te kunnen resetten." << endl;
		cout << "We moeten 100% zeker zijn dat jij dit account hebt aangemaakt." << endl;
		cout << "Het antwoord is hoofdlettergevoelig." << endl << endl;
		cout << user->getQuestion() << endl << "Antwoord:\t";
		getline(cin, antwoord, '\n');
		if (antwoord == "") return false;
		int keer = 0;
		//veilige invoer
		while (Encrypt(string(antwoord + user->getSalt())) + PEPPER != user->getAnswer() && keer < 3){
			system("cls");
			cout << "Users Online: " << UsersDAO::get_aantal_online() << "_________________________________________________" << endl;
			cout << "                 _/_/_/    _/      _/    _/                _/     " << endl;
			cout << "              _/        _/_/_/_/      _/_/_/_/    _/_/_/  _/_/_/  " << endl;
			cout << "               _/_/      _/      _/    _/      _/        _/    _/ " << endl;
			cout << "                  _/    _/      _/    _/      _/        _/    _/  " << endl;
			cout << "           _/_/_/        _/_/  _/      _/_/    _/_/_/  _/    _/   " << endl;
			cout << "==================================================================" << endl;
			cout << "+oo((X))=============>  SECURITY  QUESTION  <=============((X))oo+" << endl;
			cout << "==================================================================" << endl << endl;
			cout << "Dit is een foutief antwoord. Je hebt nog " << 3 - keer << "pogingen te gaan." << endl;
			if (keer > 1) cout << "Geef een leeg wachtwoord om terug te gaan naar Login." << endl << endl;
			cout << user->getQuestion() << endl << "Antwoord:\t"; getline(cin, antwoord, '\n');
			if (antwoord == "") return false;
			keer++;
		}
		if (Encrypt(string(antwoord + user->getSalt())) + PEPPER == user->getAnswer()) {
			return reset_passwoord(user, AppState);			
		}
		else {
			cout << "Het spijt ons. Maar we kunnen u niet vertrouwen op dit moment." << endl;
			cout << "Contacteer de systeembeheerder (Admin@domainname.com) voor nader onderzoek." << endl;
			Sleep(5000);
		}
	}
	else {
		cout << "Deze gebruiker heeft nooit een 'security question' ingesteld." << endl;
		cout << "Contacteer de systeembeheerder (Admin@domainname.com) voor nader onderzoek." << endl;
		Sleep(5000);
	}
	return false;
}
 