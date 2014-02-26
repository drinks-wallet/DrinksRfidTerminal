/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _CLOCK_H
#define _CLOCK_H

class Clock
{
public:

    void setUnixTime(unsigned long time);
    unsigned long getUnixTime();

private:

    unsigned long zero;
};

#endif
