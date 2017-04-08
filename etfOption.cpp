#include "etfOption.h"
#include <stdio.h>
#include <iostream>

etfOption::etfOption()
{
	dptRatio = 120;
	optUnit = 10000;
	opnInterest = 0;
}

int etfOption::getNxtOption(etfOption * tgt,unsigned int curMonth,unsigned int delta)
{
	if(delta > (EXSISTING_MONTH -1)){
		return FUNCTION_ERROR;
	}
	if(tgt == NULL){
		return FUNCTION_ERROR;
	}
	*tgt = *this;
	if((curMonth == 0) ||(curMonth >12)){
		return FUNCTION_ERROR;
	}
	const unsigned char* pMMT = &MMT[(curMonth-1)*EXSISTING_MONTH];
	for(int i=0;i<(EXSISTING_MONTH-1);i++){
		if(*pMMT == (char)expMonth){
			if((delta+i+1)>EXSISTING_MONTH){
				return FUNCTION_FAIL;
			}
			tgt->expMonth = *(pMMT+delta);
			if(tgt->expMonth<expMonth){
				tgt->expYear++;
			}
			return FUNCTION_SUCCESS;
		}
		pMMT++;
	}
	return FUNCTION_FAIL;
}


int etfOption::getPreOption(etfOption * tgt,unsigned int curMonth, unsigned int delta)
{
	if(delta > (EXSISTING_MONTH -1)){
		return FUNCTION_ERROR;
	}
	if(tgt == NULL){
		return FUNCTION_ERROR;
	}
	*tgt = *this;
	if((curMonth == 0) ||(curMonth >12)){
		return FUNCTION_ERROR;
	}
	const unsigned char* pMMT = &MMT[(curMonth-1)*EXSISTING_MONTH];
	for(unsigned int i=1;i<(EXSISTING_MONTH);i++){
		if(*pMMT == (char)expMonth){
			if(i>delta){
				tgt->expMonth = *(pMMT-delta);
				if(tgt->expMonth > expMonth){
					tgt->expYear--;
				}
				return FUNCTION_SUCCESS;
			}else{
				return FUNCTION_FAIL;
			}
			
		}
		pMMT++;
	}
	return FUNCTION_FAIL;
}

int etfOption::getDpOption(etfOption * tgt, etfOptList * optList){
	if((tgt == NULL)||(optList == NULL)){
		return FUNCTION_ERROR;
	}
	for(etfOptList::iterator it = optList->begin();it!=optList->end();it++){
		if(it->exePrise == exePrise){
			it++;
			if(it == optList->end()){
				return FUNCTION_FAIL;
			}
			*tgt = *it;
			return FUNCTION_SUCCESS;
		}
	}
	
	return FUNCTION_FAIL;
}


int etfOption::getLtOption(etfOption * tgt, etfOptList * optList){
	if((tgt == NULL) || (optList == NULL)){
		return FUNCTION_ERROR;
	}
	for(etfOptList::iterator it = optList->begin();it!=optList->end();it++){
		if(it->exePrise == exePrise){
			if(it == optList->begin()){
				return FUNCTION_FAIL;
			}
			it--;
			*tgt = *it;
			return FUNCTION_SUCCESS;
		}
	}
	
	return FUNCTION_FAIL;
}
unsigned int etfOption::getDeposit(unsigned int curEtfPrise){
	if(curPrise == 0) return 0;
	if(optType == OPTION_TYPE_CALL){
		unsigned int tmp = exePrise;
		if(tmp> curEtfPrise){//out of money
			tmp -= curEtfPrise;
		}else{//in money
			tmp = 0;
		}
		unsigned int a,b; 
		a = curEtfPrise*12/100;
		a = (a>tmp)?(a-tmp):0;
		b = curEtfPrise*7/100;
		a = a>b?a:b;
		return (curPrise + a)*dptRatio/100;
		
	}else if(optType == OPTION_TYPE_PUT){
		unsigned int tmp = exePrise;
	
		if(tmp< curEtfPrise){//out of money
			tmp = curEtfPrise -tmp;
		}else{//in money
			tmp = 0;
		}
		unsigned int a,b; 
		a = curEtfPrise*12/100;
		a = (a>tmp)?(a-tmp):0;
		b = exePrise*7/100;
		a = a>b?a:b;
		tmp = curPrise + a;
		return ((tmp<exePrise)?tmp:exePrise)*dptRatio/100;
	}
	return 0;

}
/*
int etfOption::getCurPrise(etfOptList * optList){

	if(optList == NULL){
		return FUNCTION_ERROR;
	}
	etfOptList::iterator it = optList->begin();	
	if((it->expMonth != expMonth) || (it->expYear != expYear)){
		return FUNCTION_FAIL;
	}
	do{
		if(exePrise == it->exePrise){
			curPrise = it->curPrise;
			return FUNCTION_SUCCESS;
		}
		it++;
	}while(it != optList->end());
	return FUNCTION_FAIL;
}
*/
etfOption * etfOption::findExePrise(etfOptList * optList){
	if(optList == NULL){
		return NULL;
	}
	for(etfOptList::iterator it = optList->begin();it!=optList->end();it++){
		if(it->exePrise == exePrise){
			return &(*it);
		}
	}
	return NULL;
}

