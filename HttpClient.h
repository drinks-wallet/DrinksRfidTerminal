#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

class HttpClient
{
  public:
    void begin();   
    bool connect();
    void disconnect();
    void println();
    void println(char*);
    void readln(char*,int);
    bool readblock(char*,int,char);
    void skipHeaders();
    void performGetRequest(char*);    
    void performPostRequest(char* path, char* content);
    
  private:
    void sendCommonHeader(char*,char*);
};

#endif
