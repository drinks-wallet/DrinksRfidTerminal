#include <Arduino.h>

#include "Console.h"

#define WAIT_TIME        2000
#define COMMAND_MAX_SIZE   16

void Console::begin()
{
  Serial.begin(9600);
}

void Console::enter(Display& display)
{
  display.setText(0, "Serial console 9600");
  display.setText(1, "Press any key");

  unsigned long start =  millis();

  while( ! Serial.available() )
  {
    if( millis() > start + WAIT_TIME ) return;
  }

  display.setText(1, "Connected !");

  showHelp();

  while (true)
  {    
    char s[COMMAND_MAX_SIZE];
    
    readCommand(s);

    if (!strcmp(s,"exit"))
    {
      Serial.println("Exit console console");
      break;
    }

    if (!strcmp(s,"help"))
    {
      showHelp();
      continue;
    }
    
    Serial.print("Unknown command: ");
    Serial.println(s);
  }    
}

void Console::showHelp()
{
  Serial.println("Commands:");
  Serial.println(" - help : show this help");
  Serial.println(" - exit : close console, go back to normal");
}

void Console::readCommand(char* s)
{
  int i = 0;

  Serial.print("> ");

  while (true)
  {   
    char c = Serial.read();
    
    if( c == '\n' )
    {
      s[i] = 0 ;
      break;
    }

    if( c != -1 && c != '\r' && i<COMMAND_MAX_SIZE )
    {
      s[i] = c;
      i++;
    }  
  }

  Serial.println(s);
}

