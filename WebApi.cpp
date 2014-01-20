#include <Arduino.h>
#include <JsonParser.h>

#include "Clock.h"
#include "HttpClient.h"
#include "WebApi.h"
#include "WebApiBuyRequest.h"
#include "WebApiSyncResponse.h"

void WebApi::begin()
{
	http.begin();
	lastSyncTime = 0;
}

bool WebApi::sync(Catalog& catalog)
{
	// already sync'ed
	if (lastSyncTime != 0 && millis() < lastSyncTime + SYNC_PERIOD)
		return true;

	Serial.println("Sync...");

	char buffer[160];

	if (!http.performGetRequest("/drinks/api/sync", buffer, sizeof(buffer))) return false;

	WebApiSyncResponse response(buffer);

	if (!response.isValid())
		return false;

	response.getCatalog(catalog);
	clock.setTime(response.getTime());

	lastSyncTime = millis();
	
	return true;
}

bool WebApi::buy(char* badge, int product)
{
	char buffer[128];

	WebApiBuyRequest request(badge, product, clock.getTime());
	request.getContent(buffer, sizeof(buffer));
	
	Serial.println(buffer);

	http.performPostRequest("/drinks/api/buy", buffer, sizeof(buffer));

	Serial.println(buffer);

	return true;
}




