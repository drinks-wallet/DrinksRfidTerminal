#include <Arduino.h>
#include <JsonParser.h>
#include <string.h>

#include "HashBuilder.h"
#include "WebApiBuyResponse.h"

WebApiBuyResponse::WebApiBuyResponse(char* json)
{
	messages[0] = NULL;
	messages[1] = NULL;
	melody = NULL;
	time = NULL;
	hash = NULL;

	JsonParser<13> parser;

	JsonHashTable root = parser.parseHashTable(json);

	if (!root.success())
	{
		//Serial.println("Sync: invalid JSON");
		return;
	}

	melody = root.getString("Melody");

	if (melody == NULL)
	{
		//Serial.println("Sync: 'Melody' not found");
	}

	JsonArray messageArray = root.getArray("Message");

	if (messageArray.success())
	{
		messages[0] = messageArray.getString(0);
		messages[1] = messageArray.getString(1);
	}
	else
	{
		//Serial.println("Sync: 'Message' not found");
	}

	time = root.getString("Time");

	if (time == NULL)
	{
		//Serial.println("Sync: 'Time' not found");
	}

	hash = root.getString("Hash");

	if (hash == NULL)
	{
		//Serial.println("Sync: 'Hash' not found");
	}
}

bool WebApiBuyResponse::isValid()
{
	return melody != NULL && messages[0] != NULL && messages[1] != NULL && time != NULL && validateHash();
}

bool WebApiBuyResponse::validateHash()
{
	HashBuilder hashBuilder;
	
	hashBuilder.print(melody);
	hashBuilder.print(messages[0]);
	hashBuilder.print(messages[1]);
	hashBuilder.print(time);

	char hashString[17];

	hashBuilder.getResult(hashString);

	//Serial.println(hashString);

	return strcasecmp(hash, hashString) == 0;
}