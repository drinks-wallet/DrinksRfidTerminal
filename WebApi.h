#ifndef _WEBAPI_H
#define _WEBAPI_H

#include "Catalog.h"
#include "Clock.h"
#include "HttpClient.h"

class WebApi
{
  public:
    void begin();
    
    bool sync(Catalog& catalog);    
    
    bool buy(char* badge, int product);
    
  private:
  
    bool performSync(Catalog& catalog);
  
    HttpClient http;
    Clock clock;
    unsigned long lastSyncTime;
};

#endif
