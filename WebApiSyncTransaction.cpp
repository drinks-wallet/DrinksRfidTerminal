/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "WebApiSyncTransaction.h"

bool WebApiSyncTransaction::perform(HttpClient& http)
{
	buffer[0] = 0;

	if (!http.perform("GET /drinks/api/sync", buffer, sizeof(buffer)))
		return false;

	if (!response.parse(buffer))
	{
		Serial.println("Invalid response");
		return false;
	}

	return true;
}