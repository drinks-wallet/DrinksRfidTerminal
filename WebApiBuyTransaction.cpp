/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>

#include "WebApiBuyRequest.h"
#include "WebApiBuyResponse.h"
#include "WebApiBuyTransaction.h"

WebApiBuyTransaction::WebApiBuyTransaction(char* badge, int product, unsigned long time)
{
	WebApiBuyRequest request(badge, product, time);
	request.getContent(buffer, sizeof(buffer));
}

bool WebApiBuyTransaction::perform(HttpClient& http)
{
	if (!http.perform("POST /drinks/api/buy", buffer, sizeof(buffer)))
		return false;

	WebApiBuyResponse response(buffer);

	if (!response.isValid())
	{
		Serial.println("Invalid response");
		return false;
	}

	melody = response.getMelody();
	messages[0] = response.getMessage(0);
	messages[1] = response.getMessage(1);

	return true;
}