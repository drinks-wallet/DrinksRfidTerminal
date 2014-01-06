#include "WebClient.h"
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

#define MAX_LINE_SIZE 32
#define SERVER_PORT 8080

static IPAddress server(10,1,130,11); 
// char server[] = "lbotelho-pc";

static EthernetClient client;

static byte mac[] = {  
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

void WebClient::begin()
{
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

bool WebClient::connect()
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

void WebClient::disconnect()
{
  client.stop(); 
}

void WebClient::println()
{
  client.println();
}

void WebClient::println(char* s)
{
  client.println(s);
}

void WebClient::readln(char* buffer, int size)
{
  for( int i=0; i<size ; i++ )
  {
    while (!client.available())
    {
      if(!client.connected())
      {
        buffer[i] = 0;
        return;
      } 
    }

    buffer[i] = client.read();
    //Serial.print(buffer[i]);

    if( buffer[i] == '\n' )
    {
        buffer[i] = 0;
        return;
    } 
  }
}


void WebClient::skipHeaders()
{
  char line[32];
  do
  {    
    readln(line, sizeof(line));
  }
  while( line[0] != '\r' && line[0] != '\n'); 
}

unsigned long WebClient::getClock()
{
  if (!connect()) return 0;

  println("GET /drinks/api/terminal/clock HTTP/1.1");
  println("Host: 10.1.130.11:8080");
  println("Connection: close");
  println();

  skipHeaders();

  char line[16];
  readln(line, sizeof(line));

  unsigned long clock = strtoul(line, NULL, 10);

  disconnect();

  return clock;
}

