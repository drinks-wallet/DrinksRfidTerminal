/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SipHash_2_4.h>

#include "Configuration.h"
#include "HashBuilder.h"

using namespace ArduinoJson::Internals;

HashBuilder::HashBuilder()
{
    unsigned char key[16] = PRIVATE_KEY;
    sipHash.initFromRAM(key);
}

const char* HashBuilder::getHash()
{
    sipHash.finish();

    StringBuilder sb(hash, sizeof(hash));

    for (int i = 0; i < 8; i++) {
        byte c = sipHash.result[i];
        if (c < 16) sb.write('0');
        sb.print(c, HEX);
    }

    return hash;
}

size_t HashBuilder::write(uint8_t c)
{
    sipHash.updateHash(c);
    return 1;
}