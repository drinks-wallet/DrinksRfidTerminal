#include <Arduino.h>

#include "HttpClient.h"
#include "WebClient.h"

static HttpClient http;

void WebClient::begin()
{
  http.begin();
}

unsigned long WebClient::getTime()
{
  if (!http.connect()) return 0;

  http.performGetRequest("/drinks/api/terminal/time");

  char line[16];
  http.readln(line, sizeof(line));

  unsigned long clock = strtoul(line, NULL, 10);

  http.disconnect();

  return clock;
}

void WebClient::getCatalog(Catalog& catalog)
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




