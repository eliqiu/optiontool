#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "etfOption.h"
#include "optStratege.h"

class account
{
public:

	etfOptList opnIntList;
	optStratege optS;	

	account();
	~account();
	int cycCheck();
	float money;
	float sevCharge;

	int initial(unsigned int year, unsigned int month, unsigned int date);

	int setOpnInterest(unsigned int expYear, unsigned int expMonth, char optType, unsigned int exePrise, unsigned int quantity);
	int setPrsList(etfOptList calPrsList, etfOptList putPrsList);
	int setDate(unsigned int year, unsigned int month, unsigned int date);
	int setEtfStatus(unsigned int cur10KPrise);
	int setPrsList(etfOptList * calOptList, etfOptList * putOptList);
	
	int getTotalDeposit();

};

#endif // ACCOUNT_H
