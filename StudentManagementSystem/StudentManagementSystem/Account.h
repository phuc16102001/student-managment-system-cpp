#ifndef _ACCOUNT_HEADER_
#define _ACCOUNT_HEADER_

#include "Constant.h"
#include "SHA256.h"

struct Account {
	string ID = "";
	string lastName = "";
	string firstName = "";
	bool gender = 0;				//0: female, 1: male
	string dob = "00-00-0000";
	string password = "000000000";	//One way hash
	int accountType = 2;			//0: staff, 1: lecture, 2: student
};

struct AccountList {
	Account* accountData = nullptr;
	AccountList* nextAccount = nullptr;
};

void clearAccountList(AccountList*& accountList);															//Clear accountList
bool importAccountFromStorage(AccountList*& accountList);													//Import from .txt
bool saveAccountListToStorage(AccountList* accountList);													//Save accountList to .txt
bool importStudentFromCSV(string path, AccountList*& accountList, AccountList*& accountListStorage);		//Import from .csv and merge into storage
Account* findAccountID(string accountID, AccountList* accountList);											//Find accountID 
bool checkPassword(string passwordInput, Account* account);													//Return correct if same
void outputAccount(Account* account);																		//Output 1 account to console
void outputAccountList(AccountList* list);																	//Output accountList to console
bool insertAccountToAccountList(AccountList*& accountList, Account* accountData);							//Insert account to the end of accountList (unique id)
int getLengthAccountList(AccountList* list);																//Get length of accountList
int changePasswordAccount(string oldPassword, string newPassword, string repeatPassword, Account* account); //Change account's password
bool editAccount(Account* account, string lastName, string firstName, bool gender, string dob);				//Edit account's data
void resetAccountPassword(Account* account);																//Reset password of an account (change to dob)
string clearSpecialCharString(string input);																//Clear all special character in a string, remain alphabet and number

#endif