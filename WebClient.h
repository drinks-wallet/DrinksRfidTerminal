#ifndef _WEBCLIENT_H
#define _WEBCLIENT_H

#include "Catalog.h"

class WebClient
{
  public:
    void begin();
    unsigned long getClock();    
    void getCatalog(Catalog& catalog);
    
  private:
    bool connect();
    void disconnect();
    void println();
    void println(char*);
    void readln(char*,int);
    bool readblock(char*,int,char);
    void skipHeaders();
    void performGetRequest(char*);    
};

#endif
