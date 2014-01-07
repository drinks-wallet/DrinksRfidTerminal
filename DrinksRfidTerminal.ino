#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>
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
  Serial.begin(9600);

  display.begin();
  display.setHeader("Initialize...");    

  api.begin();
  buttons.begin();
  rfid.begin();

  display.setHeader("Connecting...");    
  
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

  display.setHeader(catalog.getHeader());
}



void loop() 
{  
  int product = buttons.getSelectedIndex();
  
  display.setSelection(catalog.getProduct(product)); 

  char* badge = rfid.tryRead();

  if( badge )
  {
    Serial.println(badge);     
    api.buy(clock.getTime(), badge, product);
  }

  delay(100);
}



