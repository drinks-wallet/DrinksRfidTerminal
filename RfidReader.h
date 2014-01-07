#ifndef _RFIDREADER_H
#define _RFIDREADER_H

class RfidReader
{
  public:
  
    void begin();
    char* tryRead();
};

#endif
