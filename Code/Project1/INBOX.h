#pragma once
#include "UsersDAO.h"
#include "WishlistDAO.h"
#include "ProfilesDAO.h"
#include "ExtrasDAO.h"
#include "InterestsDAO.h"
#include "HobbiesDAO.h"
#include "MessagesDAO.h"
class INBOX
{
public:
	INBOX();
	~INBOX();

	static Status showInbox(Users* activeUser, Settings* settings, Status* AppState, int* inboxOptie);
};

