/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Dns.h>

#include "Configuration.h"
#include "HttpClient.h"

#define xstr(s) str(s)
#define str(s) #s

#define NOT_EMPTY(s) (s[0]!=0 && s[0]!='\r' && s[0]!='\n')

void HttpClient::begin()
{
    delay(100);

    byte mac[6] = MAC_ADDRESS;

    Serial.println("DHCP...");

    // start the Ethernet connection:
    while (0 == Ethernet.begin(mac)) 
    {
        Serial.println("Failed. Retry...");
    }

    Serial.print("Address=");
    Serial.println(Ethernet.localIP());
    
    Serial.print("Subnet=");
    Serial.println(Ethernet.subnetMask());
    
    Serial.print("DNS=");
    Serial.println(Ethernet.dnsServerIP());

    Serial.println("Resolve " SERVER_NAME "...");
    
    DNSClient dns;

    dns.begin(Ethernet.dnsServerIP());

    while (1 != dns.getHostByName(SERVER_NAME, serverIp))
    {
        Serial.println("Failed. Retry...");
    }

    Serial.print("Address=");
    Serial.println(serverIp);

}

void HttpClient::readln(char* buffer, int size)
{
    int i;

    for (i = 0; i < size - 1; i++)
    {
        while (!client.available())
        {
            if (!client.connected())
            {
                buffer[i] = 0;
                return;
            }
        }

        buffer[i] = client.read();
        // Serial.print(buffer[i]); 

        if (buffer[i] == '\n')
            break;
    }

    buffer[i] = 0;
}

bool HttpClient::perform(const char* request, char* content, int maxContentSize)
{
    /*
     * 1. SEND REQUEST
     */

    Serial.println(request);    

    if (!client.connect(serverIp, SERVER_PORT))
    {
        Serial.println("Connect failed");
        return false;
    }
    
    client.print(request);
    client.println(" HTTP/1.1");
    client.println("Host: " SERVER_NAME ":" xstr(SERVER_PORT));
    client.println("Accept: application/json");
    client.println("Connection: close");

    if (content[0])
    {
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(strlen(content));
        client.println();

        Serial.println(content);
        client.println(content);
    }
    else
    {
        client.println();
    }

    /*
     * 2. READ RESPONSE
     */        
    
    // skip HTTP headers
    while (readln(content, maxContentSize), NOT_EMPTY(content));

    // read content
    readln(content, maxContentSize);
        
    Serial.println(content);

    client.stop();

    return content[0] != 0;
}


