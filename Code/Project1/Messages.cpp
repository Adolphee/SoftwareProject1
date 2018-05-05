#include "Messages.h"

Messages::Messages(int messageID, string zenderID, string ontvangerID, string inhoud)
{
	this->messageID = messageID;
	this->zenderID = zenderID;
	this->ontvangerID = ontvangerID;
	this->inhoud = inhoud;
}

Messages::~Messages()
{

}

string Messages::toString()
{
	stringstream ss;
	ss << zenderID << ":\n\t" << inhoud << endl;

	return ss.str();
}

int Messages::getMessageID()
{
	return messageID;
}

string Messages::getZenderID()
{
	return zenderID;
}

string Messages::getOntvangerID()
{
	return ontvangerID;
}

string Messages::getInhoud()
{
	return inhoud;
}

string Messages::getTimeStamp()
{
	return timestamp;
}

void Messages::setMessageID(int ID)
{
	this->messageID = ID;
}

void Messages::setZenderID(string username)
{
	this->zenderID = username;
}

void Messages::setOntvangerID(string username)
{
	this->ontvangerID = username;
}

void Messages::setInhoud(string bericht)
{
	this->inhoud = bericht;
}

void Messages::setTimeStamp(string timestamp)
{
	this->timestamp = timestamp;
}



