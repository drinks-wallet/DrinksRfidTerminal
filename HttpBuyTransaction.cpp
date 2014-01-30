/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>
#include <JsonParser.h>

#include "HashBuilder.h"
#include "HttpBuyTransaction.h"

bool HttpBuyTransaction::send(char* badge, int product, unsigned long time)
{
	char productString[2];
	char timeString[11];
	char hash[17];

	sprintf(productString, "%d", product);
	sprintf(timeString, "%lu", time);

	HashBuilder hashBuilder;
	hashBuilder.print(badge);
	hashBuilder.print(productString);
	hashBuilder.print(timeString);
	hashBuilder.getResult(hash);

	snprintf(buffer, sizeof(buffer), "{Badge:\"%s\",Hash:\"%s\",Product:%s,Time:%s}", badge, hash, productString, timeString);

	return http.perform("POST /drinks/api/buy", buffer, sizeof(buffer));
}

bool HttpBuyTransaction::parse()
{
	JsonParser<13> parser;

	JsonHashTable root = parser.parseHashTable(buffer);
	if (!root.success()) return false;

	melody = root.getString("Melody");
	if (melody == NULL) return false;

	JsonArray messageArray = root.getArray("Message");
	if (!messageArray.success()) return false;
	
	messages[0] = messageArray.getString(0);
	messages[1] = messageArray.getString(1);

	time = root.getString("Time");
	if (time == NULL) return false;

	hash = root.getString("Hash");
	if (hash == NULL) return false;

	return true;
}

bool HttpBuyTransaction::validate()
{
	char computedHash[17];

	HashBuilder hashBuilder;
	hashBuilder.print(melody);
	hashBuilder.print(messages[0]);
	hashBuilder.print(messages[1]);
	hashBuilder.print(time);
	hashBuilder.getResult(computedHash);

	return strcasecmp(hash, computedHash) == 0;
}