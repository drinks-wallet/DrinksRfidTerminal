#ifndef _WEBAPIBUYREQUEST_H
#define _WEBAPIBUYREQUEST_H

class WebApiBuyRequest
{
public:

	WebApiBuyRequest(char* badge, int product, unsigned long time)
	{
		this->badge = badge;

		sprintf(this->product, "%d", product);
		sprintf(this->time, "%lu", time);
	}

	void getContent(char*, int);

private:

	void computeHash(char*);

	char* badge;
	char product[2];
	char time[11];
};

#endif 