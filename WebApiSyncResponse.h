/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _WEBAPISYNCRESPONSE_H
#define _WEBAPISYNCRESPONSE_H

#include "Catalog.h"
#include <stdlib.h>

class WebApiSyncResponse
{
public:

	bool parse(char* json);	

	void getCatalog(Catalog&);
	unsigned long getTime() { return strtoul(time, 0, 10); }

private:

	bool validateHash();

	char* time;
	char* header;
	char* products[5];
	char* hash;
};

#endif