#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Display.h"
#include "Pins.h"

static LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

void Display::begin()
{
  lcd.begin(20, 2);
  delay(100);
}

void Display::setHeader(char* s)
{
  lcd.setCursor(0, 0);
  lcd.print(s);
}

void Display::setSelection(char* s)
{
  lcd.setCursor(0, 1);
  lcd.print('<');
  lcd.setCursor(2, 1);
  lcd.print(s);
  lcd.setCursor(19, 1);
  lcd.print('>');
}
