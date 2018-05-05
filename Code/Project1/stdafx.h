#pragma once
#define INTRO_PREMIUM 3 //3 dagen gratis premium voor nieuwkomers
#define LENGTE_SALT 32
#define PEPPER "PEPPER"

//#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;


#include "include\cppconn\connection.h"
#include "include\cppconn\driver.h"
#include "Gegevens.h"
using namespace sql;

#include "DatabaseSingleton.h"
#include "include\cppconn\prepared_statement.h"
#include "include\cppconn\exception.h"

//Klassen
#include "Adres.h"
#include "Extras.h"
#include "Hobbies.h"
#include "Interests.h"
#include "Users.h"
#include "Messages.h"
#include "Wishlist.h"
#include "Profiles.h"
#include "SHA512.h"

//ENUMS
enum PremiumStatus { OK = -1, LAATSTE_DAG, OVERTIJD };
enum Status{LOGIN = 1, MENU, BERICHTEN, PROFIEL, myPROFIEL, MATCHES, INSTELLINGEN, WISHLIST};
enum Settings { OVERALL = 1, BASICS, INTERESTS, EXTRAS, HOBBIES, PASSWOORD, SEC_QUEST, UPGRADE};
//Functies
const string currentDate();													 //TEST OK
int datumvergelijking(string begindatum, string vandaag);					//TEST OK

//string random_string();													//TEST OK
//int rdn(string);

//Openbare waarden
static bool AppRun = true;
static string gekozenGebruiker;
static string current_loggedIN_Username;