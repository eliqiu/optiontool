#include "optStratege.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "memory.h"


class getCurPrise;
class getCurPrise;
optStratege::optStratege()
{
		calOptPrsList[0] = NULL;
		calOptPrsList[1] = NULL;
		calOptPrsList[2] = NULL;
		calOptPrsList[3] = NULL;
		
		putOptPrsList[0] = NULL;
		putOptPrsList[1] = NULL;
		putOptPrsList[2] = NULL;
		putOptPrsList[3] = NULL;
		
		prmShfCalPstDelta = 150;
		prmShfPutPstDelta = 150;
		money = 500000; //50w initial value;
		
		etfPrs10k = 0;
		memset(opnPutInterest,0,sizeof(opnPutInterest));
		memset(opnPutQuantity,0,sizeof(opnPutQuantity));
		memset(opnCalInterest,0,sizeof(opnCalInterest));
		memset(opnCalQuantity,0,sizeof(opnCalQuantity));
}

optStratege::~optStratege()
{
}

int optStratege::setPutOptPrsList(etfOptList * l0, etfOptList * l1, etfOptList * l2, etfOptList * l3){
		if((l0 == NULL) || (l1 == NULL) ||(l2 == NULL) || (l3 == 0)){
			return FUNCTION_ERROR;
		}
		putOptPrsList[0] = l0;
		putOptPrsList[1] = l1;
		putOptPrsList[2] = l2;
		putOptPrsList[3] = l3;
		
		expMonth[0] = putOptPrsList[0]->at(0).expMonth;
		expMonth[1] = putOptPrsList[1]->at(0).expMonth;
		expMonth[2] = putOptPrsList[2]->at(0).expMonth;
		expMonth[3] = putOptPrsList[3]->at(0).expMonth;
		
		expDate[0] = putOptPrsList[0]->at(0).expDate;
		expDate[1] = putOptPrsList[1]->at(0).expDate;
		expDate[2] = putOptPrsList[2]->at(0).expDate;
		expDate[4] = putOptPrsList[3]->at(0).expDate;
		
		return FUNCTION_SUCCESS;
}

int optStratege::setCalOptPrsList(etfOptList * l0, etfOptList * l1, etfOptList * l2, etfOptList * l3){
		if((l0 == NULL) || (l1 == NULL) ||(l2 == NULL) || (l3 == 0)){
			return FUNCTION_ERROR;
		}
		calOptPrsList[0] = l0;
		calOptPrsList[1] = l1;
		calOptPrsList[2] = l2;
		calOptPrsList[3] = l3;
		
		expMonth[0] = calOptPrsList[0]->at(0).expMonth;
		expMonth[1] = calOptPrsList[1]->at(0).expMonth;
		expMonth[2] = calOptPrsList[2]->at(0).expMonth;
		expMonth[3] = calOptPrsList[3]->at(0).expMonth;
		
		expDate[0] = calOptPrsList[0]->at(0).expDate;
		expDate[1] = calOptPrsList[1]->at(0).expDate;
		expDate[2] = calOptPrsList[2]->at(0).expDate;
		expDate[3] = calOptPrsList[3]->at(0).expDate;
		
		return FUNCTION_SUCCESS;
}
/**************************************************\
 * shift postion to later position
 * 1. check if the prise is larger than prmPrsDelta*MonDelta
 * 2. later month has higher preority. that means moving the postion as far as we can
 *
*/
 
