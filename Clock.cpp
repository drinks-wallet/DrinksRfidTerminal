/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "Clock.h"

void Clock::setUnixTime(unsigned long time)
{
    zero = time - millis() / 1000;
}

unsigned long Clock::getUnixTime()
{
    return zero + millis() / 1000;
}
