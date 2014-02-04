/*
 * "Drinks" RFID Terminal
 * Buy sodas with your company badge!
 *
 * Benoit Blanchon 2014 - MIT License
 * https://github.com/bblanchon/DrinksRfidTerminal
 */

#include <Arduino.h>

#include "Configuration.h"
#include "Buttons.h"
#include "Pins.h"

#define DEBOUNCE_PERIOD		200

static int selectedIndex = 0;
static int count = 1;
static unsigned long keyPressTime = 0;

static void move(int inc)
{
	unsigned long now = millis();

	if (keyPressTime + DEBOUNCE_PERIOD < now)
	{
		keyPressTime = now;
		selectedIndex = (selectedIndex + count + inc) % count;
	}
}

static void decrement()
{
	move(-1);
}

static void increment()
{
	move(+1);
}

void Buttons::begin()
{
	pinMode(PIN_BTN_LEFT, INPUT);
	digitalWrite(PIN_BTN_LEFT, HIGH);
	pinMode(PIN_BTN_RIGHT, INPUT);
	digitalWrite(PIN_BTN_RIGHT, HIGH);
	attachInterrupt(0, increment, FALLING);
	attachInterrupt(1, decrement, FALLING);
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


