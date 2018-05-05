#include "WishlistDAO.h"
Connection* WishlistDAO::con = nullptr;


WishlistDAO::WishlistDAO()
{
}
WishlistDAO::~WishlistDAO()
{
}

vector<Users*> WishlistDAO::getList(int listID)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	vector<Users*> list;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return list;

		stmt = con->createStatement();
		stringstream zoekopdracht;
		zoekopdracht << "SELECT u.* FROM Users u, Wishlist w WHERE u.username = w.username AND w.wishlistID = ";
		zoekopdracht << listID;
		res = stmt->executeQuery(zoekopdracht.str());

		int j = 0;
		while (res->next()) {
			list.push_back(new Users(res->getString("username"), res->getString("password"), res->getString("securityQuestion"), res->getString("antwoord")));
			list[j]->setPremium(res->getBoolean("premium"));
			list[j]->setGratisPremium(res->getBoolean("gratisPremium"));
			list[j]->setOnline(res->getBoolean("online"));
			list[j]->setBeginDatumPremium(res->getString("beginDatumPremium"));
			list[j]->setWishlistID(res->getInt("wishlistID"));
			list[j]->setIsActief(res->getBoolean("isActief"));
			list[j]->setSalt(res->getString("salt"));
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


	return list;
}

int WishlistDAO::getID(string username)
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
		zoekopdracht << "SELECT wishlistID FROM Users where username = '";
		zoekopdracht << username << "'";
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

int WishlistDAO::createList()
{
	PreparedStatement *prep_stmt = nullptr;
	int wishlistID;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;

		con->setAutoCommit(0);//zet auto commit af
		prep_stmt = con->prepareStatement("INSERT INTO Wishlist_owners VALUES (NULL,NULL)");
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
		wishlistID = rs->getInt(1);
	}
	prep_stmt2->close();
	delete prep_stmt2;
	delete rs;

	con->commit();
	con->setAutoCommit(1);//zet auto commit terug aan
	return wishlistID;
}

bool WishlistDAO::add(int target_listID, string user_to_add)
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
		prep_stmt = con->prepareStatement("INSERT INTO Wishlist VALUES(?,?)");
		prep_stmt->setInt(1, target_listID);
		prep_stmt->setString(2, user_to_add);
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

bool WishlistDAO::exists(int target_listID, string user_to_seek)
{
	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	bool exists = false;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return exists;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT COUNT(*) FROM Wishlist WHERE wishlistID = ";
		zoekopdracht << target_listID << " AND username = '" << user_to_seek << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			if (res->getInt(1) != 0) exists = true; else exists = false;
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


	return exists;
}

bool WishlistDAO::removeUser(int target_listID, string user_to_delete)
{
	PreparedStatement *prep_stmt = nullptr;
	int updatecount;
	try {
		if (con == nullptr || con->isClosed())
		{
			DatabaseSingleton* d = DatabaseSingleton::getInstance();
			con = d->getConnection();
		}

		if (con == nullptr)
			return 0;

		con->setAutoCommit(0);//zet auto commit af
		prep_stmt = con->prepareStatement("DELETE FROM Wishlist WHERE wishlistID = ? AND username = ?");
		prep_stmt->setInt(1, target_listID);
		prep_stmt->setString(2, user_to_delete);
		updatecount = prep_stmt->executeUpdate();


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
	return (updatecount > 0);
}

bool WishlistDAO::clearList(int target_listID)
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
		prep_stmt = con->prepareStatement("DELETE FROM Wishlist WHERE wishlistID = ?");
		prep_stmt->setInt(1, target_listID);
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

bool WishlistDAO::clearList(string username)
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
		prep_stmt = con->prepareStatement("DELETE FROM Wishlist WHERE wishlistID = (SELECT wishlistID FROM Users WHERE username = ?)");
		prep_stmt->setString(1, username);
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

int WishlistDAO::wishlist_count(string username)
{

	ResultSet *res = nullptr;
	Statement *stmt = nullptr;
	int count = 0;

	try {
		if (con == nullptr || con->isClosed())
			con = DatabaseSingleton::getInstance()->getConnection();

		if (con == nullptr)
			return count;


		stmt = con->createStatement();

		stringstream zoekopdracht;
		zoekopdracht << "SELECT COUNT(*) FROM Wishlist WHERE username = '" << username << "'";
		res = stmt->executeQuery(zoekopdracht.str());

		if (res->next()) {
			count = res->getInt(1);
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


	return count;
}
