#include "Catalog.h"   
#include <string.h>

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

void Catalog::setProduct(int id,char* s)
{
 strncpy(products[id], s, PRODUCT_NAME_MAX_SIZE); 
}

char* Catalog::getHeader()
{
   return header;
}

void Catalog::setHeader(char* s)
{
   strncpy(header, s, CATALOG_HEADER_MAX_SIZE); 
}





