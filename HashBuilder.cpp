#include <Arduino.h>
#include <SipHash_2_4.h>

#include "HashBuilder.h"

static unsigned char key[16] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };


HashBuilder::HashBuilder()
{
	sipHash.initFromRAM(key);
}

void HashBuilder::getResult(char* destination)
{
	sipHash.finish();

	for (int i = 0; i < 8; i++)	
		sprintf(destination + 2 * i, "%02X", sipHash.result[i]);
	
	destination[16] = 0;
}

void HashBuilder::print(char* source)
{
	while (*source)
	{
		sipHash.updateHash((byte) *source);
		source++;
	}
}