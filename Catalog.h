#ifndef _CATALOG_H
#define _CATALOG_H

#define CATALOG_MAX_COUNT      10
#define PRODUCT_PRICE_MAX_SIZE 8
#define PRODUCT_NAME_MAX_SIZE 16

class Catalog
{
  public:
  
    Catalog();
   
    void setCount(int);
    int getCount();
    
    char* getName(int);
    void setName(int,char*);
    
    char* getPrice(int);
    void setPrice(int,char*);

  private:

    int count;
    char prices[10][PRODUCT_PRICE_MAX_SIZE];
    char names[10][PRODUCT_NAME_MAX_SIZE];
};

#endif
