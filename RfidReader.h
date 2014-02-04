/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _RFIDREADER_H
#define _RFIDREADER_H

#include <SoftwareSerial.h>

#include "Pins.h"

class RfidReader
{
public:

	RfidReader() : rfid(PIN_RFID, PIN_RFID)
	{
	}

	void begin()
	{
		rfid.begin(9600);
	}

	char* tryRead();

private:

	byte parseHexNibble(char);
	byte parseHexByte(char*);
	byte computeCheckSum(char*);

	SoftwareSerial rfid;
	char buffer[14];
};

#endif
