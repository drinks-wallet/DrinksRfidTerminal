#include <Arduino.h>

#include "HttpClient.h"
#include "WebApi.h"

static HttpClient http;

void WebApi::begin()
{
  http.begin();
}

unsigned long WebApi::getTime()
{
  if (!http.connect()) return 0;

  http.performGetRequest("/drinks/api/terminal/time");

  char line[16];
  http.readln(line, sizeof(line));

  unsigned long clock = strtoul(line, NULL, 10);

  http.disconnect();

  return clock;
}

void WebApi::getCatalog(Catalog& catalog)
{
  if (!http.connect()) return;

  http.performGetRequest("/drinks/api/terminal/catalog");

  char buffer[32];
  int i;
  boolean more;

  more = http.readblock(buffer, sizeof(buffer), ';');
  catalog.setHeader(buffer);
  
  for( i=0 ; i<CATALOG_MAX_COUNT && more; i++)
  {    
    more = http.readblock(buffer, sizeof(buffer), ';');
    catalog.setProduct(i, buffer);
  }
  catalog.setProductCount(i);  

  http.disconnect();
}

bool WebApi::buy(unsigned long time, char* badge, int product)
{
  char buffer[64];
  sprintf(buffer, "time=%lu&badge=%s&product=%d", time, badge, product);
  
  Serial.println(buffer);
 
  http.performPostRequest("/drinks/api/terminal/buy", buffer);
  
  http.readln(buffer, 64);
  
  Serial.println(buffer);
}




