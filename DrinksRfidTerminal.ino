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
  webClient.begin();
  buttons.begin();
  
  
  
    display.setHeader("CHOOSE PRODUCT:");
  
  Serial.print("CLOCK = ");
  Serial.println(webClient.getClock());
  
  Serial.println("CATALOG =");
  
  webClient.getCatalog(catalog);
    
  for( int i=0 ; i<catalog.getCount() ; i++ )
  {
   Serial.print("PRICE=");
   Serial.println(catalog.getPrice(i));
   
   Serial.print("NAME=");
   Serial.println(catalog.getName(i));    
  }
  
    buttons.setCount(catalog.getCount());
}



void loop() 
{  
  display.setSelection(catalog.getName(buttons.getSelectedIndex())); 
    
  delay(100);
}


