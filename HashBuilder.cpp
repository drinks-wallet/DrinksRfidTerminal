/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>
#include <SipHash_2_4.h>

#include "Configuration.h"
#include "HashBuilder.h"

HashBuilder::HashBuilder()
{
	unsigned char key[16] = PRIVATE_KEY;
	sipHash.initFromRAM(key);
}

char* HashBuilder::getHash()
{
	sipHash.finish();

	for (int i = 0; i < 8; i++)
		sprintf(hash + 2 * i, "%02X", sipHash.result[i]);

	hash[16] = 0;
	return hash;
}

void HashBuilder::print(char* source)
{
	while (*source)
	{
		sipHash.updateHash((byte) *source);
		source++;
	}
}