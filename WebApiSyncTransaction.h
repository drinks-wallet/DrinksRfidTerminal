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

	WebApiSyncTransaction(HttpClient& http)
		: http(http)
	{

	}

	bool perform()
	{
		return send() && parse() && validate();
	}

	void getCatalog(Catalog&);
	unsigned long getTime() { return strtoul(time, 0, 10); }

private:

	bool send();
	bool parse();
	bool validate();

	HttpClient& http;
	char buffer[150];	
	char* time;
	char* header;
	char* products[5];
	char* hash;
};

#endif