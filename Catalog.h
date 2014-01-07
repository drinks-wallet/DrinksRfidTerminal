#ifndef _CATALOG_H
#define _CATALOG_H

#define CATALOG_MAX_COUNT        10
#define PRODUCT_NAME_MAX_SIZE    24
#define CATALOG_HEADER_MAX_SIZE  24

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
    char products[10][PRODUCT_NAME_MAX_SIZE];
    char header[CATALOG_HEADER_MAX_SIZE];
};

#endif
