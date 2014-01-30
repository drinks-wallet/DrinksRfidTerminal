/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _HTTPBUYTRANSACTION_H
#define _HTTPBUYTRANSACTION_H

#include "HttpClient.h"

class HttpBuyTransaction
{
public:

	HttpBuyTransaction(HttpClient& http)
		:http(http)
	{
	}

	bool perform(char* badge, int product, unsigned long time)
	{
		return send(badge, product, time) && parse() && validate();
	}

	char* getMelody() { return melody; }
	char* getMessage(int i) { return messages[i]; }

private:

	bool send(char*, int, unsigned long);
	bool parse();
	bool validate();

	HttpClient& http;
	char buffer[150];
	char* hash;
	char* messages[2];
	char* melody;
	char* time;
};

#endif