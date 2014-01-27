/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include "Catalog.h"
#include <stdlib.h>

class WebApiSyncResponse
{
public:

	WebApiSyncResponse(char* json);

	bool isValid();

	void getCatalog(Catalog&);
	unsigned long getTime() { return strtoul(time, 0, 10); }

private:

	bool validateHash();

	char* time;
	char* header;
	char* products[5];
	char* hash;
};
