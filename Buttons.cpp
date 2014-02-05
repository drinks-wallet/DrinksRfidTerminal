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

bool isLeftButtonPressed = false, isRightButtonPressed = false;
static unsigned long blindUntil = 0;

static bool checkBounce()
{
	unsigned long now = millis();
	if (now < blindUntil) return false;
	blindUntil = now + DEBOUNCE_PERIOD;
	return true;
}

static void onLeftPressed()
{
	if (checkBounce())
		isLeftButtonPressed = true;
}

static void onRightPressed()
{
	if (checkBounce())
		isRightButtonPressed = true;
}

void Buttons::begin()
{
	pinMode(PIN_BTN_LEFT, INPUT);
	digitalWrite(PIN_BTN_LEFT, HIGH);
	pinMode(PIN_BTN_RIGHT, INPUT);
	digitalWrite(PIN_BTN_RIGHT, HIGH);
	attachInterrupt(0, onRightPressed, FALLING);
	attachInterrupt(1, onLeftPressed, FALLING);
}


