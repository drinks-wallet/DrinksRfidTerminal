#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <SipHash_2_4.h>
#include <SoftwareSerial.h>

#include "Buttons.h"
#include "Catalog.h"
#include "Clock.h"
#include "Display.h"
#include "RfidReader.h"
#include "WebApi.h"

static Buttons buttons;
static Catalog catalog;
static Clock clock;
static Display display;
static RfidReader rfid;
static WebApi api;

void setup() 
{  
  display.begin();
  display.setText(0, "Serial console 9600");
  display.setText(1, "Press any key");
  
  Serial.begin(9600);
  
  while( millis() < 2000 );  

  display.begin();
  display.setText(0, "Initialize...");   
  display.setText(1, "");

  api.begin();
  buttons.begin();
  rfid.begin();

  display.setText(0, "Connecting...");    
  
  unsigned long time = api.getTime();
  clock.setTime(time); 
  
  Serial.print("TIME = ");
  Serial.println(time);  

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



void loop() 
{  
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



