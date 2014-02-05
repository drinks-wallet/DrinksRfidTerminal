/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "Pins.h"

class Display
{
public:

    void begin();
    void setText(int, const char*);
    void setSelection(int, const char*);
    void setError();
    void setBusy();
    
    void setBacklight(byte intensity)
    {
        analogWrite(PIN_LCD_LIGHT, intensity);
    }
};

#endif
