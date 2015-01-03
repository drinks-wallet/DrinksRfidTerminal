/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _HASHBUILDER_H
#define _HASHBUILDER_H

class HashBuilder : public Print
{
public:

    HashBuilder();
    const char* getHash();

    virtual size_t write(uint8_t c);

private:
    char hash[17];
};

#endif