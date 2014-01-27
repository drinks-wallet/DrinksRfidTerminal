/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "HashBuilder.h"
#include "WebApiBuyRequest.h"

void WebApiBuyRequest::computeHash(char* buffer)
{
	HashBuilder hashBuilder;

	hashBuilder.print(badge);
	hashBuilder.print(product);
	hashBuilder.print(time);

	hashBuilder.getResult(buffer);
}

void WebApiBuyRequest::getContent(char* buffer, int size)
{
	char hash[17];

	computeHash(hash);

	snprintf(buffer, size, "{Badge=\"%s\",Hash=\"%s\",Product=%s,Time=%s}", badge, hash, product, time);
}