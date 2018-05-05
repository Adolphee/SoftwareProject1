#include "Wishlist.h"



Wishlist::Wishlist(int ID, string owner)
{
	this->wishlistID = ID;
	this->owner = owner;
}

Wishlist::~Wishlist()
{

}

int Wishlist::getID()
{
	return wishlistID;
}

string Wishlist::getOwner()
{
	return owner;
}

vector<string>* Wishlist::getList()
{
	return list;
}

bool Wishlist::is_too_big(vector<string>* list)
{
	return (list->size() >= 5);
}

void Wishlist::setID(int id)
{
	this->wishlistID = id;
}

void Wishlist::setOwner(string username)
{
	this->owner = username;
}

void Wishlist::setList(vector<string>* list)
{
	this->list = list;
}
