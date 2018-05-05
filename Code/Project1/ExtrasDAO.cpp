#include "ExtrasDAO.h"

Connection* ExtrasDAO::con = nullptr;

bool ExtrasDAO::removeExtras(int profileID, int extrasID)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;

		prep_stmt = con->prepareStatement("UPDATE Profiles SET extrasID = NULL where profileID = ?");
		prep_stmt->setInt(1, profileID);
		if (prep_stmt->executeUpdate() == 0)
			return false;

		prep_stmt2 = con->prepareStatement("delete FROM Extras where extrasID = ?");
		prep_stmt2->setInt(1, extrasID);
		if (prep_stmt2->executeUpdate() == 0)
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

ExtrasDAO::ExtrasDAO()
{
}

ExtrasDAO::~ExtrasDAO()
{
}

Extras* ExtrasDAO::saveExtras(Extras *extras)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr || extras == nullptr)
			return 0;

		if (extras->getID() != -1)
		{
			stringstream zoekopdracht;
			zoekopdracht << "UPDATE Extras SET horoscoop = ? , haarkleur = ?, oogkleur = ?, lengte = ?, love_status = ? , muziekstijl = ? where extrasID = ?";
			prep_stmt = con->prepareStatement(zoekopdracht.str());
			prep_stmt->setInt(7, extras->getID());
		}
		else
		{
			con->setAutoCommit(0);//zet auto commit af
			prep_stmt = con->prepareStatement("INSERT INTO Extras VALUES (NULL, ?,?,?,?,?,?)");
		}

		prep_stmt->setString(1, extras->getHoroscoop());
		prep_stmt->setString(2, extras->getHaarkleur());
		prep_stmt->setString(3, extras->getOogKleur());
		prep_stmt->setInt(4, extras->getLengte());
		prep_stmt->setString(5, extras->getStatus());
		prep_stmt->setString(6, extras->getMuziekstijl());
		int updatecount = prep_stmt->executeUpdate();

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


	if (extras->getID() == -1)
	{
		PreparedStatement* prep_stmt2 = con->prepareStatement("SELECT LAST_INSERT_ID();");
		//ResultSet* rs = stmt->executeQuery("SELECT @@identity as id;");
		ResultSet* rs = prep_stmt2->executeQuery();

		if (rs->next())
		{
			extras->setID(rs->getInt(1));
		}
		prep_stmt2->close();
		delete prep_stmt2;
		delete rs;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return extras;
}


Extras* ExtrasDAO::getExtras(int profileID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Extras* extras = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return extras;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT e.* FROM Extras e, Profiles p WHERE e.extrasID = p.extrasID AND p.profileID = '";
		zoekopdracht << profileID << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			extras = new Extras(res->getInt("extrasID"), res->getString("horoscoop"), res->getString("haarkleur"), res->getString("oogkleur"), res->getInt("lengte"), res->getString("love_status"), res->getString("muziekstijl"));
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


	return extras;
}
