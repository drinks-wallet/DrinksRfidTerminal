/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _BUTTONS_H
#define _BUTTONS_H

class Buttons
{
  public:
  
    void begin();
    int getSelectedIndex();
    void setCount(int);   
};

#endif
