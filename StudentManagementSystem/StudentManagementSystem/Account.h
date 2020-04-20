#ifndef _ACCOUNT_HEADER_
#define _ACCOUNT_HEADER_

#include "Constant.h"

struct Account {
	string ID;
	string lastName;
	string firstName;
	bool gender;
	string dob;
	string password;
	int accountType;	//0: staff, 1: lecture, 2:student
};

struct AccountList {
	Account account;
	AccountList* nextAccount = nullptr;
};

void clearAccountList(AccountList*& accountList);									//Clear accountList
bool importAccountFromStorage(AccountList*& accountList);							//Import from .txt
bool saveAccountListToStorage(AccountList* accountList);							//Save accountList to .txt
bool importStudentFromCSV(string path, AccountList*& accountList);					//Import from .csv
bool findAccountID(string accountID, AccountList* accountList, Account& result);	//Find accountID and return found
bool checkPassword(string passwordInput, Account account);							//Return correct if same
void outputAccount(Account account);												//Output 1 account to console
void outputAccountList(AccountList* list);											//Output accountList to console

#endif