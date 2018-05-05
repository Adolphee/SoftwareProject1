#pragma once
#include "stdafx.h"

class InterestsDAO
{
private:
	static Connection* con;
public:
	InterestsDAO();
	~InterestsDAO();

	static int getID(int profileID);												//TEST OK
	static Interests* getInterests(int ID);											//TEST OK
	static bool removeUserInterests(int profileID, int interestID);					//TEST OK				
	static bool saveInterests(Interests* interest);									//TEST OK


};

