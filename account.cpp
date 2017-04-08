
#include "account.h"
#include "datAPI.h"
#include <stdio.h>


account::account()
{
	money =500000;//50w
	sevCharge = 8.2;
	opnIntList.reserve(100);
}

account::~account()
{
}

int account::initial(unsigned int year, unsigned month, unsigned int date){
	optS.setDate(year,month,date);
	return FUNCTION_SUCCESS;
}

int account::cycCheck(){
	/*
	rdPrise(&putPrsList0, &putPrsList1,&putPrsList2, &putPrsList3,
	&calPrsList0, &calPrsList1,&calPrsList2, &calPrsList3);
	optS.setCalOptPrsList(&calPrsList0, &calPrsList1, &calPrsList2, &calPrsList3);
	optS.setPutOptPrsList(&putPrsList0, &putPrsList1, &putPrsList2, &putPrsList3);
	optS.setTimeValue();
	if(opnInterest.size() == 0){
		
		
	}*/
	optS.setOpnInterest(&opnIntList);
	optS.ansPrepare();
	return FUNCTION_SUCCESS;
}
int account::setOpnInterest(unsigned int expYear, unsigned int expMonth, char optType, unsigned int exePrise, unsigned int quantity)
{
	etfOption opt;
	opt.expYear = expYear;
	opt.expMonth = expMonth;
	opt.optType = optType;
	opt.exePrise = exePrise;
	opt.opnInterest = quantity;
	opnIntList.push_back(opt);
	return FUNCTION_SUCCESS;
}
int account::setEtfStatus(unsigned int cur10KPrise)
{
	optS.etfPrs10k = cur10KPrise;
	return FUNCTION_SUCCESS;
}
int account::setPrsList(etfOptList* calOptList, etfOptList* putOptList)
{
	if((calOptList == NULL )|| (putOptList == NULL)){
		return FUNCTION_ERROR;
	}
	optS.setCalOptPrsList(&calOptList[0],&calOptList[1], &calOptList[2],&calOptList[3]);
	optS.setPutOptPrsList(&putOptList[0],&putOptList[1], &putOptList[2],&putOptList[3]);
	return FUNCTION_SUCCESS;
}
int account::getTotalDeposit()
{
	if(opnIntList.empty()){
		return 0;
	}
	return optS.getTotDeposit();
}
