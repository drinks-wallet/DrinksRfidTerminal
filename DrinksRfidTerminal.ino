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
#include "Display.h"
#include "HttpBuyTransaction.h"
#include "HttpClient.h"
#include "HttpSyncTransaction.h"
#include "RfidReader.h"
#include "Sound.h"

#define SYNC_PERIOD	60000L

static Buttons buttons;
static Catalog catalog;
static Clock clock;
static Display display;
static HttpClient http;
static RfidReader rfid;
static Sound sound;

unsigned long lastSyncTime = 0;

void setup()
{
	Serial.begin(9600);

	display.begin();

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
	HttpBuyTransaction buyTransaction(http);

	if (!buyTransaction.perform(badge, product, clock.getTime()))
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

	HttpSyncTransaction syncTransaction(http);

	if (!syncTransaction.perform())
		return false;
	
	syncTransaction.getCatalog(catalog);
	clock.setTime(syncTransaction.getTime());

	lastSyncTime = millis();

	return true;
}
