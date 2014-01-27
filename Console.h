/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Display.h"

class Console
{
public:

	void begin();
	void enter(Display& display);

private:

	void readCommand(char*);
	void showHelp();
};

#endif
