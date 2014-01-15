#ifndef _WEBAPI_H
#define _WEBAPI_H

#include "Catalog.h"

class WebApi
{
  public:
    void begin();
    
    boolean sync(Catalog& catalog);    
    
    bool buy(char* badge, int product);
};

#endif
