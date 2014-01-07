#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

#include "HttpClient.h"

#define MAX_LINE_SIZE 32
#define SERVER_PORT 8080

static IPAddress server(10,1,130,11); 
// char server[] = "lbotelho-pc";

static EthernetClient client;

static byte mac[] = {  
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

void HttpClient::begin()
{
  delay (100);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

  // give the Ethernet shield a second to initialize:
  delay(1000);
}

bool HttpClient::connect()
{
  if (client.connect(server, SERVER_PORT)) {
    //Serial.println("connected");
    return true;
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
    return false;
  }
}

void HttpClient::disconnect()
{
  client.stop(); 
}

void HttpClient::println()
{
  client.println();
}

void HttpClient::println(char* s)
{
  client.println(s);
}

void HttpClient::readln(char* buffer, int size)
{
  readblock(buffer, size, '\n');
}

bool HttpClient::readblock(char* buffer, int size, char terminator)
{
  for( int i=0; i<size ; i++ )
  {
    while (!client.available())
    {
      if(!client.connected())
      {
        buffer[i] = 0;
        return false;
      } 
    }

    buffer[i] = client.read();
    //Serial.print(buffer[i]);

    if( buffer[i] == terminator )
    {
      buffer[i] = 0;
      return true;
    } 
  }
}


void HttpClient::skipHeaders()
{
  char line[32];
  do
  {    
    readln(line, sizeof(line));
  }
  while( line[0] != '\r' && line[0] != '\n'); 
}

void HttpClient::performGetRequest(char* path)
{
  client.print("GET ");
  client.print(path);
  client.println(" HTTP/1.1");
  client.println("Host: 10.1.130.11:8080");
  client.println("Accept: text/plain");
  client.println("Connection: close");
  client.println();

  skipHeaders(); 
}



