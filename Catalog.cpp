#include "Catalog.h"   
#include <string.h>

Catalog::Catalog()
{
 count = 0; 
}

void Catalog::setCount(int n)
{
  count = n;
}

int Catalog::getCount()
{
 return count; 
}
    
char* Catalog::getName(int id)
{
 return names[id];
}

void Catalog::setName(int id,char* s)
{
 strncpy(names[id], s, PRODUCT_NAME_MAX_SIZE); 
}

char* Catalog::getPrice(int id)
{
   return prices[id];
}

void Catalog::setPrice(int id,char* s)
{
   strncpy(prices[id], s, PRODUCT_PRICE_MAX_SIZE); 
}





