#pragma once
#include "stdafx.h"

class Wishlist
{
private:
	int wishlistID;
	string owner;
	vector<string>* list;

public:
	Wishlist(int ID, string owner);
	~Wishlist();

	int getID();
	string getOwner();
	vector <string>* getList();
	bool is_too_big(vector <string>* list);

	void setID(int);
	void setOwner(string);
	void setList(vector<string>*);

};

