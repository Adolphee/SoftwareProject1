#include "UsersDAO.h"

Connection* UsersDAO::con = nullptr;


string random_string() {
	//salt genereren, stukje code die random alphanum string genereert. 
	//Credits: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
	string salt = "";
	for (int i = 0; i < LENGTE_SALT; i++)
	{

		switch (rand() % 3)
		{
		case 0:
			salt += ('0' + rand() % 10);
			break;
		case 1:
			salt += ('A' + rand() % 26);
			break;
		case 2:
			salt += ('a' + rand() % 26);
			break;
		}
	}
	return salt;
}


string UsersDAO::getPassword(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	string password;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return "";


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT password FROM Users where username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			password = res->getString(1);
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}


	return password;
}

UsersDAO::UsersDAO()
{
}
UsersDAO::~UsersDAO()
{
}

bool UsersDAO::wink(string zender, string ontvanger)
{
	if (zender == ontvanger) return false; else {
		//Dit wordt een giant DAO methode vergeleken met de rest dus hou je vast
		PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr, *prep_stmt5 = nullptr;
		try {
			if (con == nullptr || con->isClosed())
			{
				DatabaseSingleton* d = DatabaseSingleton::getInstance();
				con = d->getConnection();
			}

			if (con == nullptr)
				return 0;

			//Bij de ontvanger de ontvangen winks incrementeren
			stringstream opdracht1;
			opdracht1 << "UPDATE Profiles SET winksReceived = winksReceived+1 WHERE username = '" << ontvanger << "'";
			prep_stmt = con->prepareStatement(opdracht1.str());
			int updatecount1 = prep_stmt->executeUpdate();

			//Bij de verzender de winks die overblijven decrementeren
			stringstream opdracht2;
			opdracht2 << "UPDATE Profiles SET winksToGive = winksToGIve-1 WHERE username = '" << zender << "'";
			prep_stmt2 = con->prepareStatement(opdracht2.str());
			int updatecount2 = prep_stmt2->executeUpdate();

			//De ontvanger op de hoogte brengen met een bericht
			stringstream inhoud; inhoud << "[KNIPOOGJE] ontvangen van " << zender << "!!" << endl;
			Messages bericht(-1, "Admin", ontvanger, inhoud.str());
			stringstream opdracht5;
			con->setAutoCommit(0);//zet auto commit af
			prep_stmt5 = con->prepareStatement("INSERT INTO Messages VALUES (NULL, ?, ?, ?, NULL)");
			prep_stmt5->setString(1, bericht.getZenderID());
			prep_stmt5->setString(2, bericht.getOntvangerID());
			prep_stmt5->setString(3, bericht.getInhoud());
			int updatecount5 = prep_stmt5->executeUpdate();

			//con -> commit();
			prep_stmt->close();
			prep_stmt2->close();
			prep_stmt5->close();
			delete prep_stmt;
			delete prep_stmt2;
			delete prep_stmt5;
		}
		catch (SQLException &e)
		{
			cout << "PROBLEM: " << e.what() << endl;
			if (prep_stmt != nullptr)
				delete prep_stmt;
			if (prep_stmt2 != nullptr)
				delete prep_stmt2;
			if (prep_stmt5 != nullptr)
				delete prep_stmt5;
			return 0;
		}

		con->commit();
		con->setAutoCommit(1);
		return true;
	}
}
//eigenlijk is getIsActief() overbodig
bool UsersDAO::getIsActief(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	bool isActief = false;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return isActief;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT isActief FROM Users where username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			isActief = res->getBoolean(1);
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}


	return isActief;
}

bool UsersDAO::check_beschikbaarheid(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	bool beschikbaar = true;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT count(*) FROM Users where username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next() && res->getInt(1) > 0) {
			beschikbaar = false; //username gevonden? dan bestaat hij al en is hij dus niet meer beschikbaar
		}

		stmt->close();
		con->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}


	return beschikbaar;
}

//Deze ook, dit is gewoon voor users die ik al in DB had geplaatst voordat ik de Encryptie toevoegde
string UsersDAO::generate_salt(string username)
{
	string salt = random_string();

	//salt wegschrijven naar DB
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return "";

		stringstream zoekopdracht;
		zoekopdracht << "UPDATE Users SET salt = ? WHERE username = ?";;
		prep_stmt = con->prepareStatement(zoekopdracht.str());		
		prep_stmt->setString(1, salt);
		prep_stmt->setString(2, username);
		prep_stmt->executeUpdate();

		prep_stmt->close();
		delete prep_stmt;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		return "";
	}

	con->commit();
	return salt;
}
//Deze ook
string UsersDAO::getSalt(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	string salt;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return "";


		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT salt FROM Users WHERE username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			salt = res->getString(1);
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}

	return salt;
}

