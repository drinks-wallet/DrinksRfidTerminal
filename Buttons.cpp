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

byte Buttons::pressedButton = Buttons::NONE;
unsigned long Buttons::blindUntil = 0;

bool Buttons::checkBounce()
{
    unsigned long now = millis();
    if (now < blindUntil) return false;
    blindUntil = now + DEBOUNCE_PERIOD;
    return true;
}

void Buttons::onLeftPressed()
{
    if (checkBounce())
        pressedButton = LEFT;
}

void Buttons::onRightPressed()
{
    if (checkBounce())
        pressedButton = RIGHT;
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