int optStratege::tryShfPosition(etfOption * tg){
	if(tg == NULL){
		return FUNCTION_ERROR;
	}

	etfOption dst,*dst1;
	if(getCurPrise(tg) != FUNCTION_SUCCESS){
		return FUNCTION_ERROR;
	}
	unsigned int monDelta = 0;
	unsigned int shfDelta = getShfDelta(tg->optType);
	if(tg->getNxtOption(&dst,curMonth, 3)== FUNCTION_SUCCESS){
		dst1 = getTheOption(&dst);
		if(dst1 != NULL){
			monDelta = dst1->expYear>tg->expYear?(12+dst1->expMonth-tg->expMonth):(dst1->expMonth-tg->expMonth);
			if((dst1->curPrise-tg->curPrise)>(monDelta*shfDelta)){
				*tg = *dst1;
				return FUNCTION_SUCCESS;
			}
		}
	}
	if(tg->getNxtOption(&dst,curMonth,2) == FUNCTION_SUCCESS){
		dst1 = getTheOption(&dst);
		if(dst1 != NULL){
			monDelta = dst1->expYear>tg->expYear?(12+dst1->expMonth-tg->expMonth):(dst1->expMonth-tg->expMonth);
			if((dst1->curPrise-tg->curPrise)>(monDelta*shfDelta)){
				*tg = *dst1;
				return FUNCTION_SUCCESS;
			}
		}		
	}
	if(tg->getNxtOption(&dst,curMonth,1) == FUNCTION_SUCCESS){
		dst1 = getTheOption(&dst);
		if(dst1 != NULL){
			monDelta = dst1->expYear>tg->expYear?(12+dst1->expMonth-tg->expMonth):(dst1->expMonth-tg->expMonth);
			if((dst1->curPrise-tg->curPrise)>(monDelta*shfDelta)){
				*tg = *dst1;
				return FUNCTION_SUCCESS;
			}
		}		
	}
	return FUNCTION_FAIL;
}



int optStratege::getTotTV(etfOptList * optList){
	if(optList == NULL) return 0;
	int sum = 0;
	etfOption tmp;
	for(etfOptList::iterator it=optList->begin();it!=optList->end();it++){
		sum +=it->getTV(etfPrs10k)*it->opnInterest;
	}
	return sum;
}



int optStratege::getTotRV(etfOptList * optList){
	if(optList == NULL) return 0;
	int sum = 0;
	for(etfOptList::iterator it = optList->begin();it !=optList->end();it++){
		sum += it->getRV(etfPrs10k)*it->opnInterest;
	}
	return sum;
	
}

int optStratege::getCurPrise(etfOption* tg){
	etfOption *src = getTheOption(tg);
	if(src == NULL) return FUNCTION_ERROR;
	tg->curPrise = src->curPrise;
	return FUNCTION_SUCCESS;
}

int optStratege::setCurOpnIntPrise(){
	int result = FUNCTION_SUCCESS;
	
	for(etfOptList::iterator i = opnIntList->begin();i != opnIntList->end();i++){
		if(getCurPrise(&(*i)) != FUNCTION_SUCCESS) result = FUNCTION_ERROR;
	}
	return result;
}

etfOption * optStratege::getTheOption(etfOption * tg){
	unsigned int optLife;
	if(tg == NULL) return NULL;
	if((calOptPrsList[0]->at(0)).expMonth == tg->expMonth) optLife = 0;
	else if(calOptPrsList[1]->at(1).expMonth == tg->expMonth) optLife = 1;
	else if(calOptPrsList[2]->at(2).expMonth == tg->expMonth) optLife = 2;
	else if(calOptPrsList[3]->at(3).expMonth == tg->expMonth) optLife = 3;
	else return NULL; //can't find proper prise list;
	return getTheOption(tg->exePrise, tg->optType,optLife);
}	

etfOptList * optStratege::getPrsList(char optType, unsigned int optLife){
	etfOptList * prsList = NULL;
	if(optType == OPTION_TYPE_CALL){
		switch(optLife){
		case 0: prsList = calOptPrsList[0]; break;
		case 1: prsList = calOptPrsList[1]; break;
		case 2: prsList = calOptPrsList[2]; break;
		case 3: prsList = calOptPrsList[3]; break;
		}
	}else if(optType == OPTION_TYPE_PUT){
		switch(optLife){
		case 0: prsList = putOptPrsList[0]; break;
		case 1: prsList = putOptPrsList[1]; break;
		case 2: prsList = putOptPrsList[2]; break;
		case 3: prsList = putOptPrsList[3]; break;
		
		}		
	}	
	return prsList;
}

int optStratege::getOptIndex(unsigned int exePrise, char optType, unsigned int optLife){
	etfOptList * prsList = getPrsList(optType,optLife);
	if(prsList == NULL) return -1;
	int i=0;
	for(etfOptList::iterator it = prsList->begin(); it!=prsList->end();it++,i++){
		if(it->exePrise == exePrise){
			return i;
		}
	}
	return -1;
}

