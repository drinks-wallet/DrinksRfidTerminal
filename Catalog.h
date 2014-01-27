/*
* "Drinks" RFID Terminal
* Buy your sodas with your company badge!
*
* Benoit Blanchon 2014 - MIT License
* https://github.com/bblanchon/DrinksRfidTerminal
*/

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
	void setProduct(int, char*);

	char* getHeader();
	void setHeader(char*);

	static const int MAX_PRODUCT_COUNT = 4;
	static const int PRODUCT_NAME_SIZE = 19;
	static const int CATALOG_HEADER_SIZE = 21;

private:

	int count;
	char products[MAX_PRODUCT_COUNT][PRODUCT_NAME_SIZE];
	char header[CATALOG_HEADER_SIZE];
};

#endif
