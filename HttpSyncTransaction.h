/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _HTTPSYNCTRANSACTION_H
#define _HTTPSYNCTRANSACTION_H

#include "Catalog.h"
#include "HttpClient.h"

class HttpSyncTransaction
{
public:

    HttpSyncTransaction(HttpClient& http)
        : http(http)
    {

    }

    bool perform()
    {
        return send() && parse() && validate();
    }

    void getCatalog(Catalog&);
    
    unsigned long getTime() 
    { 
        // use strtol instead of strtoul to reduce code space
        return strtol(time, 0, 10); 
    }

private:

    bool send();
    bool parse();
    bool validate();

    HttpClient& http;
    char buffer[200];    
    const char* time;
    const char* header;
    const char* products[Catalog::MAX_PRODUCT_COUNT + 1];
    const char* hash;
};

#endif