etfOption * optStratege::getTheOption(unsigned int exePrise, char optType, unsigned int optLife){
	int i = getOptIndex(exePrise, optType, optLife);
	if(i<0) return NULL;
	etfOptList * prsList = getPrsList(optType,optLife);
	if(prsList == NULL) return NULL;
	return &(prsList->at(i));

	
}

int optStratege::getTotDeposit(){
	int sum =0;
	for(etfOptList::iterator it = opnIntList->begin();it!=opnIntList->end();it++){
		std::cout<<"opt prise : "<< it->curPrise<<" / ETF prise : "<<etfPrs10k<<std::endl;
		sum+=it->getDeposit(etfPrs10k)*it->opnInterest;
	}
	return sum;
}


unsigned int optStratege::getExpDate(unsigned int year, unsigned int month){
	unsigned int week=0;

	if(month == 1 || month == 2){
		month += 12;
		year--;
	}
	//calculate date 01;
	week=(1+2*month+3*(month+1)/5+year+year/4-year/100+year/400)%7;
	
    switch(week)
	{
		case 0:;
		case 1:;
		case 2:
		{
			return 3*7+3-week;
			
		}
		
		case 3:;
		case 4:;
		case 5:;
		case 6:
		{
			return 3*7 + 7-week + 3;
		}
	}
	return 0;
}

#define __SET_CALL_OPTION_TIME_VALUE__(x)  \
{\
	if(calOptPrsList[x] != NULL){\
		for(etfOptList::iterator it = calOptPrsList[x]->begin();it!=calOptPrsList[x]->end();it++){\
			if(it->exePrise>etfPrs10k){\
				it->realValue = 0;\
				it->timeValue = it->curPrise;\
			}else{\
				it->realValue = etfPrs10k - it->exePrise;\
				it->timeValue = it->curPrise - it->realValue;\
			}\
		}\
	} else {\
		return FUNCTION_ERROR;\
	}\
}

#define __SET_PUT_OPTION_TIME_VALUE__(x)  \
{\
	if(putOptPrsList[x] != NULL){\
		for(etfOptList::iterator it = putOptPrsList[x]->begin();it!=putOptPrsList[x]->end();it++){\
			if(it->exePrise<etfPrs10k){\
				it->realValue = 0;\
				it->timeValue = it->curPrise;\
			}else{\
				it->realValue =  it->exePrise-etfPrs10k;\
				it->timeValue = it->curPrise - it->realValue;\
			}\
		}\
	} else {\
		return FUNCTION_ERROR;\
	}\
}
int optStratege::setTimeValue(){
	if(etfPrs10k == 0){
		return FUNCTION_ERROR;
	}
	__SET_CALL_OPTION_TIME_VALUE__(0);
	__SET_CALL_OPTION_TIME_VALUE__(1);
	__SET_CALL_OPTION_TIME_VALUE__(2);
	__SET_CALL_OPTION_TIME_VALUE__(3);
	__SET_PUT_OPTION_TIME_VALUE__(0);
	__SET_PUT_OPTION_TIME_VALUE__(1);
	__SET_PUT_OPTION_TIME_VALUE__(2);
	__SET_PUT_OPTION_TIME_VALUE__(3);	
	return FUNCTION_SUCCESS;

}

int optStratege::setDate(unsigned int year, unsigned int month, unsigned int date){
	curYear = year;
	curDate = date;
	curMonth = month;
	return FUNCTION_SUCCESS;
}

#define __SET_EXP_DATE__(x) \
{\
	if(putOptPrsList[x] != NULL){\
		expDate[x] = getExpDate(putOptPrsList[x]->at(0).expYear, putOptPrsList[x]->at(0).expMonth);\
	}else if(calOptPrsList[x] != NULL){\
		expDate[x] = getExpDate(calOptPrsList[x]->at(0).expYear, calOptPrsList[x]->at(0).expMonth);\
	}else{\
		return FUNCTION_ERROR;\
	}\
}

int optStratege::setExpDate(){

	__SET_EXP_DATE__(0);
	__SET_EXP_DATE__(1);
	__SET_EXP_DATE__(2);
	__SET_EXP_DATE__(3);
	return FUNCTION_SUCCESS;
}

