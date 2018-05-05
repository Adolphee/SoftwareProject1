#pragma once
#include "stdafx.h"

class Messages
{
private:
	int messageID;
	string zenderID;
	string ontvangerID;
	string inhoud;
	string timestamp;
public:
	Messages(int messageID, string zenderID, string ontvangerID, string inhoud);
	~Messages();



	int getMessageID();
	string getZenderID();
	string getOntvangerID();
	string getInhoud();
	string getTimeStamp();

	void setMessageID(int ID);
	void setZenderID(string username);
	void setOntvangerID(string username);
	void setInhoud(string bericht);
	void setTimeStamp(string timestamp);

	string toString();
};

