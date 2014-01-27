/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _RFIDREADER_H
#define _RFIDREADER_H

class RfidReader
{
public:

	void begin();
	char* tryRead();
};

#endif
