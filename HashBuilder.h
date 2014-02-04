/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _HASHBUILDER_H
#define _HASHBUILDER_H

class HashBuilder
{
public:

	HashBuilder();
	void print(char*);
	char* getHash();

private:
	char hash[17];
};

#endif