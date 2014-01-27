/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _DISPLAY_H
#define _DISPLAY_H

class Display
{
public:

	void begin();
	void setText(int, char*);
	void setSelection(int, char*);
};

#endif
