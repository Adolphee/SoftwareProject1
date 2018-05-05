#pragma once
#include "stdafx.h"
class DatabaseSingleton
{
private:
	Connection* connection;
	Driver *driver;
	DatabaseSingleton();
	static DatabaseSingleton* databaseSingleton;
	

public:
	static DatabaseSingleton* getInstance();
	Connection* getConnection();
	~DatabaseSingleton();
};

