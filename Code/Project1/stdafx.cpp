#include "stdafx.h"


int datumvergelijking(string begindatum, string vandaag)
{
	if (atoi(begindatum.substr(0, 4).c_str()) <= atoi(vandaag.substr(0, 4).c_str())
		&& atoi(begindatum.substr(5, 2).c_str()) <= atoi(vandaag.substr(5, 2).c_str())
		&& atoi(begindatum.substr(8, 2).c_str()) <= atoi(vandaag.substr(8, 2).c_str()))
	{
		if (atoi(begindatum.substr(0, 4).c_str()) == atoi(vandaag.substr(0, 4).c_str())
			&& atoi(begindatum.substr(5, 2).c_str()) == atoi(vandaag.substr(5, 2).c_str())
			&& atoi(begindatum.substr(8, 2).c_str()) == atoi(vandaag.substr(8, 2).c_str())) return LAATSTE_DAG; return OK;

	} return OVERTIJD;
}




//string random_string() {
//	//salt genereren, stukje code die random alphanum string genereert. 
//	//Credits: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
//	string salt = "";
//	for (int i = 0; i < 32; i++)
//	{
//
//		switch (rand() % 3)
//		{
//		case 0:
//			salt += ('0' + rand() % 10);
//			break;
//		case 1:
//			salt += ('A' + rand() % 26);
//			break;
//		case 2:
//			salt += ('a' + rand() % 26);
//			break;
//		}
//	}
//	return salt;
//}




//const string currentDate() {
//	//credits: http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//	//Ik heb deze aangepast.
//	time_t     now = time(0);
//	struct tm  tstruct;
//	char       buf[80];
//	tstruct = *localtime(&now);
//	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
//
//	return buf;
//}
//
//
//
//int rdn(string datum) {
//	//Datum omzetten in een int zodat aantal dagen berekenen tussen 2 datums mogelijk is.
//	//Ik heb de methode van StackOverflow getransformeerd zodat het met een string werkt ipv 3 integers als parameters.
//	//Inspiratie: http://stackoverflow.com
//	int y = atoi(datum.substr(0, 4).c_str());
//	int m = atoi(datum.substr(5, 2).c_str());
//	int d = atoi(datum.substr(8, 2).c_str());
//
//	if (m < 3)
//		y--, m += 12;
//	return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
//}
//

