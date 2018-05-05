#pragma once
#include "stdafx.h"

class ExtrasDAO
{
private:
	static Connection *con;
public:
	ExtrasDAO();
	~ExtrasDAO();
	static Extras* saveExtras(Extras *extras);													//TEST OK
	static Extras* getExtras(int profileID);													//TEST OK
	static bool removeExtras(int profileID/*Voor de Foreign Key*/, int extrasID);				//TEST OK


};

