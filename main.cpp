#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "etfOption.h"
#include "optStratege.h"
#include "account.h"
#include "datAPI.h"
#include "memory.h"

using namespace std;
int main(int argc, char **argv)
{
	account acc;
	etfOptList calPrsList[4];
	etfOptList putPrsList[4];
	int ansResult[4][3][MAX_LEVEL];
	unsigned int year = 2017;
	unsigned int month = 4;
	unsigned int date = 4;
	unsigned int etf10KPrise = 23430;
	rdOpnInterest(acc);
	prtOptList(acc.opnIntList);
	rdOptPrise(calPrsList,putPrsList,year,month,date);
	/*
	std::cout<<"Print prise list:-----------------------------"<<std::endl;
	prtOptList(calPrsList[0]);
	prtOptList(calPrsList[1]);
	prtOptList(calPrsList[2]);
	prtOptList(calPrsList[3]);
	prtOptList(putPrsList[0]);
	prtOptList(putPrsList[1]);
	prtOptList(putPrsList[2]);
	prtOptList(putPrsList[3]);
	 */
	acc.initial(year,month,date);	
	acc.setEtfStatus(etf10KPrise);	
    acc.setPrsList(calPrsList, putPrsList);
	acc.cycCheck();
	prtOptList(acc.opnIntList);

	cout<<"Total CALL QUANTITY: "<<acc.optS.ansQtyCurve(ansResult,OPTION_TYPE_CALL)<<endl;
	prnAnsMatrix(ansResult,"CALL QUANTITY");
	
	cout<<"Total CALL TV: "<<acc.optS.ansTVCurve(ansResult,OPTION_TYPE_CALL)<<endl;
	prnAnsMatrix(ansResult,"CALL TV");
	
	cout<<"Total CALL RV: "<<acc.optS.ansRVCurve(ansResult,OPTION_TYPE_CALL)<<endl;
	prnAnsMatrix(ansResult,"CALL RV");
	
	cout<<"Total PUT QUANTITY: "<<acc.optS.ansQtyCurve(ansResult,OPTION_TYPE_PUT)<<endl;
	prnAnsMatrix(ansResult,"PUT QUANTITY");
	
	cout<<"Total PUT TV: "<<acc.optS.ansTVCurve(ansResult,OPTION_TYPE_PUT)<<endl;
	prnAnsMatrix(ansResult,"PUT TV");
	
	cout<<"Total PUT RV: "<<acc.optS.ansRVCurve(ansResult,OPTION_TYPE_PUT)<<endl;
	prnAnsMatrix(ansResult,"PUT RV");
	
	cout<<"Total CALL PRISE: "<<acc.optS.ansPrsCurve(ansResult,OPTION_TYPE_CALL)<<endl;
	prnAnsMatrix(ansResult,"CALL PRISE");
	
	cout<<"Total PUT PRISE: "<<acc.optS.ansPrsCurve(ansResult,OPTION_TYPE_PUT)<<endl;
	prnAnsMatrix(ansResult,"PUT PRISE");
	
	cout<<"AT MONEY PRISE: "<<acc.optS.ansPrfCurve(ansResult)<<endl;
	prnAnsMatrix(ansResult,"Profit Curve");

	memset(ansResult,0,sizeof(ansResult));
//	cout<<"Total Deposit : "<<acc.optS.ansDpsCurve(ansResult,500)<<endl;
//	prnAnsMatrix(ansResult,"Deposit Curve");
		memset(ansResult,0,sizeof(ansResult));
	cout<<"Total Deposit : "<<acc.optS.ansDpsCurve(ansResult,30000)<<endl;
	prnAnsMatrix(ansResult,"Deposit Curve");
	char a;
	do{
		/*
		cout<<"option type"<<endl;
		cin>>opt.optType;
		cout<<"exe Prise"<<endl;
		cin>>opt.exePrise;
		cout<<"curent Prise"<<endl;
		cin>>opt.curPrise;
		cout<<"quantity: ";
		cin>>qnt;
		cout<<"deposit : "<<opt.calDeposit(curEtfPrise)*qnt<<endl;
		 * */
		//cout<<"year";
		//cin>>year;

		cin>>a;
		//cout<<a<<endl;
	}while(a == 'y');
	 
	return 0;
}
