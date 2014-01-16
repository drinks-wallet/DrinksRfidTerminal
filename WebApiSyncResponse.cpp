#include <Arduino.h>
#include <JsonParser.h>

#include "WebApiSyncResponse.h"

WebApiSyncResponse::WebApiSyncResponse(char* json)
{
	JsonParser<13> parser;

	Serial.println(json);
	JsonHashTable root = parser.parseHashTable(json);

	if (!root.success())
	{
		Serial.println("Sync: invalid JSON");
		header = NULL;
		time = NULL;
		hash = NULL;
		return;
	}

	header = root.getString("Header");

	if (header == NULL)
	{
		Serial.println("Sync: 'Header' not found");
	}

	JsonArray productsArray = root.getArray("Products");

	if (productsArray.success())
	{
		int count = productsArray.getLength();
		for (int i = 0; i < count; i++)
		{
			products[i] = productsArray.getString(i);
		}
		products[count] = NULL;
	}
	else
	{
		Serial.println("Sync: 'Products' not found");
		products[0] = NULL;
	}

	time = root.getString("Time");

	if (time == NULL)
	{
		Serial.println("Sync: 'Time' not found");
	}

	hash = root.getString("Hash");

	if (hash == NULL)
	{
		Serial.println("Sync: 'Hash' not found");
	}
}

bool WebApiSyncResponse::isValid()
{
	return header != NULL && products[0] != NULL && time != 0 && validateHash();
}

bool WebApiSyncResponse::validateHash()
{
	return true;
}

void WebApiSyncResponse::getCatalog(Catalog& catalog)
{
	Serial.println(header);
	catalog.setHeader(header);
	
	int i;
	for (i = 0; i < 4; i++)
	{
		if (products[i] == NULL) break;
		catalog.setProduct(i, products[i]);
		Serial.println(products[i]);
	}
	catalog.setProductCount(i);
}