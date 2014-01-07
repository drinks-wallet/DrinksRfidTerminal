#ifndef _WEBCLIENT_H
#define _WEBCLIENT_H

#include "Catalog.h"

class WebClient
{
  public:
    void begin();
    unsigned long getTime();    
    void getCatalog(Catalog& catalog);    
};

#endif
