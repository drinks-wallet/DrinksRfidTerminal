#include <Arduino.h>
#include <SipHash_2_4.h>

#include "HttpClient.h"
#include "WebApi.h"

static HttpClient http;

unsigned char key[16] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

void WebApi::begin()
{
  http.begin();
}

unsigned long WebApi::getTime()
{
  if (!http.connect()) return 0;

  http.performGetRequest("/drinks/api/time");

  char line[16];
  http.readln(line, sizeof(line));

  unsigned long clock = strtoul(line, NULL, 10);

  http.disconnect();

  return clock;
}

void WebApi::getCatalog(Catalog& catalog)
{
  if (!http.connect()) return;

  http.performGetRequest("/drinks/api/catalog");

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

static void computeHash(char* source, char* destination)
{
  sipHash.initFromPROGMEM(key);
  for (int i=0; source[i] ;i++)
    sipHash.updateHash((byte)source[i]);
  sipHash.finish();  
  
  for(int i=0 ; i<8 ; i++)
  {
    sprintf(destination+2*i, "%02X", sipHash.result[i]);
  }
  destination[16] = 0;
}

bool WebApi::buy(unsigned long time, char* badge, int product)
{
  if (!http.connect()) return false;
  
  int i, j;
  char buffer[128];
  char* hash = buffer + sprintf(buffer, "badge=%s&product=%d&time=%lu&hash=", badge, product, time);
   
  computeHash(buffer, hash);
  
  //Serial.println(buffer);
  
  http.performPostRequest("/drinks/api/buy", buffer);
  
  http.readln(buffer, 64);
  
  Serial.println(buffer);
  
  http.disconnect();
  
  return true;
}




