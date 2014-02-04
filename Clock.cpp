/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "Clock.h"

void Clock::setTime(unsigned long time)
{
	zero = time - millis();
}

unsigned long Clock::getTime()
{
	return zero + millis();
}