int optStratege::setLeftDays(){
	if(curMonth<calOptPrsList[0]->at(0).expMonth){
		lftDays[0] = expDate[0] + 31- curDate;
	}else{
		lftDays[0] = expDate[0] - curDate;
	}
	lftDays[1] = lftDays[0] + 30;
	if(curMonth<calOptPrsList[2]->at(0).expMonth){
		lftDays[2] = lftDays[1] + 30*(calOptPrsList[2]->at(0).expMonth - curMonth);
	}else{
		lftDays[2] = lftDays[1] + 30*(12+calOptPrsList[2]->at(0).expMonth - curMonth);
	}
	lftDays[3] = lftDays[2] + 90;
	return FUNCTION_SUCCESS;
}
/*
 * level = 0: at the money option.
 * level < 0: out the money option.
 * level > 0: in the money option.
 */
etfOption * optStratege::fndMstVluOpt(int level,char optType){
	unsigned int expPrise = getAtMnyExePrise();
	etfOption * opt0, * opt1, * opt2, * opt3, * result = NULL;
	int val0,val1,val2,val3;
	expPrise += level*500;
	opt0 = getTheOption(expPrise,optType,0);
	if(opt0 == NULL){
		val0 = 0;
	}else{
		val0 = opt0->timeValue/lftDays[0];
	}
	opt1 = getTheOption(expPrise,optType,1);
	if(opt1 == NULL){
		val1 = 0;
	}else{
		val1 = opt0->timeValue/lftDays[1];
	}
	opt2 = getTheOption(expPrise,optType,2);
	if(opt2 == NULL){
		val2 = 0;
	}else{
		val2 = opt0->timeValue/lftDays[2];
	}
	opt3 = getTheOption(expPrise,optType,3);
	if(opt3 == NULL){
		val3 = 0;
	}else{
		val3 = opt3->timeValue/lftDays[3];
	}
	int val = val0;
	result = opt0;
	if(val<val1){
		val = val1;
		result = opt1;
	}
	if(val < val2){
		val = val2;
		result = opt2;
	}
	if(val < val3){
		val = val3;
		result = opt3;
	}
	if(val<0 || val ==0){
		return NULL;		
	}
	return result;
}

int optStratege::setOpnInterest(etfOptList * list){

	if(list == NULL){
		return FUNCTION_ERROR;
	}
	opnIntList = list;
	setCurOpnIntPrise();
	return ansPrepare();

}


unsigned int optStratege::getAtMnyExePrise()
{
	unsigned int exePrise =0;

	if((etfPrs10k)%500 < 250){
		exePrise = etfPrs10k - etfPrs10k%500;
	}else{
		exePrise = etfPrs10k - etfPrs10k%500 + 500;
	}
	return exePrise;
}

unsigned int optStratege::ansPrsCurve(int result [4][3][MAX_LEVEL], char optType)
{
	unsigned int totPrise = 0;
	if(optType == OPTION_TYPE_CALL){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnCalQuantity[life][atMoney][level] == 0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnCalInterest[life][atMoney][level];
				val = opnCalInterest[life][atMoney][level]->curPrise * opnCalQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totPrise += val;
			}
		}
	}
	}else if(optType == OPTION_TYPE_PUT){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnPutQuantity[life][atMoney][level] == 0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnPutInterest[life][atMoney][level];
				val = opnPutInterest[life][atMoney][level]->curPrise * opnPutQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totPrise += val;
			}
		}
	}
	}else{
		return 0;
	}
	
	return totPrise;	
}


