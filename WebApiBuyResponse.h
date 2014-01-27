/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _WEBAPIBUYRESPONSE_H
#define _WEBAPIBUYRESPONSE_H

class WebApiBuyResponse
{
public:

	WebApiBuyResponse(char* json);

	bool isValid();

	char* getMessage(int i) { return messages[i]; }
	char* getMelody() { return melody; }

private:

	bool validateHash();

	char* hash;
	char* messages[2];
	char* melody;
	char* time;
};

#endif