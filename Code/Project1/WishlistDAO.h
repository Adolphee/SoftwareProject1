#pragma once
#include "stdafx.h"

class WishlistDAO
{
private:
	static Connection* con;
	//static bool delete_list(int listID);
public:
	WishlistDAO();
	~WishlistDAO();

	static vector<Users*> WishlistDAO::getList(int listID);									//TEST OK
	static int getID(string username);														//TEST OK
	static int createList();																//TEST OK

	static bool add(int target_listID, string user_to_add);									//TEST OK
	static bool exists(int target_listID, string user_to_seek);								//TEST OK
	static bool removeUser(int target_listID, string user_to_delete);						//TEST OK
	static bool clearList(int target_listID);												//TEST OK
	static bool clearList(string username);													//TEST OK
	static int wishlist_count(string username);
};

