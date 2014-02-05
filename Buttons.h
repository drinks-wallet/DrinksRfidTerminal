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
        if (pressedButton != RIGHT) return false;
        pressedButton = NONE;
        return true;
    }

    bool leftPressed()
    {
        if (pressedButton != LEFT) return false;
        pressedButton = NONE;
        return true;
    }

private:

    static bool checkBounce();
    static void onLeftPressed();
    static void onRightPressed();

    static const unsigned long DEBOUNCE_PERIOD = 100;
    static const byte NONE = 0;
    static const byte LEFT = 1;
    static const byte RIGHT = 2;

    static byte pressedButton;
    static unsigned long blindUntil;
};

#endif
