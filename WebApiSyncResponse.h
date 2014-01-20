#include "Catalog.h"
#include <stdlib.h>

class WebApiSyncResponse
{
public:

	WebApiSyncResponse(char* json);

	bool isValid();

	void getCatalog(Catalog&);
	unsigned long getTime() { return strtoul(time,0,10); }

private:

	bool validateHash();

	char* time;
	char* header;
	char* products[5];
	char* hash;
};
