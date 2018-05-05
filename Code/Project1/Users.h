#pragma once
#include "stdafx.h"
class Users
{
protected:
	string random_string();
private:
	static Connection* con;
	string username;
	string password;
	string salt = "";
	string pepper = PEPPER;
	bool premium = false;
	bool online = false;
	bool isActief = true;
	int wishlistID;
	string beginDatumPremium = "";
	bool gratisPremium = true;
	string securityQuestion;
	string antwoord;
public:
	Users(string username, string password, string question, string answer);
	~Users();

	int getWishlistID();
	string getQuestion();
	string getAnswer();
	string getBeginDatumPremium();
	string getUsername();
	string getPassword();
	string getSalt();
	string getPepper();
	bool getPremium();
	bool getOnline();
	bool getIsActief();
	bool getGratisPremium();

	void setQuestion(string);
	void setAnswer(string);
	void setWishlistID(int);
	void setGratisPremium(bool);
	void setBeginDatumPremium(string datum);
	void setUsername(string);
	void setPassword(string);
	void setSalt(string);
	void setPremium(bool);
	void setOnline(bool);
	void setIsActief(bool);

};

