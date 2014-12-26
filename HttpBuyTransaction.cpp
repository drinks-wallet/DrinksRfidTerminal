/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>
#include <ArduinoJson.h>

#include "Configuration.h"
#include "HashBuilder.h"
#include "HttpBuyTransaction.h"

bool HttpBuyTransaction::send(char* badge, int product, unsigned long time)
{
    char productString[2];
    char timeString[11];
    
    snprintf(productString, sizeof(productString), "%d", product);
    snprintf(timeString, sizeof(timeString), "%lu", time);

    HashBuilder hashBuilder;
    hashBuilder.print(badge);
    hashBuilder.print(productString);
    hashBuilder.print(timeString);
    
    StaticJsonBuffer<JSON_OBJECT_SIZE(4)> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["Badge"] = badge;
    json["Hash"] = hashBuilder.getHash();
    json["Product"] = productString;
    json["Time"] = timeString;
    json.printTo(buffer, sizeof(buffer));

    return http.query("POST " API_PATH "/buy", buffer, sizeof(buffer));
}

bool HttpBuyTransaction::parse()
{
    StaticJsonBuffer<JSON_OBJECT_SIZE(4)+JSON_ARRAY_SIZE(2)> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(buffer);
    if (!root.success()) return false;

    melody = root["Melody"];
    if (melody == NULL) return false;

    JsonArray& messageArray = root["Message"];
    if (!messageArray.success()) return false;
    
    messages[0] = messageArray[0];
    messages[1] = messageArray[1];

    time = root["Time"];
    if (time == NULL) return false;

    hash = root["Hash"];
    if (hash == NULL) return false;

    return true;
}

bool HttpBuyTransaction::validate()
{
    HashBuilder hashBuilder;
    hashBuilder.print(melody);
    hashBuilder.print(messages[0]);
    hashBuilder.print(messages[1]);
    hashBuilder.print(time);

    return strcasecmp(hash, hashBuilder.getHash()) == 0;
}