unsigned int optStratege::ansQtyCurve(int result[4][3][MAX_LEVEL],char optType)
{
	unsigned int totQuantity = 0;
	if(optType == OPTION_TYPE_CALL){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				result[life][atMoney][level] = opnCalQuantity[life][atMoney][level];
				totQuantity += opnCalQuantity[life][atMoney][level];
			}
		}
	}
	}else if(optType == OPTION_TYPE_PUT){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				result[life][atMoney][level] = opnPutQuantity[life][atMoney][level];
				totQuantity += opnPutQuantity[life][atMoney][level];
			}
		}
	}
	}else{
		return 0;
	}
	
	return totQuantity;
}
unsigned int optStratege::ansTVCurve(int result[4][3][MAX_LEVEL], char optType)
{
	unsigned int totTV = 0;

	if(optType == OPTION_TYPE_CALL){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnCalQuantity[life][atMoney][level] ==0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnCalInterest[life][atMoney][level];
				val = opnCalInterest[life][atMoney][level]->getTV(etfPrs10k);
				val = val*opnCalQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totTV += val;
			}
		}
	}
	}else if(optType == OPTION_TYPE_PUT){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnPutQuantity[life][atMoney][level] ==0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnPutInterest[life][atMoney][level];
				val = opnPutInterest[life][atMoney][level]->getTV(etfPrs10k);
				val = val*opnPutQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totTV += val;
			}
		}
	}
	}else{
		return 0;
	}
	
	return totTV;
}
unsigned int optStratege::ansRVCurve(int result[4][3][MAX_LEVEL], char optType)
{
	unsigned int totRV = 0;

	if(optType == OPTION_TYPE_CALL){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnCalQuantity[life][atMoney][level] ==0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnCalInterest[life][atMoney][level];
				val = opnCalInterest[life][atMoney][level]->getRV(etfPrs10k);
				val = val*opnCalQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totRV += val;
			}
		}
	}
	}else if(optType == OPTION_TYPE_PUT){
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(opnPutQuantity[life][atMoney][level] ==0){
					result[life][atMoney][level] = 0;
					continue;
				}
				int val = 0;
				//unsigned int idx = 0;
				//idx = opnPutInterest[life][atMoney][level];
				val = opnPutInterest[life][atMoney][level]->getRV(etfPrs10k);
				val = val*opnPutQuantity[life][atMoney][level];
				result[life][atMoney][level] = val;
				totRV += val;
			}
		}
	}
	}else{
		return 0;
	}
	
	return totRV;
}
unsigned int optStratege::getShfDelta(char optType)
{
	if(optType == OPTION_TYPE_CALL){
		return prmShfCalPstDelta;
	}else if(optType == OPTION_TYPE_PUT){
		return prmShfPutPstDelta;
	}else{
		return 0;
	}
}



unsigned int optStratege::ansPrepare()
{
	unsigned int atMnyPrise = getAtMnyExePrise();
	unsigned int optLife;
	memset(opnPutInterest,0,sizeof(opnPutInterest));
	memset(opnPutQuantity,0,sizeof(opnPutQuantity));
	memset(opnCalInterest,0,sizeof(opnCalInterest));
	memset(opnCalQuantity,0,sizeof(opnCalQuantity));
	
	for(unsigned int life = 0;life<4;life++){
		//unsigned int index = 0;
		for(etfOptList::iterator it = calOptPrsList[life]->begin();it!= calOptPrsList[life]->end();it++){
//			std::cout<<"testing life/"<<life<<"  atMoneyPrise/"<<atMnyPrise;
//			std::cout<<"	InOutMoney/"<<it->getInOutMoney(atMnyPrise)<<"	level/"<<it->getLevel(atMnyPrise)<<std::endl;

			if(it->getLevel(atMnyPrise) == 0 ){
				opnCalInterest[life][AT_MONEY_INDEX][0] = &(*it);
			}else{
				opnCalInterest[life][it->getInOutMoney(atMnyPrise)][it->getLevel(atMnyPrise)-1] = &(*it);
			
			}
			//index++;
		}
		
		//index = 0;
		for(etfOptList::iterator it = putOptPrsList[life]->begin();it!= putOptPrsList[life]->end();it++){
//			std::cout<<"testing life/"<<life<<"  atMoneyPrise/"<<atMnyPrise;
//			std::cout<<"	InOutMoney/"<<it->getInOutMoney(atMnyPrise)<<"	level/"<<it->getLevel(atMnyPrise)<<std::endl;
			if(it->getLevel(atMnyPrise) == 0 ){
				opnPutInterest[life][AT_MONEY_INDEX][0] = &(*it);
			}else{
				unsigned int tmpMoney = it->getInOutMoney(atMnyPrise);
				unsigned int tmpLevel = it->getLevel(atMnyPrise)-1;
				opnPutInterest[life][tmpMoney][tmpLevel] = &(*it);
			
			}
			//index++;
		}
	}
	for(etfOptList::iterator it = opnIntList->begin();it!=opnIntList->end();it++){
		optLife = it->getLife(expMonth[0]);

		//int temp = getOptIndex(it->exePrise, it->optType, optLife);
		//if(temp <0){
		//	return FUNCTION_ERROR;
		//}
		unsigned int level = 0;
		unsigned int atMoney = it->getInOutMoney(atMnyPrise);
		
		level = it->getLevel(atMnyPrise) -1;
		if(it->optType == OPTION_TYPE_CALL){
			//opnCalInterest[optLife][atMoney][level] = temp;
			opnCalQuantity[optLife][atMoney][level] += it->opnInterest;
		}else if(it->optType == OPTION_TYPE_PUT){
			//opnPutInterest[optLife][atMoney][level] = temp;
			opnPutQuantity[optLife][atMoney][level] += it->opnInterest;
		}else{
			return FUNCTION_ERROR;
		}
		
	}
	return FUNCTION_SUCCESS;	
}

