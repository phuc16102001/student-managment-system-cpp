#ifndef _ACCOUNT_HEADER_
#define _ACCOUNT_HEADER_

#include "Constant.h"
#include "CharPointer.h"

struct Account {
	char ID[9];
	char* lastName;
	char* firstName;
	bool gender;
	char dob[11];
	char* password;
	int accountType;
};

struct AccountList {
	Account account;
	AccountList* nextAccount = nullptr;
};

bool importAccountFromStorage(AccountList*& accountList);						//Import from .txt
bool importAccountFromCSV(char* path, AccountList*& accountList);				//Import from .csv
bool findAccountID(char* accountID, AccountList* accountList, Account& result);	//Find accountID and return found
bool checkPassword(char* passwordInput, Account account);						//Return correct

#endif