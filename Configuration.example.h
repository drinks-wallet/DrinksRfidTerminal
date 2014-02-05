/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

//  PLEASE READ ! ! !
// 
//  You need to rename this file into "Configuration.h" in order to compile the project.
//  Then you must change the values to match you actual configuration.

#define PRIVATE_KEY {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}

#define MAC_ADDRESS {0x01,0x23,0x45,0x67,0x89,0xAB}

#define SERVER_NAME "drinks.example.com"

#define SERVER_PORT 80

#endif