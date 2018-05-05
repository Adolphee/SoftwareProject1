#pragma once
#include "stdafx.h"

class MessagesDAO
{
private:
	static Connection* con;
public:
	MessagesDAO();
	~MessagesDAO();
	static Messages* getMessage(int messageID);																//TEST OK
	static vector <Messages*> getConversation(string zender, string onvtanger);								//TEST OK				
	static Messages* verzend(Messages* bericht);															//TEST OK
	static vector<string> getContacten(string username);
};

