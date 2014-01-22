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
	if (!http.performPostRequest("/drinks/api/buy", buffer, sizeof(buffer)))
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