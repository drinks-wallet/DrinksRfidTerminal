/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "Pins.h"
#include "Sound.h"

void Sound::begin()
{
    pinMode(PIN_BUZZER, OUTPUT);
}

void Sound::play(char* melody)
{
    int frequencies [] = { 4186, 4699, 4699, 5274, 6271, 7040, 7902 };

    while (true)
    {
        byte note = *melody;

        if (note >= 'a' && note <= 'g')
            tone(PIN_BUZZER, frequencies[note - 'a']);

        if (note >= 'A' && note <= 'G')
            tone(PIN_BUZZER, frequencies[note - 'A'] * 2);

        melody++;
        if (*melody == 0) break;

        byte duration = *melody - '0';
        if (duration<0 || duration>9) break;

        duration = 1 << (duration - 1);

        delay(75 * duration);
        noTone(PIN_BUZZER);

        melody++;
        if (*melody == 0) break;

        delay(10);
    }
}