int prnAnsMatrix(int result[4][3][MAX_LEVEL], const char* info)
{
	std::cout<<std::string(info)<<"-----------------------------"<< std::endl;
	for(unsigned int j= 0;j<4;j++){
		std::cout<<"life"<<j<<": "<< std::endl;
		std::cout<<"at money: 	";
		for(unsigned int i=0;i<MAX_LEVEL;i++){
			std::cout<<result[j][AT_MONEY_INDEX][i]<<"	";
		}
		std::cout<<std::endl;
		std::cout<<" in money: 	";
		for(unsigned int i=0;i<MAX_LEVEL;i++){
			std::cout<<result[j][IN_MONEY_INDEX][i]<<"	";
		}
		std::cout<<std::endl;	
		std::cout<<" out money: 	";
		for(unsigned int i=0;i<MAX_LEVEL;i++){
			std::cout<<result[j][OUT_MONEY_INDEX][i]<<"	";
		}
		std::cout<<std::endl;		
	}
	
	return FUNCTION_SUCCESS;
}
unsigned int optStratege::ansRatio(int result [4][3][MAX_LEVEL], int total)
{
	for(unsigned int life=0;life<4;life++){
		for(unsigned int atMoney = 0;atMoney<3;atMoney++){
			for(unsigned int level = 0;level<MAX_LEVEL;level++){
				if(result[life][atMoney][level] == 0) {
					continue;
				}else {
					result[life][atMoney][level] = result[life][atMoney][level] *1000/total;
				}
			}
		}
	}
	return total;

}
unsigned int optStratege::ansPrfCurve(int result [4][3][MAX_LEVEL])
{
	unsigned int savEtfPrise = etfPrs10k;
	int totRV = 0;
	unsigned int atMnyPrise = getAtMnyExePrise();
	int dumy[4][3][MAX_LEVEL];

	etfPrs10k = atMnyPrise;
	
	int totPrise = ansPrsCurve(dumy, OPTION_TYPE_CALL) + ansPrsCurve(dumy, OPTION_TYPE_PUT);
	totRV = ansRVCurve(dumy,OPTION_TYPE_CALL) + ansRVCurve(dumy,OPTION_TYPE_PUT);
	result[0][AT_MONEY_INDEX][0] = totPrise - totRV;
	for(unsigned int i=0;i<MAX_LEVEL;i++){
		etfPrs10k += 500;
		totRV = ansRVCurve(dumy,OPTION_TYPE_CALL) + ansRVCurve(dumy,OPTION_TYPE_PUT);
		result[0][OUT_MONEY_INDEX][i] = totPrise - totRV;
	}
	etfPrs10k = atMnyPrise;
	for(unsigned int i=0;i<MAX_LEVEL;i++){
		etfPrs10k -= 500;
		totRV = ansRVCurve(dumy,OPTION_TYPE_CALL) + ansRVCurve(dumy,OPTION_TYPE_PUT);
		result[0][IN_MONEY_INDEX][i] = totPrise - totRV;
	}
	etfPrs10k = savEtfPrise;
	return atMnyPrise;
}

