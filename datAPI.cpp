#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "account.h"
using namespace std;
int rdOpnInterest(account &acc){
	std::ifstream fin("C:\\Users\\eqiu\\Documents\\Eli\\invest\\Debug\\opnInterest.txt"); 
	//std::ifstream fin("opnInterest.txt"); 
	char line[1024]={0}; 
	unsigned int expMonth = 0;
	unsigned int exePrise = 0;
	unsigned int quantity = 0;
	std::string soptType = "";
	char optType;
	
	unsigned int i =0;
	if(!fin.is_open()){
		cout<<"File read error!!"<<endl;
		return FUNCTION_ERROR;
	}
	while(fin.getline(line, sizeof(line))) 
	{ 
		std::stringstream word(line); 
		word >> expMonth; 
		word >> exePrise; 
		word >> soptType;
		word >> quantity;
		cout <<i<< "	" << expMonth<<"	" << soptType<<"	"<<exePrise<< "	"<<quantity<<std::endl;
		if(soptType == "Call"){
			optType = OPTION_TYPE_CALL;
		}else if(soptType == "Put"){
			optType = OPTION_TYPE_PUT;
		}else{
			cout<<"wrong line\n";
			continue;
		}
		acc.setOpnInterest(2017,expMonth,optType,exePrise*10,quantity);
		i++;

	} 
	fin.clear(); 
	fin.close(); 
	return FUNCTION_SUCCESS;
}

int rdOptPrise(etfOptList *calOptList, etfOptList *putOptList,unsigned int year,unsigned int month, unsigned int date){
	std::ifstream fin("C:\\Users\\eqiu\\Documents\\Eli\\invest\\Debug\\prsList.txt"); 
	//std::ifstream fin("opnInterest.txt"); 
	char line[1024]={0}; 
	std::string soptType = "";
	etfOption optItem;
//	const char * plife = NULL;
	unsigned int life;
	unsigned int expDate = 	optStratege::getExpDate(year, month);
	optItem.expDate = expDate;
	unsigned int exp = expDate>date?0:1;

	unsigned int i =0;
	if(!fin.is_open()){
		cout<<"File read error!!"<<endl;
		return FUNCTION_ERROR;
	}
	//fin.getline(line,sizeof(line));
	while(fin.getline(line, sizeof(line))) 
	{ 
		if(line[0] == 0){
			continue;
		}
		std::stringstream word(line); 
		float prise;
		word >> optItem.expYear;
		word >> optItem.expMonth; 
		word >> optItem.exePrise; 
		optItem.exePrise = optItem.exePrise*10;
		word >> soptType;
		word >> prise;
		optItem.curPrise = ((unsigned int)(prise*100000)+5)/10;
		life = optItem.getLife(month+exp);

		cout <<i<< "	" << optItem.expMonth<<"	" << soptType<<"	"<<optItem.exePrise<< "	"<<optItem.opnInterest<<"	"<<optItem.curPrise<<std::endl;
		if(soptType == "call"){
			optItem.optType = OPTION_TYPE_CALL;
			calOptList[life].push_back(optItem);
		}else if(soptType == "put"){
			optItem.optType = OPTION_TYPE_PUT;
			putOptList[life].push_back(optItem);
		}else{
			cout<<"wrong line\n";
			continue;
		}
		i++;

	} 
	fin.clear(); 
	fin.close(); 
	return FUNCTION_SUCCESS;	
}

