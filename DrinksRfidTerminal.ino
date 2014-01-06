#include <SPI.h>
#include <Ethernet.h>

#include "Catalog.h"
#include "WebClient.h"

WebClient webClient;
Catalog catalog;

void setup() 
{  
  Serial.begin(9600);
  
  webClient.begin();
}

void loop() 
{
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
  
  delay(5000);
}


