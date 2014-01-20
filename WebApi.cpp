#include <Arduino.h>
#include <JsonParser.h>

#include "Clock.h"
#include "HttpClient.h"
#include "WebApi.h"
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
	if (!http.connect()) return false;

	int i, j;
	char buffer[128];
	char* hash = buffer + sprintf(buffer, "badge=%s&product=%d&time=%lu&hash=", badge, product, clock.getTime());

	//computeHash(buffer, hash);

	//Serial.println(buffer);

	http.performPostRequest("/drinks/api/buy", buffer);

	http.readln(buffer, 64);

	Serial.println(buffer);

	http.disconnect();

	return true;
}




