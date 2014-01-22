#ifndef _WEBAPIBUYTRANSACTION_H
#define _WEBAPIBUYTRANSACTION_H

#include "HttpClient.h"

class WebApiBuyTransaction
{
public:

	WebApiBuyTransaction(char* badge, int product, unsigned long time);
	bool perform(HttpClient&);

	char* getMelody() { return melody; }
	char* getMessage(int i) { return messages[i]; }

private:

	char buffer[150];
	char* melody;
	char* messages[2];
};

#endif