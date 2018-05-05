#include "InterestsDAO.h"
Connection* InterestsDAO::con = nullptr;


InterestsDAO::InterestsDAO()
{
}
InterestsDAO::~InterestsDAO()
{
}

int InterestsDAO::getID(int profileID)
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

		stringstream zoekopdracht;
		zoekopdracht << "SELECT interestID FROM Profiles where profileID = ";
		zoekopdracht << profileID;
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

Interests * InterestsDAO::getInterests(int interestID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Interests* interest = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return interest;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Interests where interestID = ";
		zoekopdracht << interestID;
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			interest = new Interests(res->getInt("interestID"), res->getBoolean("sport"), res->getBoolean("natuur"),
				res->getBoolean("kunst"), res->getBoolean("games"), res->getBoolean("technologie"), res->getBoolean("wetenschap"),
				res->getBoolean("cultuur"), res->getBoolean("reizen"), res->getBoolean("filosofie"), res->getBoolean("conspiracy"),
				res->getBoolean("sociale_media"), res->getBoolean("muziek"), res->getBoolean("fotografie"), res->getBoolean("dieren"));
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


	return interest;
}

bool InterestsDAO::removeUserInterests(int profileID, int interestID)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;

		prep_stmt2 = con->prepareStatement("UPDATE Profiles SET interestID = NULL where profileID = ?");
		prep_stmt2->setInt(1, profileID);

		if (prep_stmt2->executeUpdate() == 0)
			return false;

		prep_stmt = con->prepareStatement("delete FROM Interests where interestID = ?");
		prep_stmt->setInt(1, interestID);

		if (prep_stmt->executeUpdate() == 0)
			return false;

		con->commit();
		prep_stmt->close();
		prep_stmt2->close();
		delete prep_stmt;
		delete prep_stmt2;
	}
	catch (SQLException &e)
	{
		cout << "PROBLEM: " << e.what() << endl;
		if (prep_stmt != nullptr)
			delete prep_stmt;
		if (prep_stmt2 != nullptr)
			delete prep_stmt2;
		return false;
	}

	return true;
}

bool InterestsDAO::saveInterests(Interests * interest)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr || interest == nullptr)
			return 0;

		if (interest->getID() != -1)
		{
			stringstream zoekopdracht;
			zoekopdracht << "UPDATE Interests SET sport = ?, natuur = ?, kunst = ?, games = ?, technologie = ?, wetenschap = ?, cultuur = ?, reizen = ?, filosofie = ?, conspiracy = ?, sociale_media = ?, muziek = ?, fotografie = ?, dieren = ? WHERE interestID = ";
			zoekopdracht << interest->getID();
			prep_stmt = con->prepareStatement(zoekopdracht.str());
		}
		else
		{
			con->setAutoCommit(0);//zet auto commit af
			prep_stmt = con->prepareStatement("INSERT INTO Interests VALUES (NULL, ?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
		}

		prep_stmt->setBoolean(1, interest->getSport());
		prep_stmt->setBoolean(2, interest->getNatuur());
		prep_stmt->setBoolean(3, interest->getKunst());
		prep_stmt->setBoolean(4, interest->getGames());
		prep_stmt->setBoolean(5, interest->getTechnologie());
		prep_stmt->setBoolean(6, interest->getWetenschap());
		prep_stmt->setBoolean(7, interest->getCultuur());
		prep_stmt->setBoolean(8, interest->getReizen());
		prep_stmt->setBoolean(9, interest->getFilosofie());
		prep_stmt->setBoolean(10, interest->getSamenzweringstheoriën());
		prep_stmt->setBoolean(11, interest->getSocialeMedia());
		prep_stmt->setBoolean(12, interest->getMuziek());
		prep_stmt->setBoolean(13, interest->getFotografie());
		prep_stmt->setBoolean(14, interest->getDieren());


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


	if (interest->getID() == -1)
	{
		PreparedStatement* prep_stmt2 = con->prepareStatement("SELECT LAST_INSERT_ID();");

		ResultSet* rs = prep_stmt2->executeQuery();

		if (rs->next())
		{
			interest->setID(rs->getInt(1));
		}
		prep_stmt2->close();
		delete prep_stmt2;
		delete rs;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return interest;
}
