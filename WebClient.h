#ifndef _WEBCLIENT_H
#define _WEBCLIENT_H

class WebClient
{
  public:
    void begin();
    unsigned long getClock();    
    
  private:
    bool connect();
    void disconnect();
    void println();
    void println(char*);
    void readln(char*,int);
    void skipHeaders();
};

#endif
