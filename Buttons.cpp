#include <Arduino.h>

#include "Buttons.h"
#include "Pins.h"

static int selectedIndex = 0;
static int count = 1;

static void decrement()
{  
  selectedIndex = (selectedIndex-1) % count;  
}

static void increment()
{
  selectedIndex = (selectedIndex+1) % count;
}

void Buttons::begin()
{
  pinMode(PIN_BTN_LEFT, INPUT);
  digitalWrite(PIN_BTN_LEFT, HIGH);
  pinMode(PIN_BTN_RIGHT, INPUT); 
  digitalWrite(PIN_BTN_RIGHT, HIGH); 
  attachInterrupt(0, decrement, RISING);
  attachInterrupt(1, increment, RISING);
}

int Buttons::getSelectedIndex()
{
  return selectedIndex;
}

void Buttons::setCount(int n)
{  
 count = n; 
 selectedIndex %= n;
}
