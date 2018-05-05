#include "stdAfx.h"
#include "DatabaseSingleton.h"

DatabaseSingleton* DatabaseSingleton::databaseSingleton=nullptr;

DatabaseSingleton::DatabaseSingleton()
{
	connection = nullptr;
	try{
		driver = get_driver_instance();
		connection = driver -> connect(URL, USER, PASSWORD);
		connection -> setAutoCommit(0);
		connection -> setSchema(DATABASE);
			} catch (SQLException &e) {
		cout<<"PROBLEM: "<<e.what()<<endl;
	}
}


DatabaseSingleton::~DatabaseSingleton()
{
	delete connection;
}


DatabaseSingleton* DatabaseSingleton::getInstance()
{
	if(databaseSingleton==nullptr)
		databaseSingleton = new DatabaseSingleton();
	return databaseSingleton;
}

Connection* DatabaseSingleton::getConnection()
{
	if (connection == nullptr || connection->isClosed())
	{

		if(connection!=nullptr)
			delete connection;

		try
		{
			connection = driver -> connect(URL, USER, PASSWORD);
			connection -> setAutoCommit(0);
			connection -> setSchema(DATABASE);
		} catch (SQLException &e) {
		cout<<"PROBLEM: "<<e.what()<<endl;
		return nullptr;
	}
	}
	return connection;
}