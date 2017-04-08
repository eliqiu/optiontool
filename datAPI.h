#ifndef DATA_API_H
#define DATA_API_H
#include "etfOption.h"
#include "account.h"

int rdOptPrise(etfOptList *calOptList, etfOptList *putOptList,unsigned int year,unsigned int month, unsigned int date);


int rdOpnInterest(account &acc);

#endif