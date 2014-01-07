#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "Buttons.h"
#include "Catalog.h"
#include "Display.h"
#include "RfidReader.h"
#include "WebClient.h"

static Buttons buttons;
static Catalog catalog;
static Display display;
static RfidReader rfid;
static WebClient webClient;

void setup() 
{  
  Serial.begin(9600);

  display.begin();
  display.setHeader("Initialize...");    

  webClient.begin();
  buttons.begin();
  rfid.begin();

  display.setHeader("Connecting...");    

  Serial.print("CLOCK = ");
  Serial.println(webClient.getClock());

  Serial.println("CATALOG:");

  webClient.getCatalog(catalog);

  for( int i=0 ; i<catalog.getProductCount() ; i++ )
  {
    Serial.println(catalog.getProduct(i));    
  }

  buttons.setCount(catalog.getProductCount());

  display.setHeader(catalog.getHeader());
}



void loop() 
{  
  display.setSelection(catalog.getProduct(buttons.getSelectedIndex())); 

  char* badge = rfid.tryRead();

  if( badge )
  {
    Serial.println(badge); 
  }

  delay(100);
}



