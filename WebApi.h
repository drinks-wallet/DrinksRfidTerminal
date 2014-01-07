#ifndef _WEBAPI_H
#define _WEBAPI_H

#include "Catalog.h"

class WebApi
{
  public:
    void begin();
    unsigned long getTime();    
    void getCatalog(Catalog& catalog);    
};

#endif
