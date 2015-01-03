/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
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

    bool perform(char* badge, int product, long time)
    {
        return send(badge, product, time) && parse() && validate();
    }

    const char* getMelody() { return melody; }
    const char* getMessage(int i) { return messages[i]; }

private:

    bool send(char*, int, long);
    bool parse();
    bool validate();

    HttpClient& http;
    char buffer[150];
    const char* hash;
    const char* messages[2];
    const char* melody;
    const char* time;
};

#endif