unsigned int optStratege::ansDpsCurve(int result [4][3][MAX_LEVEL], unsigned int delta)
{
	//1. get TV for each level.
	int tvRefMatrix[4][3][MAX_LEVEL];
	//unsigned int calIndex, putIndex;
	unsigned int savEtfPrise = etfPrs10k;
	memset(tvRefMatrix,0,sizeof(tvRefMatrix));
	//at money tv
	

	for(unsigned int life = 0;life <4;life++){
		int calTV = 0;
		int putTV = 0;		
	//}
	//in money tv
		for(unsigned int inOutMoney = 0;inOutMoney < 3;inOutMoney ++){
			putTV = tvRefMatrix[life][AT_MONEY_INDEX][0]/2;
			calTV = tvRefMatrix[life][AT_MONEY_INDEX][0] - putTV;
			unsigned int grade=100;
			for(unsigned int level = 0;level < MAX_LEVEL;level ++){
				if(opnCalInterest[life][inOutMoney][level] != 0){
					calTV = opnCalInterest[life][inOutMoney][level]->getTV(etfPrs10k);
					calTV = (calTV>0)?calTV:0;
				}else{
					if(calTV>0){
						calTV = calTV*grade/100;
					}
					
				}
				if(opnPutInterest[life][inOutMoney][level] != 0){
					putTV = opnPutInterest[life][inOutMoney][level]->getTV(etfPrs10k);
					putTV = (putTV>0)?putTV:0;
				}else{
					if(putTV>0){
						putTV = putTV*grade/100;
					}
				}
				tvRefMatrix[life][inOutMoney][level] =	putTV + calTV;
				if(level == 1){
					int tmp = tvRefMatrix[life][inOutMoney][1]*100/tvRefMatrix[life][inOutMoney][0];
					grade = (tmp>0)?tmp:(0-tmp);
				}else if(level >1){
					int tmp = tvRefMatrix[life][inOutMoney][level]*100/tvRefMatrix[life][inOutMoney][level-1];
					tmp = (tmp>0)? tmp:(0-tmp);
					grade +=tmp;
					grade >>=1;
				}
			}	
		}
	}
	
	setCurOpnIntPrise();
	result[0][AT_MONEY_INDEX][0] = getTotDeposit();
	
	for(unsigned int i = 0; i <MAX_LEVEL;i++){
		if(etfPrs10k <= delta){
			etfPrs10k = 1;
		}else{
			etfPrs10k -=delta;
		}
		for(etfOptList::iterator it = opnIntList->begin();it!=opnIntList->end();it++){
			unsigned int tmpAtMoney = it->getInOutMoney(etfPrs10k);
			unsigned int tmpLevel = it->getLevel(etfPrs10k);
			
			tmpLevel = (tmpLevel == 0)?tmpLevel:(tmpLevel-1);
			tmpLevel = (tmpLevel>=MAX_LEVEL)?(MAX_LEVEL-1):tmpLevel;
			unsigned int tmpLife = it->getLife(expMonth[0]);
			it->curPrise = it->getRV(etfPrs10k)+prdTV(it->optType,tvRefMatrix[tmpLife][tmpAtMoney][tmpLevel],etfPrs10k - savEtfPrise);
		}
		result[0][IN_MONEY_INDEX][i] = getTotDeposit();
	}
		
	etfPrs10k = savEtfPrise;
	for(unsigned int i = 0; i <MAX_LEVEL;i++){
		etfPrs10k +=delta;
		for(etfOptList::iterator it = opnIntList->begin();it!=opnIntList->end();it++){
			unsigned int tmpAtMoney = it->getInOutMoney(etfPrs10k);
			unsigned int tmpLevel = it->getLevel(etfPrs10k);
			tmpLevel = (tmpLevel == 0)?tmpLevel:(tmpLevel-1);
			unsigned int tmpLife = it->getLife(expMonth[0]);
			it->curPrise = it->getRV(etfPrs10k)+prdTV(it->optType,tvRefMatrix[tmpLife][tmpAtMoney][tmpLevel],etfPrs10k - savEtfPrise);
		}
		result[0][OUT_MONEY_INDEX][i] = getTotDeposit();
	}
	
	etfPrs10k = savEtfPrise;
	return result[0][AT_MONEY_INDEX][0];

}
unsigned int optStratege::prdTV(char optType, unsigned int tvRef, int delta)
{
	return tvRef>>1;
}
