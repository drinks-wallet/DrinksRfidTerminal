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

bool isLeftButtonPressed, isRightButtonPressed;

static void onLeftPressed()
{
	isLeftButtonPressed = true;
}

static void onRightPressed()
{
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


