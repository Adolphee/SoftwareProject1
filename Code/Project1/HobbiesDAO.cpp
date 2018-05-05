#include "HobbiesDAO.h"

Connection* HobbiesDAO::con = nullptr;


HobbiesDAO::HobbiesDAO()
{
}


HobbiesDAO::~HobbiesDAO()
{
}

int HobbiesDAO::getID(string naam)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	int ID = -1;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return ID;


		stmt = con->createStatement();

		//eerst de naam lowercase maken om te vergelijken met wat er in de DB staat
		transform(naam.begin(), naam.end(), naam.begin(), ::tolower);

		stringstream zoekopdracht;
		zoekopdracht << "SELECT hobbiesID FROM Hobbies where naam = '";
		zoekopdracht << naam << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			ID = res->getInt(1);
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


	return ID;
}

Hobbies * HobbiesDAO::getHobby(int ID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Hobbies* hobby = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return hobby;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Hobbies where hobbiesID = ";
		zoekopdracht << ID;
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			hobby = new Hobbies(res->getInt("hobbiesID"), res->getString("naam"));
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


	return hobby;
}

vector<string> HobbiesDAO::getAll(int profileID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<string> hobbies;
	vector<int> hobbiesIDs;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return hobbies;

		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT naam FROM Hobbies h, Profile_Hobbies ph WHERE h.hobbiesID = ph.hobbiesID AND ph.profileID = ";
		zoekopdracht << profileID;
		res = stmt->executeQuery(zoekopdracht.str());

		while (res->next()) {
			hobbies.push_back(res->getString("naam"));
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


	return hobbies;
}

bool HobbiesDAO::removeUserHobby(int profileID, int hobbiesID)
{
	PreparedStatement *prep_stmt = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;

		prep_stmt = con->prepareStatement("delete FROM Profile_Hobbies where profileID = ? AND hobbiesID = ?");
		prep_stmt->setInt(1, profileID);
		prep_stmt->setInt(2, hobbiesID);

		if (prep_stmt->executeUpdate() == 0)
			return false;

		con->commit();
		prep_stmt->close();
		delete prep_stmt;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		return false;
	}

	return true;
}

Hobbies * HobbiesDAO::saveHobby(Hobbies * hobby)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr || hobby == nullptr)
			return 0;

		if (hobby->getID() != -1)
		{
			stringstream zoekopdracht;
			zoekopdracht << "UPDATE Hobbies SET naam = ? WHERE hobbiesID = ";
			zoekopdracht << hobby->getID();
			prep_stmt = con->prepareStatement(zoekopdracht.str());
		}
		else
		{
			con->setAutoCommit(0);//zet auto commit af
			prep_stmt = con->prepareStatement("INSERT INTO Hobbies VALUES (NULL, ?)");
		}

		prep_stmt->setString(1, hobby->getNaam());


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


	if (hobby->getID() == -1)
	{
		PreparedStatement* prep_stmt2 = con->prepareStatement("SELECT LAST_INSERT_ID();");
		//ResultSet* rs = stmt->executeQuery("SELECT @@identity as id;");
		ResultSet* rs = prep_stmt2->executeQuery();

		if (rs->next())
		{
			hobby->setID(rs->getInt(1));
		}
		prep_stmt2->close();
		delete prep_stmt2;
		delete rs;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return hobby;
}

bool HobbiesDAO::exists(string naam)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	int ID = -1;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return ID;


		stmt = con->createStatement();

		//eerst de naam lowercase maken om te vergelijken met wat er in de DB staat
		transform(naam.begin(), naam.end(), naam.begin(), ::tolower);

		stringstream zoekopdracht;
		zoekopdracht << "SELECT hobbiesID FROM Hobbies where naam = '";
		zoekopdracht << naam << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			ID = res->getInt(1);
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


	return ID;
}
