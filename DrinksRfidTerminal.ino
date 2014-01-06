#include "WebClient.h"
#include <SPI.h>
#include <Ethernet.h>

WebClient webClient;

void setup() 
{  
  Serial.begin(9600);
  
  webClient.begin();
}

void loop() 
{
  Serial.print("CLOCK = ");
  Serial.println(webClient.getClock());
  delay(5000);
}


