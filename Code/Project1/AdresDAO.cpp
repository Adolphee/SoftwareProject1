#include "AdresDAO.h"
Connection* AdresDAO::con = nullptr;


AdresDAO::AdresDAO()
{
}

AdresDAO::~AdresDAO()
{
}

bool AdresDAO::removeAdres(int profileID, int adresID)
{
	PreparedStatement *prep_stmt = nullptr, *prep_stmt2 = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return false;

		prep_stmt = con->prepareStatement("delete FROM Profile_Addresses where profileID = ? AND adresID = ?");
		prep_stmt->setInt(1, profileID), prep_stmt->setInt(2, adresID);
		prep_stmt->executeUpdate();

		prep_stmt2 = con->prepareStatement("delete FROM Addresses where adresID = ?");
		prep_stmt2->setInt(1, adresID);
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

vector<Adres*> AdresDAO::getAll(int profileID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<Adres*> adressen;
	vector<int> adresIDs;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return adressen;

		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT a.adresID FROM Addresses a, Profile_Addresses pa WHERE pa.adresID = a.adresID AND pa.profileID = ";
		zoekopdracht << profileID;
		res = stmt->executeQuery(zoekopdracht.str());

		while (res->next())
			adresIDs.push_back(res->getInt(1));
		for (int i = 0; i < adresIDs.size(); i++) 
			adressen.push_back(AdresDAO::getAdres(adresIDs[i]));

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


	return adressen;
}
//Adressen ophalen van een persoon
Adres* AdresDAO::getAdres(int adresID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Adres* adres = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return adres;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Addresses where adresID = ";
		zoekopdracht << adresID;
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			adres = new Adres(res->getInt("adresID"), res->getString("land"), res->getString("provincie"), res->getInt("postcode"), res->getString("gemeente"), res->getString("straatnaam"), res->getInt("huisnummer"), res->getInt("bus"));
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


	return adres;
}

//Adres aanpassen/toevoegen
Adres* AdresDAO::saveAdres(Adres* adres)
{
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr || adres == nullptr)
			return 0;

		if (adres->getID() != -1)
		{
			stringstream zoekopdracht;
			zoekopdracht << "UPDATE Addresses SET land = ? , provincie = ?, postcode = ?, gemeente = ?, straatnaam = ? , huisnummer = ?, bus = ? where adresID = ";
			zoekopdracht << adres->getID();
			prep_stmt = con->prepareStatement(zoekopdracht.str());
		}
		else
		{
			con->setAutoCommit(0);//zet auto commit af
			prep_stmt = con->prepareStatement("INSERT INTO Addresses VALUES (NULL, ?,?,?,?,?,?,?)");
		}

		prep_stmt->setString(1, adres->getLand());
		prep_stmt->setString(2, adres->getProvincie());
		prep_stmt->setInt(3, adres->getPostcode());
		prep_stmt->setString(4, adres->getGemeente());
		prep_stmt->setString(5, adres->getStraat());
		prep_stmt->setInt(6, adres->getHuisnummer());
		prep_stmt->setInt(7, adres->getBus());
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


	if (adres->getID() == -1)
	{
		PreparedStatement* prep_stmt2 = con->prepareStatement("SELECT LAST_INSERT_ID();");
		//ResultSet* rs = stmt->executeQuery("SELECT @@identity as id;");
		ResultSet* rs = prep_stmt2->executeQuery();

		if (rs->next())
		{
			adres->setID(rs->getInt(1));
		}
		prep_stmt2->close();
		delete prep_stmt2;
		delete rs;
	}

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return adres;
}


