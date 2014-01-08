#include <Ethernet.h>
#include <SPI.h>
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

#define CLOCK_SYNC_PERIOD  1*60*1000

static Buttons buttons;
static Catalog catalog;
static Clock clock;
static Console console;
static Display display;
static RfidReader rfid;
static WebApi api;

static unsigned long clockSyncTime = 0;

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

  Serial.println("CATALOG:");

  api.getCatalog(catalog);

  for( int i=0 ; i<catalog.getProductCount() ; i++ )
  {
    Serial.print("[");
    Serial.print(i);
    Serial.print("]");
    Serial.println(catalog.getProduct(i));    
  }

  buttons.setCount(catalog.getProductCount());

  display.setText(0, catalog.getHeader());
}

static void syncClockIfNeeded()
{
  if( clockSyncTime != 0 && clockSyncTime + CLOCK_SYNC_PERIOD < millis() ) 
    return;
  
  unsigned long time = api.getTime();
  
  if( time != 0 )
  {      
    clockSyncTime = millis(); 
    clock.setTime(time);
  }
  else
  {
    clockSyncTime = 0;
  }
  
   Serial.print("TIME = ");
  Serial.println(time); 
}



void loop() 
{  
  syncClockIfNeeded();
  
  if( clockSyncTime == 0 )
  {
   display.setText(0, "* * * ERROR * * *"); 
   display.setText(1, "Connection failed");
  }
  
  int product = buttons.getSelectedIndex();

  display.setSelection(1, catalog.getProduct(product)); 

  char* badge = rfid.tryRead();

  if( badge )
  {
    Serial.println(badge);     
    api.buy(clock.getTime(), badge, product);
  }

  delay(100);
}




