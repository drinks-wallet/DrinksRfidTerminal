#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#include "Catalog.h"
#include "Display.h"
#include "WebClient.h"

WebClient webClient;
Catalog catalog;
Display display;

void setup() 
{  
  Serial.begin(9600);
  
  display.begin();
  webClient.begin();
}

void loop() 
{
  display.setHeader("CHOOSE PRODUCT:");
  
  Serial.print("CLOCK = ");
  Serial.println(webClient.getClock());
  
  Serial.println("CATALOG =");
  
  webClient.getCatalog(catalog);
  
  display.setSelection(catalog.getName(0));
  
  for( int i=0 ; i<catalog.getCount() ; i++ )
  {
   Serial.print("PRICE=");
   Serial.println(catalog.getPrice(i));
   
   Serial.print("NAME=");
   Serial.println(catalog.getName(i));    
  }
    
  delay(5000);
}


