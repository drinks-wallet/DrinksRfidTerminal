/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Ethernet.h>
#include <SPI.h>
#include <JsonParser.h>
#include <LiquidCrystal.h>
#include <SipHash_2_4.h>
#include <SoftwareSerial.h>

#include "Buttons.h"
#include "Catalog.h"
#include "Clock.h"
#include "Console.h"
#include "Display.h"
#include "HttpClient.h"
#include "RfidReader.h"
#include "Sound.h"
#include "WebApiSyncResponse.h"
#include "WebApiBuyTransaction.h"

static Buttons buttons;
static Catalog catalog;
static Clock clock;
static Console console;
static Display display;
static HttpClient http;
static RfidReader rfid;
static Sound sound;

unsigned long lastSyncTime = 0;

void setup()
{
	display.begin();
	console.begin();

	//console.enter(display);

	display.setText(0, "Initializing...");
	display.setText(1, "");

	sound.begin();
	http.begin();
	buttons.begin();
	rfid.begin();

	display.setText(0, "Connecting...");
}

void displayError()
{
	display.setText(0, "* * * ERROR * * *");
	display.setText(1, "Connection failed");
	delay(5000);
}

void loop()
{
	if (!sync())
	{
		displayError();
	}

	buttons.setCount(catalog.getProductCount());
	display.setText(0, catalog.getHeader());

	int product = buttons.getSelectedIndex();

	display.setSelection(1, catalog.getProduct(product));

	char* badge = rfid.tryRead();

	if (badge)
	{
		if (!buy(badge, product))
		{
			displayError();
		}
	}

	delay(100);
}

bool buy(char* badge, int product)
{
	WebApiBuyTransaction buyTransaction(badge, product, clock.getTime());

	if (!buyTransaction.perform(http))
		return false;

	display.setText(0, buyTransaction.getMessage(0));
	display.setText(1, buyTransaction.getMessage(1));
	sound.play(buyTransaction.getMelody());
	delay(3000);

	return true;
}

bool sync()
{
	// already sync'ed
	if (lastSyncTime != 0 && millis() < lastSyncTime + SYNC_PERIOD)
		return true;

	char buffer[160];

	if (!http.performGetRequest("/drinks/api/sync", buffer, sizeof(buffer)))
		return false;

	WebApiSyncResponse response(buffer);

	if (!response.isValid())
	{
		Serial.println("Invalid response");
		return false;
	}

	response.getCatalog(catalog);
	clock.setTime(response.getTime());

	lastSyncTime = millis();

	return true;
}
