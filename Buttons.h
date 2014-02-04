/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _BUTTONS_H
#define _BUTTONS_H

extern bool isLeftButtonPressed, isRightButtonPressed;

class Buttons
{
public:
  
    void begin();

    bool rightPressed()
    {
        if (!isRightButtonPressed) return false;
        delay(100);
        isRightButtonPressed = false;
        return true;
    }

    bool leftPressed()
    {
        if (!isLeftButtonPressed) return false;
        delay(100);
        isLeftButtonPressed = false;
        return true;
    }

private:
};

#endif
