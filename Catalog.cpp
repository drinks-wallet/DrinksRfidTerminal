/*
* "Drinks" RFID Terminal
* Buy sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

#include <string.h>

#include "Catalog.h"   

Catalog::Catalog()
{
    count = 0;
}

void Catalog::setProductCount(int n)
{
    count = n;
}

int Catalog::getProductCount()
{
    return count;
}

char* Catalog::getProduct(int id)
{
    return products[id];
}

void Catalog::setProduct(int id, char* s)
{
    strncpy(products[id], s, PRODUCT_NAME_SIZE);
}

char* Catalog::getHeader()
{
    return header;
}

void Catalog::setHeader(char* s)
{
    strncpy(header, s, CATALOG_HEADER_SIZE);
}