int UsersDAO::get_aantal_online()
{

	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	int OnlineUsers = NULL;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return OnlineUsers;


		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT COUNT(*) FROM Users WHERE online = 1");

		if (res->next()) {
			OnlineUsers = res->getInt(1);
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}


	return OnlineUsers;
}

PremiumStatus UsersDAO::premium_overtijd(Users* user)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return OVERTIJD;


		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT beginDatumPremium FROM Users WHERE username = '";
		zoekopdracht << user->getUsername() << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			user->setBeginDatumPremium(res->getString(1));
		}


		if (user->getBeginDatumPremium() != "" && user->getPremium()) {
			if (user->getGratisPremium()) user->setGratisPremium(false);
		}


		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}
	if (user->getBeginDatumPremium() == "") return OVERTIJD;
	return PremiumStatus(datumvergelijking(user->getBeginDatumPremium(), currentDate()));
}

string UsersDAO::getUsername(int profileID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	string username = "";

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return username;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT username FROM Profiles where profileID = ";
		zoekopdracht << profileID;
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			username = res->getString(1);
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}


	return username;
}

//Profiles * UsersDAO::getProfile(string username)
//{
//	ResultSet *res = nullptr;
//	Statement *stmt = nullptr;
//	Profiles* profile = nullptr;
//
//	try {
//		if (con == nullptr || con->isClosed())
//			con = DatabaseSingleton::getInstance()->getConnection();
//
//		if (con == nullptr)
//			return profile;
//		
//
//		stmt = con->createStatement();
//
//		stringstream zoekopdracht;
//		zoekopdracht << "SELECT * FROM Profiles where username = '";
//		zoekopdracht << username <<"'";
//		res = stmt->executeQuery(zoekopdracht.str());
//
//		if (res->next()) {
//			profile = new Profiles(res->getInt("profileID"), res->getString("username"), res->getString("naam"), 
//				res->getString("voornaam"), res->getString("geboortedatum"), res->getInt("interestID"), 
//				res->getInt("extrasID"), res->getInt("geslacht"), res->getInt("zoekt"));
//		}
//
//		stmt->close();
//		delete stmt;
//		delete res;
//
//		//con ->close();
//	}
//	catch (SQLException &e) {
//		cout << "PROBLEM: " << e.what() << endl;
//		con->close();
//
//		if (stmt != nullptr)
//			delete stmt;
//		if (res != nullptr)
//			delete res;
//	}
//
//
//	return profile;
//}


Users * UsersDAO::getUser(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Users* user = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return user;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Users where username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			user = new Users(res->getString("username"), res->getString("password"), res->getString("securityQuestion"), res->getString("antwoord"));
			user->setPremium(res->getBoolean("premium"));
			user->setGratisPremium(res->getBoolean("gratisPremium"));
			user->setOnline(res->getBoolean("online"));
			user->setBeginDatumPremium(res->getString("beginDatumPremium"));
			user->setWishlistID(res->getInt("wishlistID"));
			user->setIsActief(res->getBoolean("isActief"));
			user->setSalt(res->getString("salt"));
			int vandaag = 0;
			int beginPremium = 0;
		};

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	}

	//Premium-wijzigingen opslaan & exit.
	//saveUser(user); 
	return user;
}

//bool UsersDAO::logIN(string username, string password)
//{
//	if (getPassword(username) == password) {
//		Users* user = getUser(username);
//		user->setOnline(true);
//		update(user);
//		return true;
//	}
//	return false;
//}
//
//bool UsersDAO::logOUT(string username)
//{
//	Users* user = getUser(username);
//	user->setOnline(false);
//	update(user);
//	return true;
//}

Users* UsersDAO::addUser(Users * user)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;

		con->setAutoCommit(0);//zet auto commit af
		prep_stmt = con->prepareStatement("INSERT INTO Users VALUES (?,?,?,?,0,1,?,?,1,?,?,?)");

		prep_stmt->setString(1, user->getUsername());
		prep_stmt->setString(2, user->getPassword());
		prep_stmt->setString(3, user->getSalt());
		prep_stmt->setString(4, PEPPER);
		prep_stmt->setString(5, user->getBeginDatumPremium());
		prep_stmt->setBoolean(6, user->getOnline());
		prep_stmt->setInt(7, user->getWishlistID());
		prep_stmt->setString(8, user->getQuestion());
		prep_stmt->setString(9, user->getAnswer());
		int updatecount = prep_stmt->executeUpdate();

		//con -> commit();
		prep_stmt->close();
		delete prep_stmt;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		return 0;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return user;
}

