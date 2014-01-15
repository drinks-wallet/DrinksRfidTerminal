#include <Arduino.h>
#include <JsonParser.h>
#include <SipHash_2_4.h>

#include "Clock.h"
#include "HttpClient.h"
#include "WebApi.h"

#define SYNC_PERIOD    60000L
//#define TESTING_WITHOUT_SERVER 1

static HttpClient http;
static Clock clock;

static unsigned long lastSyncTime = 0;

unsigned char key[16] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

void WebApi::begin()
{
  http.begin();
}

bool extractHead(JsonHashTable root, Catalog& catalog)
{  
  char* header = root.getString("Header");
  
  if (header == NULL)
  {
    Serial.println("Sync: 'Header' not found");
    return false;
  }
  
  catalog.setHeader(header);
  
  return true;
}

bool extractProducts(JsonHashTable root, Catalog& catalog)
{  
  JsonArray array = root.getArray("Products");

  if (!array.success())
  {
    Serial.println("Sync: 'Products' not found");
    return false;
  }
  
  Serial.println("products=");

  int count = array.getLength();
  catalog.setProductCount(count);
  
  for( int i=0 ; i<count ; i++ )
  {
    char* name = array.getString(i);
    Serial.println(name);
    catalog.setProduct(i, name);
  }
  
  return true;
}

bool extractTime(JsonHashTable root)
{
  unsigned long time = root.getLong("Time");
  
  if (time == 0)
  {
   Serial.println("Sync: 'Time' not found");
   return false;
  }
  
  clock.setTime(time); 
  
  return true;
}

boolean WebApi::sync(Catalog& catalog)
{ 
  if( millis() < lastSyncTime + SYNC_PERIOD )
    return true;  
  
  Serial.println("Sync...");
  
  char json[160];

#if TESTING_WITHOUT_SERVER
  strcpy(json, "{\"Header\":\"Selectionnez...\",\"Products\":[\"Can 1E\",\"Ice 0.5E\"],\"Time\":0}");
#else
  if( !http.performGetRequest("/drinks/api/sync", json, sizeof(json)) ) return false;
#endif
  
  JsonParser<100> parser;
  
  Serial.println(json);
  
  JsonHashTable root = parser.parseHashTable(json);
  
  if (!root.success())
  {
   Serial.println("Sync: invalid JSON"); 
   return false;
  }     
   
  boolean success = 
    extractHead(root,catalog) &&
    extractProducts(root,catalog) &&
    extractTime(root);

  if( success ) 
  {
    lastSyncTime = millis();
  }
  
  return success;
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

bool WebApi::buy(char* badge, int product)
{
  if (!http.connect()) return false;
  
  int i, j;
  char buffer[128];
  char* hash = buffer + sprintf(buffer, "badge=%s&product=%d&time=%lu&hash=", badge, product, clock.getTime());
   
  computeHash(buffer, hash);
  
  //Serial.println(buffer);
  
  http.performPostRequest("/drinks/api/buy", buffer);
  
  http.readln(buffer, 64);
  
  Serial.println(buffer);
  
  http.disconnect();
  
  return true;
}




