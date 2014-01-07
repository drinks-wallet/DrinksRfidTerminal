#include <Arduino.h>
#include <SoftwareSerial.h>

#include "RfidReader.h"
#include "Pins.h"

static SoftwareSerial RFID(PIN_RFID, PIN_RFID); // RX and TX
static char buffer[16];

void RfidReader::begin()
{
    RFID.begin(9600);    // start serial to RFID reader
}

static char parseHexNibble(char c)
{
   if( c >= 'A' ) return c - 'A' + 0xA;
   if( c >= 'a' ) return c - 'a' + 0xA; 
   return c - '0';
}

static char parseHexByte(char* str)
{
  return (parseHexNibble(str[0]) << 4) | parseHexNibble(str[1]);
}

static char computeCheckSum(char badge[])
{
  char checkSum = 0;
  
  for( int i=0 ; i<5 ; i++ )
  {    
    checkSum ^= parseHexByte(badge+2*i);
  } 
  
  return checkSum;
}


char* RfidReader::tryRead()
{
  int i;

  if (RFID.available() < 14 ) return NULL;
    
  for( i=0 ; i<14 ; i++ )
    buffer[i] = RFID.read();
    
  if( buffer[0] != 2 || buffer[13] != 3 )
  {
    RFID.flush();
    Serial.println("UNSYNCED");
    return NULL;
  }
            
  char readCheckSum = parseHexByte(buffer+11);
  char computedCheckSum = computeCheckSum(buffer+1);
  
  if( readCheckSum != computedCheckSum )
  {
    Serial.println("INVALID CHECK SUM");
    return NULL;
  }
  
  buffer[11] = 0;
  return buffer+1;
}