bool UsersDAO::update(Users * user)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;

		stringstream zoekopdracht;
		zoekopdracht << "UPDATE Users SET username = ?, password = ?, premium = ?, gratisPremium = ?, beginDatumPremium = ?, online = ?, isActief = ?, salt = ?, securityQuestion = ?, antwoord = ? WHERE username = ?";
		prep_stmt = con->prepareStatement(zoekopdracht.str());

		prep_stmt->setString(1, user->getUsername());
		prep_stmt->setString(2, user->getPassword());
		prep_stmt->setBoolean(3, user->getPremium());
		prep_stmt->setBoolean(4, user->getGratisPremium());
		prep_stmt->setString(5, user->getBeginDatumPremium());
		prep_stmt->setBoolean(6, user->getOnline());
		prep_stmt->setBoolean(7, user->getIsActief());
		prep_stmt->setString(8, user->getSalt());
		prep_stmt->setString(9, user->getQuestion());
		prep_stmt->setString(10, user->getAnswer());
		prep_stmt->setString(11, user->getUsername());
		int updatecount = prep_stmt->executeUpdate();


		//con -> commit();
		prep_stmt->close();
		delete prep_stmt;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		return 0;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return true;
}

bool UsersDAO::update(Users * user, string target_username)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;

		stringstream zoekopdracht;
		zoekopdracht << "UPDATE Users SET username = ?, password = ?, premium = ?, gratisPremium = ?, beginDatumPremium = ?, online = ?, isActief = ?, salt = ?, securityQuestion = ?, antwoord = ? WHERE username = ?";
		prep_stmt = con->prepareStatement(zoekopdracht.str());

		prep_stmt->setString(1, user->getUsername());
		prep_stmt->setString(2, user->getPassword());
		prep_stmt->setBoolean(3, user->getPremium());
		prep_stmt->setBoolean(4, user->getGratisPremium());
		prep_stmt->setString(5, user->getBeginDatumPremium());
		prep_stmt->setBoolean(6, user->getOnline());
		prep_stmt->setBoolean(7, user->getIsActief());
		prep_stmt->setString(8, user->getSalt());
		prep_stmt->setString(9, user->getQuestion());
		prep_stmt->setString(10, user->getAnswer());
		prep_stmt->setString(11, target_username);
		int updatecount = prep_stmt->executeUpdate();


		//con -> commit();
		prep_stmt->close();
		delete prep_stmt;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		return 0;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return true;
}

bool UsersDAO::removeUser(string username)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr, *prep_stmt3 = nullptr;
	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;

		//Elke persoon eerst van de wishlist halen
		prep_stmt3 = con->prepareStatement("DELETE FROM Wishlist WHERE wishlistID = (SELECT wishlistID from Wishlist_owners WHERE username = ?)");
		prep_stmt3->setString(1, username);
		prep_stmt3->executeUpdate();
		//foreignKey verwijderen
		prep_stmt2 = con->prepareStatement("DELETE FROM Wishlist_owners WHERE username = ?");
		prep_stmt2->setString(1, username);
		prep_stmt2->executeUpdate();
		//user verwijderen
		prep_stmt = con->prepareStatement("DELETE FROM Users WHERE username = ?");
		prep_stmt->setString(1, username);
		prep_stmt->executeUpdate();
			

		con->commit();
		prep_stmt->close();
		prep_stmt2->close();
		prep_stmt3->close();
		delete prep_stmt;
		delete prep_stmt2;
		delete prep_stmt3;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		if (prep_stmt2 != nullptr)
			delete prep_stmt2;
		if (prep_stmt3 != nullptr)
			delete prep_stmt3;
		return false;
	}

	return true;
}

vector<string> UsersDAO::zoek_geslacht(Geslacht voorkeur)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<string> users;
	vector<string*> users2;
	string naam;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return users;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT username FROM Profiles where geslacht = ";
		zoekopdracht << voorkeur;
		res = stmt->executeQuery(zoekopdracht.str());
		
		while (res->next()) {
			users.push_back(res->getString("username"));
			
		}

		stmt->close();
		delete stmt;
		delete res;

		//con ->close();
	}
	catch (SQLException &e) {
		cout << "PROBLEM: " << e.what() << endl;
		con->close();

		if (stmt != nullptr)
			delete stmt;
		if (res != nullptr)
			delete res;
	} 
	return users;
}



