#ifndef _CATALOG_H
#define _CATALOG_H

#include "Configuration.h"

class Catalog
{
  public:
  
    Catalog();
   
    void setProductCount(int);
    int getProductCount();
    
    char* getProduct(int);
    void setProduct(int,char*);
    
    char* getHeader();
    void setHeader(char*);
    
  private:

    int count;
	char products[MAX_PRODUCT_COUNT][PRODUCT_NAME_SIZE];
    char header[CATALOG_HEADER_SIZE];
};

#endif
