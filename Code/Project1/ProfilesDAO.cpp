#include "ProfilesDAO.h"
Connection* ProfilesDAO::con = nullptr;


ProfilesDAO::ProfilesDAO()
{
}
ProfilesDAO::~ProfilesDAO()
{
}

int ProfilesDAO::getProfileID(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	int profileID = -1;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return profileID;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT profileID FROM Profiles where username = '";
		zoekopdracht << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			profileID = res->getInt(1);
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


	return profileID;
}


Profiles * ProfilesDAO::getProfile(string username)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Profiles* profile = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return profile;
		

		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Profiles where username = '";
		zoekopdracht << username <<"'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			profile = new Profiles(res->getInt("profileID"), res->getString("username"), res->getString("naam"),
				res->getString("voornaam"), res->getString("geboortedatum"));
			profile->setInterestID(res->getInt("interestID"));
			profile->setExtrasID(res->getInt("extrasID"));
			profile->setGeslacht(Geslacht(res->getInt("geslacht")));
			profile->setZoekt(Geslacht(res->getInt("zoekt")));
			profile->setWinksReceived(res->getInt("winksReceived"));
			profile->setWinksToGive(res->getInt("winksToGive"));
			profile->setBeschrijving(res->getString("beschrijving"));
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


	return profile;
}

Profiles * ProfilesDAO::addProfile(Profiles * profile)
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
		prep_stmt = con->prepareStatement("INSERT INTO Profiles VALUES (NULL,?,?,?,?,NULL,NULL,0,15,?,?,?)");

		prep_stmt->setString(1, profile->getUsername());
		prep_stmt->setString(2, profile->getNaam());
		prep_stmt->setString(3, profile->getVoornaam());
		prep_stmt->setString(4, profile->getGeboorteDatum());
		prep_stmt->setInt(5, profile->getGeslacht());
		prep_stmt->setInt(6, profile->getZoekt());
		prep_stmt->setString(7, profile->getBeschrijving());
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

	PreparedStatement* prep_stmt2 = con->prepareStatement("SELECT LAST_INSERT_ID();");
	ResultSet* rs = prep_stmt2->executeQuery();

	if (rs->next())
	{
		profile->setID(rs->getInt(1));
	}
	prep_stmt2->close();
	delete prep_stmt2;
	delete rs;

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return profile;
}

bool ProfilesDAO::deleteProfile(int profileID)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr, *prep_stmt4 = nullptr, *prep_stmt5 = nullptr, *prep_stmt6 = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;
		
		prep_stmt = con->prepareStatement("DELETE FROM Addresses WHERE adresID = (SELECT adresID FROM Profile_Addresses WHERE profileID = ?)");
		prep_stmt->setInt(1, profileID); int updatecount = prep_stmt->executeUpdate();
		prep_stmt4 = con->prepareStatement("DELETE FROM Studies WHERE studiesID = (SELECT studiesID FROM Profile_Studies WHERE profileID = ?)");
		prep_stmt4->setInt(1, profileID); int updatecount4 = prep_stmt4->executeUpdate();
		
		prep_stmt5 = con->prepareStatement("DELETE FROM Interests WHERE interestID = (SELECT interestID FROM Profiles WHERE profileID = ?)");
		prep_stmt5->setInt(1, profileID); int updatecount5 = prep_stmt5->executeUpdate();

		prep_stmt6 = con->prepareStatement("DELETE FROM Extras WHERE extrasID = (SELECT extrasID FROM Profiles WHERE profileID = ?)");
		prep_stmt6->setInt(1, profileID); int updatecount6 = prep_stmt6->executeUpdate();

		prep_stmt2 = con->prepareStatement("DELETE FROM Profiles WHERE profileID = ?");
		prep_stmt2->setInt(1, profileID); int updatecount2 = prep_stmt2->executeUpdate();

		//con -> commit();
		prep_stmt->close();
		prep_stmt2->close();
		prep_stmt4->close();
		prep_stmt5->close();
		prep_stmt6->close();

		delete prep_stmt;
		delete prep_stmt2;
		delete prep_stmt4;
		delete prep_stmt5;
		delete prep_stmt6;


	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		if (prep_stmt2 != nullptr)
			delete prep_stmt2;
		if (prep_stmt4 != nullptr)
			delete prep_stmt4;
		if (prep_stmt5 != nullptr)
			delete prep_stmt5;
		if (prep_stmt6 != nullptr)
			delete prep_stmt6;
		return 0;
	}

	
	con->commit();
	return true;
}

bool ProfilesDAO::updateProfile(Profiles * profile)
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
		zoekopdracht << "UPDATE Profiles SET username = ?, naam = ?, voornaam = ?, geboortedatum = ?, geslacht = ?, zoekt = ?, interestID = ?, extrasID = ?, beschrijving = ? WHERE profileID = ?";
		prep_stmt = con->prepareStatement(zoekopdracht.str());

		prep_stmt->setString(1, profile->getUsername());
		prep_stmt->setString(2, profile->getNaam());
		prep_stmt->setString(3, profile->getVoornaam());
		prep_stmt->setString(4, profile->getGeboorteDatum());
		prep_stmt->setInt(5, profile->getGeslacht());
		prep_stmt->setInt(6, profile->getZoekt());
		prep_stmt->setInt(7, profile->getInterestID());
		prep_stmt->setInt(8, profile->getExtrasID());
		prep_stmt->setString(9, profile->getBeschrijving());
		prep_stmt->setInt(10, profile->getID());

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

