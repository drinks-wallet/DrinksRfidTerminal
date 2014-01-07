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
