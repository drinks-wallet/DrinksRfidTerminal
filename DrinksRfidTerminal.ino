#include <aJSON.h>
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
#include "RfidReader.h"
#include "WebApi.h"

#define CLOCK_SYNC_PERIOD  (1*60*1000UL)
#define CATALOG_SYNC_PERIOD  (1*60*1000UL)

static Buttons buttons;
static Catalog catalog;
static Console console;
static Display display;
static RfidReader rfid;
static WebApi api;


void setup() 
{  
  display.begin();  
  console.begin();

  console.enter(display);

  display.setText(0, "Initializing...");    
  display.setText(1, "");    

  api.begin();
  buttons.begin();
  rfid.begin();

  display.setText(0, "Connecting...");    
}

void loop() 
{  
  api.sync(catalog);
  
  buttons.setCount(catalog.getProductCount());
  display.setText(0, catalog.getHeader());
  
  int product = buttons.getSelectedIndex();

  display.setSelection(1, catalog.getProduct(product)); 

  char* badge = rfid.tryRead();

  if( badge )
  {
    Serial.println(badge);     
    api.buy(badge, product);
  }

  delay(100);
}
