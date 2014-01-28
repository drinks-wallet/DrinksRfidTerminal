/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _WEBAPISYNCTRANSACTION_H
#define _WEBAPISYNCTRANSACTION_H

#include "HttpClient.h"
#include "WebApiSyncResponse.h"

class WebApiSyncTransaction
{
public:

	bool perform(HttpClient&);

	void getCatalog(Catalog& c) { response.getCatalog(c); }
	unsigned long getTime() { return response.getTime(); }

private:

	char buffer[150];
	WebApiSyncResponse response;
};

#endif