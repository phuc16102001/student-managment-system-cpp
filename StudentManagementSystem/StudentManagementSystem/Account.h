#ifndef _ACCOUNT_HEADER_
#define _ACCOUNT_HEADER_

#include "Constant.h"

struct Account {
	string ID;
	string lastName;
	string firstName;
	bool gender;		//0: female, 1: male
	string dob;
	string password;	//One way hash
	int accountType;	//0: staff, 1: lecture, 2:student
};

struct AccountList {
	Account* accountData = nullptr;
	AccountList* nextAccount = nullptr;
};

//test
void clearAccountList(AccountList*& accountList);									//Clear accountList
bool importAccountFromStorage(AccountList*& accountList);							//Import from .txt
bool saveAccountListToStorage(AccountList* accountList);							//Save accountList to .txt
bool importStudentFromCSV(string path, AccountList*& accountList);					//Import from .csv
Account* findAccountID(string accountID, AccountList* accountList);					//Find accountID 
bool checkPassword(string passwordInput, Account* account);							//Return correct if same
void outputAccount(Account* account);												//Output 1 account to console
void outputAccountList(AccountList* list);											//Output accountList to console
void insertAccountToAccountList(AccountList*& accountList, Account* accountData);	//Insert account to the end of accountList
int getLengthAccountList(AccountList* list);										//Get length of accountList
int changePasswordAccount(string oldPassword, string newPassword, string repeatPassword, Account* account); //Change account's password

#endif