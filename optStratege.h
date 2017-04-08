#ifndef OPTSTRATEGE_H
#define OPTSTRATEGE_H

#include "function.h"
#include "etfOption.h"
#include <vector>

#define AT_MONEY_INDEX OPTION_AT_MONEY
#define IN_MONEY_INDEX OPTION_IN_MONEY
#define OUT_MONEY_INDEX OPTION_OUT_MONEY

		

class optStratege
{
private:
/*
 * opn...Interest[life][at/in/out][level]
 * life:0-3
 * at/in/out:0/1/2
 * level:0-4
 */
	etfOption * opnPutInterest[4][3][MAX_LEVEL];
	etfOption * opnCalInterest[4][3][MAX_LEVEL];
	unsigned int opnPutQuantity[4][3][MAX_LEVEL];
	unsigned int opnCalQuantity[4][3][MAX_LEVEL];
	etfOptList * opnIntList;
	public:
	optStratege();
	~optStratege();
	etfOptList * putOptPrsList[4];
	etfOptList * calOptPrsList[4]; 
	
	
	unsigned int expMonth[4];
	
	unsigned int expDate[4];
	
	unsigned int lftDays[4];

	
	unsigned int etfPrs10k;
	unsigned int curYear;
	unsigned int curMonth;
	unsigned int curDate;
	unsigned int money;
	
	
	
	int setPutOptPrsList(etfOptList * l0, etfOptList * l1, etfOptList * l2, etfOptList * l3);
	int setCalOptPrsList(etfOptList * l0, etfOptList * l1, etfOptList * l2, etfOptList * l3);	
	
	int tryShfPosition(etfOption *tg);
	

	int getTotTV(etfOptList * opnInterest);  //return total time value of open interest
	int getTotRV(etfOptList *opnInterest); //return total real value of open interest
	int getTotDeposit();
	
	int getCurPrise(etfOption *tg);
	static unsigned int getExpDate(unsigned int year, unsigned month);
	int setExpDate();
	
	unsigned int getShfDelta(char optType);
	
	etfOption * getTheOption(etfOption * tg);
	etfOption * getTheOption(unsigned int exePrise, char optType, unsigned int optLife);
	int getOptIndex(unsigned int exePrise, char optType, unsigned int optLife);
	unsigned int getAtMnyExePrise();

	
	etfOptList * getPrsList(char optType, unsigned int optLife);

	int setTimeValue();
    int setDate(unsigned int year, unsigned int month, unsigned int date);
	int setLeftDays();
	etfOption * fndMstVluOpt(int level,char optType);
	
	unsigned int prmShfPutPstDelta; //shift put position prise delta
	unsigned int prmShfCalPstDelta; //shift call position prise delta
	
	unsigned int ansPrepare();
	unsigned int ansRatio(int result[4][3][MAX_LEVEL], int total);	
	unsigned int ansQtyCurve(int result[4][3][MAX_LEVEL], char optType);// result[optLife][atMoney][level]
	unsigned int ansTVCurve(int result[4][3][MAX_LEVEL],  char optType);// result[optLife][atMoney][level]
	unsigned int ansRVCurve(int result[4][3][MAX_LEVEL], char optType);// result[optLife][atMoney][level]
	unsigned int ansPrsCurve(int result[4][3][MAX_LEVEL], char optType);
	unsigned int ansDpsCurve(int result[4][3][MAX_LEVEL], unsigned int delta);
	unsigned int ansPrfCurve(int result[4][3][MAX_LEVEL]);
	unsigned int prdTV(char optType, unsigned int tvRef, int delta);
	

	
	int setOpnInterest(etfOptList * opnInsList);
	int setCurOpnIntPrise();
	
};

int prnAnsMatrix(int result[4][3][MAX_LEVEL], const char * info);
#endif // OPTSTRATEGE_H
