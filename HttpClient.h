/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

#include <Ethernet.h>

class HttpClient
{
public:
    void begin();

    bool perform(const char* path, char* content, int maxContentSize);

private:

    void readln(char*, int);

    IPAddress serverIp;
    EthernetClient client;
};

#endif