etfOption::~etfOption()
{
}

unsigned int etfOption::getLevel(unsigned int atMnyPrise)
{
	
	unsigned int level = (exePrise>atMnyPrise)? (exePrise - atMnyPrise): (atMnyPrise - exePrise);
	level = (level+250)/500;
	if(level>=MAX_LEVEL) level =MAX_LEVEL-1;
	return level;
}

int prtOptList(etfOptList &list){
		std::cout<<"expMonth"<<"	";
		std::cout<<"exePrise"<<"	";	
		std::cout<<"optType"<<"	";	
		std::cout<<"quantity"<<"	";
		std::cout<<"prise"<<"	"<<std::endl;		
	for(etfOptList::iterator it = list.begin();it!=list.end();it++){
		std::cout<<it->expMonth<<"	";
		std::cout<<it->exePrise<<"	";	
		if(it->optType == OPTION_TYPE_CALL){
			std::cout<<"CALL"<<"	";	
		}else if(it->optType == OPTION_TYPE_PUT){
			std::cout<<"PUT"<<"	";	
		}else{
			std::cout<<"WRONG TYPE:"<<it->optType<<"	";
		}
		std::cout<<it->opnInterest<<"	";
		std::cout<<it->curPrise<<"	";
		std::cout<<std::endl;
	}
	return FUNCTION_SUCCESS;
}


int etfOption::getTV(unsigned int curEtfPrise){
	if(curEtfPrise == 0){
		return 0;
	}

	if(optType == OPTION_TYPE_CALL){
		return (curEtfPrise>exePrise)?((int)(exePrise+curPrise) -(int)curEtfPrise):curPrise;
	}else if(optType == OPTION_TYPE_PUT){
		return (curEtfPrise>exePrise)?curPrise:((int)curPrise - (int)(exePrise - curEtfPrise));
	}		
	
	return 0; //can't find correct option
}

int etfOption::getRV(unsigned int curEtfPrise){
	if(optType == OPTION_TYPE_CALL){
		if(exePrise > curEtfPrise) return 0;
		else return (curEtfPrise - exePrise);
	}else if(optType == OPTION_TYPE_PUT){
		if(exePrise <curEtfPrise) return 0;
		else return (exePrise - curEtfPrise);
	}
	return 0;
}
unsigned int etfOption::getInOutMoney(unsigned int curEtfPrise)
{
	unsigned int delta = (curEtfPrise>exePrise)? (curEtfPrise - exePrise): (exePrise-curEtfPrise);
	if(delta<250){
		return OPTION_AT_MONEY;
	}
	if(optType == OPTION_TYPE_CALL){
		return (curEtfPrise>exePrise)? OPTION_IN_MONEY:OPTION_OUT_MONEY;
	}else{
		return (curEtfPrise<exePrise)? OPTION_IN_MONEY:OPTION_OUT_MONEY;		
	}
}
int etfOption::getLife(unsigned int firExeMonth)
{
	if(firExeMonth == 0 || firExeMonth >12){
		return -1;
		std::cout<<"ERROR first EXECUTION MONTH : "<< firExeMonth<<std::endl;
	}
	unsigned int i =0;
	for(;i<4;i++){
		if(expMonth == MMT[(firExeMonth-1)*EXSISTING_MONTH+i]){
			break;
		}
	}
	if( i == 4){
		std::cout<<"ERROR: can't find correct life for :"<<firExeMonth<<" / "<<expMonth<<std::endl;
	}
	return i;
}
