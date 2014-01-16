#include <Arduino.h>
#include <JsonParser.h>
#include <SipHash_2_4.h>

#include "Clock.h"
#include "HttpClient.h"
#include "WebApi.h"
#include "WebApiSyncResponse.h"
unsigned char key[16] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

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

static void computeHash(char* source, char* destination)
{
	sipHash.initFromPROGMEM(key);
	for (int i = 0; source[i]; i++)
		sipHash.updateHash((byte) source[i]);
	sipHash.finish();

	for (int i = 0; i < 8; i++)
	{
		sprintf(destination + 2 * i, "%02X", sipHash.result[i]);
	}
	destination[16] = 0;
}

bool WebApi::buy(char* badge, int product)
{
	if (!http.connect()) return false;

	int i, j;
	char buffer[128];
	char* hash = buffer + sprintf(buffer, "badge=%s&product=%d&time=%lu&hash=", badge, product, clock.getTime());

	computeHash(buffer, hash);

	//Serial.println(buffer);

	http.performPostRequest("/drinks/api/buy", buffer);

	http.readln(buffer, 64);

	Serial.println(buffer);

	http.disconnect();

	return true;
}




