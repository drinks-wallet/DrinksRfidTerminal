/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _WEBAPISYNCTRANSACTION_H
#define _WEBAPISYNCTRANSACTION_H

#include "Catalog.h"
#include "HttpClient.h"

class WebApiSyncTransaction
{
public:

	bool perform(HttpClient& http)
	{
		return send(http) && parse() && validateHash();
	}

	void getCatalog(Catalog&);
	unsigned long getTime() { return strtoul(time, 0, 10); }

private:

	bool send(HttpClient&);
	bool parse();
	bool validateHash();

	char buffer[150];	
	char* time;
	char* header;
	char* products[5];
	char* hash;
};

#endif