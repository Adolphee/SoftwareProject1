#include "MessagesDAO.h"
Connection* MessagesDAO::con = nullptr;


Messages * MessagesDAO::getMessage(int messageID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	Messages* message = nullptr;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return message;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Messages where messageID = ";
		zoekopdracht << messageID;
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			message = new Messages(res->getInt("messageID"), res->getString("zenderID"), res->getString("ontvangerID"), res->getString("inhoud"));
			message->setTimeStamp(res->getString("timestamp"));
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


	return message;
}

MessagesDAO::MessagesDAO()
{
}
MessagesDAO::~MessagesDAO()
{
}

vector<Messages*> MessagesDAO::getConversation(string persoon1, string persoon2)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<Messages*> conversatie;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return conversatie;

		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT * FROM Messages WHERE (zenderID = '" << persoon1;
		zoekopdracht << "' and ontvangerID = '" << persoon2 << "') OR (zenderID = '" << persoon2;
		zoekopdracht << "' and ontvangerID = '" << persoon1 << "') ORDER BY timestamp ASC";

		res = stmt->executeQuery(zoekopdracht.str());

		int j = 0;
		while (res->next()) {
			conversatie.push_back(new Messages(res->getInt("messageID"), res->getString("zenderID"), res->getString("ontvangerID"), res->getString("inhoud")));
			conversatie[j]->setTimeStamp(res->getString("timestamp"));
			j++;
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


	return conversatie;
}

Messages* MessagesDAO::verzend(Messages * bericht)
{
	if (bericht->getInhoud() == "") bericht->setInhoud("[Leeg bericht]");
	PreparedStatement *prep_stmt = nullptr;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr || bericht == nullptr)
			return 0;


		con->setAutoCommit(0);//zet auto commit af
		prep_stmt = con->prepareStatement("INSERT INTO Messages VALUES (NULL, ?, ?, ?, NULL)");


		prep_stmt->setString(1, bericht->getZenderID());
		prep_stmt->setString(2, bericht->getOntvangerID());
		prep_stmt->setString(3, bericht->getInhoud());

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
	//ResultSet* rs = stmt->executeQuery("SELECT @@identity as id;");
	ResultSet* rs = prep_stmt2->executeQuery();

	if (rs->next())
	{
		bericht->setMessageID(rs->getInt(1));
	}
	prep_stmt2->close();
	delete prep_stmt2;
	delete rs;

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return bericht;
}

vector<string> MessagesDAO::getContacten(string persoon1)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<string> namen;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return namen;

		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT zenderID FROM `Messages` WHERE ontvangerID = '" << persoon1 << "' UNION SELECT ontvangerID From Messages WHERE zenderID = '" << persoon1 << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		while (res->next()) {
			namen.push_back(res->getString("zenderID"));
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


	return namen;
}

