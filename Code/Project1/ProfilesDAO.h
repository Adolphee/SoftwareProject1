#pragma once
#include "Profiles.h"

class ProfilesDAO
{
private:
	static Connection * con;
public:
	ProfilesDAO();
	~ProfilesDAO();

	static int getProfileID(string username);										//TEST OK
	static Profiles* getProfile(string username);									//TEST OK
	static Profiles* addProfile(Profiles* profile);									//TEST OK
	static bool deleteProfile(int profileID);										//TEST OK
	static bool updateProfile(Profiles* profile);									//TEST OK	

};

