#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.h"
#include "Pins.h"

#define SCREEN_COLUMNS     20
#define SELECTION_MAX_LENGTH  (SCREEN_COLUMNS-2)

static LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

void Display::begin()
{
  lcd.begin(SCREEN_COLUMNS, 2);
  delay(100);
}

void Display::setHeader(char* s)
{
  lcd.setCursor(0, 0);
  lcd.print(s);
}

void Display::setSelection(char* s)
{  
  int length = strnlen(s, SELECTION_MAX_LENGTH);
  int leftPadding = (SELECTION_MAX_LENGTH - length) / 2;
  int rightPadding = SELECTION_MAX_LENGTH - length - leftPadding;
  
  lcd.setCursor(0, 1);
  
  lcd.print('<');
  
  for(int i=0 ; i<leftPadding ; i++)
    lcd.print(' ');

  lcd.print(s);
  
  for(int i=0 ; i<rightPadding ; i++)
    lcd.print(' ');
    
  lcd.print('>');
}
