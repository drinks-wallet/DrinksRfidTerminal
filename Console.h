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
