#ifndef ETFOPTION_H
#define ETFOPTION_H

#include <vector>
#include "function.h"

#define EXSISTING_MONTH 4


#define OPTION_TYPE_CALL 'c'
#define OPTION_TYPE_PUT 'p'

#define OPTION_AT_MONEY 0
#define OPTION_IN_MONEY 1
#define OPTION_OUT_MONEY 2
#define MAX_LEVEL 5

const unsigned char MMT []= { //month mapping table
	1,2,3,6,
	2,3,6,9,
	3,4,6,9,
	4,5,6,9,
	5,6,9,12,
	6,7,9,12,
	7,8,9,12,
	8,9,12,3,
	9,10,12,3,
	10,11,12,3,
	11,12,3,6,
	12,1,3,6
};

class etfOption;

typedef std::vector<etfOption> etfOptList;

class etfOption
{
public:
	etfOption();
	~etfOption();
	
	
	char optMethod;  //'S' -- Short option(Buy); 'L'-- Long option (Sell) 
	char optType; //Call or Put
	unsigned int expYear;
	unsigned int expMonth;
	unsigned int expDate;

	unsigned int curPrise; //current option prise in optUint (10k ususally)
	unsigned int exePrise; //execution prise in optUint (10k usually)
	unsigned int opnInterest;	
	int realValue;
	int timeValue;

	
	int getNxtOption(etfOption *tgt,unsigned int curMonth, unsigned int delta =1);
	int getPreOption(etfOption *tgt,unsigned int curMonth, unsigned int delta =1);
	int getDpOption(etfOption * tgt, etfOptList *optList);
	int getLtOption(etfOption *tgt, etfOptList *optList);
//	int getCurPrise(etfOptList * optList);
	unsigned int getDeposit(unsigned int curEtfPrise);
	unsigned int getInOutMoney(unsigned int curEtfPrise);
	unsigned int getLevel(unsigned int atMnyPirse);
	int getLife(unsigned int firExeMonth);
	int getTV(unsigned int curEtfPrise);
	int getRV(unsigned int curEtfPrise);
	etfOption * findExePrise(etfOptList * optList);
	
private:
	unsigned int optUnit; //10k by default
	float dptRatio; //1.2 by default
	


};

int prtOptList(etfOptList &list);

#endif // ETFOPTION_H
