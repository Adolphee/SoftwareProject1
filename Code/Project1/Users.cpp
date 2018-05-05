#include "Users.h"




string Users::random_string()
{
	//salt genereren, stukje code die random alphanum string genereert. 
	//Credits: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
	string salt = "";
	for (int i = 0; i < 32; i++)
	{

		switch (rand() % 3)
		{
		case 0:
			salt += ('0' + rand() % 10);
			break;
		case 1:
			salt += ('A' + rand() % 26);
			break;
		case 2:
			salt += ('a' + rand() % 26);
			break;
		}
	}
	return salt;
}

Users::Users(string username, string password, string question, string answer)
{
	this->username = username;
	this->password = password;
	this->securityQuestion = question;
	this->antwoord = answer;
}

Users::~Users()
{
}

int Users::getWishlistID()
{
	return wishlistID;
}

string Users::getQuestion()
{
	return securityQuestion;
}

string Users::getAnswer()
{
	return antwoord;
}

string Users::getBeginDatumPremium()
{
	return this->beginDatumPremium;
}

string Users::getUsername()
{
	return username;
}

string Users::getPassword()
{
	return password;
}

string Users::getSalt()
{
	return salt;
}

string Users::getPepper()
{
	return pepper;
}

bool Users::getPremium()
{
	return premium;
}

bool Users::getOnline()
{
	return online;
}

bool Users::getIsActief()
{
	return isActief;
}

bool Users::getGratisPremium()
{
	return gratisPremium;
}

void Users::setQuestion(string question)
{
	this->securityQuestion = question;
}

void Users::setAnswer(string antwoord)
{
	this->antwoord = antwoord;
}

void Users::setWishlistID(int ID)
{
	this->wishlistID = ID;
}

void Users::setGratisPremium(bool gratis)
{
	this->gratisPremium = gratis;
}

void Users::setBeginDatumPremium(string datum)
{
	this->beginDatumPremium = datum;
}

void Users::setUsername(string username)
{
	this->username = username;
}

void Users::setPassword(string password)
{
	this->password = password;
}

void Users::setSalt(string salt)
{
	if (salt != "") this->salt = salt;
}

void Users::setPremium(bool premium)
{
	this->premium = premium;
	if (premium) setBeginDatumPremium(currentDate());
}

void Users::setOnline(bool online)
{
	this->online = online;
}

void Users::setIsActief(bool isActief)
{
	this->isActief = isActief;
}

