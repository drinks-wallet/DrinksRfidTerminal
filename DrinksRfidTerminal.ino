#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#include "Buttons.h"
#include "Catalog.h"
#include "Display.h"
#include "WebClient.h"

WebClient webClient;
Catalog catalog;
Display display;
Buttons buttons;

void setup() 
{  
  Serial.begin(9600);
  
  display.begin();
  display.setHeader("Initialize...");    
  
  webClient.begin();
  buttons.begin();
  
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
    
  delay(100);
}


