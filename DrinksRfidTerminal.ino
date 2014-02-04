/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
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
#define IDLE_PERIOD 10000L

static Buttons buttons;
static Catalog catalog;
static Clock clock;
static Display display;
static HttpClient http;
static RfidReader rfid;
static Sound sound;

int selectedProduct = 0;
unsigned long lastSyncTime = 0;
unsigned long lastEventTime = 0;

void setup()
{
	Serial.begin(9600);

	display.begin();

	display.setText(0, "Initializing...");
	display.setText(1, "");
	display.setBacklight(255);

	sound.begin();
	http.begin();
	buttons.begin();
	rfid.begin();

	display.setText(0, "Connecting...");

	while (!sync())
	{
		delay(5000);
	}
}

void loop()
{
	unsigned long now = millis();

	showSelection();

	if (buttons.leftPressed())
	{
		moveSelectedProduct(-1);
	}
	else if (buttons.rightPressed())
	{
		moveSelectedProduct(+1);
	}

	if (now > lastEventTime + IDLE_PERIOD)
	{
		if (selectedProduct != 0)
		{
			selectedProduct = 0;
			showSelection();
		}

		if (now > lastSyncTime + SYNC_PERIOD)
		{
			if (!sync())
			{
				delay(5000);
			}
			return;
		}
	}
	else
	{
		unsigned long remainingTime = lastEventTime + IDLE_PERIOD - now;

		if (remainingTime < 1024)
		{
			display.setBacklight(remainingTime / 4);
		}
		else
		{
			display.setBacklight(255);
		}
	}

	char* badge = rfid.tryRead();

	if (badge)
	{
		buy(badge, selectedProduct);

		delay(2000);

		// ignore all waiting badge to avoid unintended double buy
		while (rfid.tryRead());
	}	
}

void moveSelectedProduct(int increment)
{
	lastEventTime = millis();
	selectedProduct = (selectedProduct + increment + catalog.getProductCount()) % catalog.getProductCount();
	showSelection();
}

void showSelection()
{
	display.setText(0, catalog.getHeader());
	display.setSelection(1, catalog.getProduct(selectedProduct));
}

bool buy(char* badge, int product)
{
	lastEventTime = millis();

	display.setBacklight(255);
	display.setBusy();

	HttpBuyTransaction buyTransaction(http);

	if (!buyTransaction.perform(badge, product, clock.getTime()))
	{
		display.setError();
		return false;
	}

	display.setText(0, buyTransaction.getMessage(0));
	display.setText(1, buyTransaction.getMessage(1));
	sound.play(buyTransaction.getMelody());

	return true;
}

bool sync()
{
	display.setBusy();

	HttpSyncTransaction syncTransaction(http);

	if (!syncTransaction.perform())
	{
		display.setError();
		return false;
	}
	
	syncTransaction.getCatalog(catalog);
	clock.setTime(syncTransaction.getTime());

	lastSyncTime = millis();

	return true;
}
