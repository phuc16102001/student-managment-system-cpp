#include "Account.h"

Account* createAccount(string accountID, string lastName, string firstName, string genderString, string dob, string accountTypeString) {
	Account* account = new Account;
	if (!account) return nullptr;

	string accountTypeList[] = { "staff","lecturer","student" };

	//LowerCase genderText
	bool gender = 0;
	for (int i = 0; i < genderString.length(); i++) {
		genderString[i] = tolower(genderString[i]);
	}
	if (genderString == "male") {
		gender = 1;
	}

	//LowerCase accountTypeString
	int accountType = 2;
	for (int i = 0; i < accountTypeString.length(); i++) {
		accountTypeString[i] = tolower(accountTypeString[i]);
	}
	for (int i = 0; i < 3; i++) {
		if (accountTypeList[i] == accountTypeString) {
			accountType = i;
			break;
		}
	}


	//Assign value
	account->ID = accountID;
	account->lastName = lastName;
	account->firstName = firstName;
	account->dob = convertDate(dob);
	account->gender = gender;
	account->password = clearSpecialCharString(account->dob);
	account->password = SHA256(account->password);
	account->accountType = accountType;

	return account;
}

bool importAccountFromStorage(AccountList*& accountList) {
	//Open file
	fstream fin(_accountStorage, ios::in);
	if (!fin.is_open()) return false;

	while (!fin.eof()) {
		//Read data input
		string tempID;
		getline(fin, tempID);
		if (tempID == "") break;

		Account* newAccount = new Account;
		newAccount->ID = tempID;
		getline(fin, newAccount->lastName);
		getline(fin, newAccount->firstName);
		fin >> newAccount->gender;
		fin.ignore();
		getline(fin, newAccount->dob);
		getline(fin, newAccount->password);
		fin >> newAccount->accountType;
		fin.ignore();

		//Insert to list
		insertAccountToAccountList(newAccount, accountList);
	}

	fin.close();
	return true;
}

bool saveAccountListToStorage(AccountList* accountList) {
	//Open file
	fstream fout(_accountStorage, ios::out);
	if (!fout.is_open()) return false;

	while (accountList != nullptr) {
		Account* nowAccount = accountList->accountData;
		fout << nowAccount->ID << endl;
		fout << nowAccount->lastName << endl;
		fout << nowAccount->firstName << endl;
		fout << nowAccount->gender << endl;
		fout << nowAccount->dob << endl;
		fout << nowAccount->password << endl;
		fout << nowAccount->accountType << endl;
		accountList = accountList->nextAccount;
	}

	fout.close();
	return true;
}

bool importStudentFromCSV(string path, AccountList*& accountList, AccountList*& accountListStorage) {
	//Open file
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;

	//Ignore the first line
	string temp;
	getline(fin, temp);

	while (!fin.eof()) {
		//Number of record
		getline(fin, temp, ',');
		if (temp == "") break;

		//Read data input
		string tempID;
		Account* newAccount = new Account;

		//Input data
		getline(fin, newAccount->ID, ',');
		getline(fin, newAccount->lastName, ',');
		getline(fin, newAccount->firstName, ',');

		//Gender
		getline(fin, temp, ',');
		if (temp == "Male") {
			newAccount->gender = true;
		}
		else {
			newAccount->gender = false;
		}

		//Dob and password default
		//Clear all special characters in password and hash
		getline(fin, newAccount->dob);
		newAccount->dob = convertDate(newAccount->dob);
		newAccount->password = clearSpecialCharString(newAccount->dob);
		newAccount->password = SHA256(newAccount->password);

		//Student account
		newAccount->accountType = 2;

		//Insert to list
		Account* findAccount = findAccountID(newAccount->ID, accountListStorage);
		if (findAccount) {
			//If account existed
			delete newAccount;
			newAccount = findAccount;
		}
		else {
			//Not exist
			insertAccountToAccountList(newAccount,accountListStorage);
		}
		insertAccountToAccountList(newAccount,accountList);
	}
	
	fin.close();
	return true;
}

Account* findAccountID(string accountID, AccountList* accountList) {
	while (accountList != nullptr) {
		if (accountList->accountData->ID == accountID) {
			return accountList->accountData;
		}
		accountList = accountList->nextAccount;
	}
	return nullptr;
}

bool checkPassword(string passwordInput, Account* account) {
	//Check if the passwordInput is equal to account password
	return SHA256(passwordInput) == account->password;
}

void clearAccountList(AccountList*& accountList) {
	while (accountList != nullptr) {
		AccountList* temp = accountList;
		Account* account = temp->accountData;
		accountList = accountList->nextAccount;
		delete account;
		delete temp;
	}
}

bool insertAccountToAccountList(Account* accountData, AccountList*& accountList) {
	if (accountList == nullptr) {
		accountList = new AccountList;
		accountList->accountData = accountData;
		accountList->nextAccount = nullptr;
	}
	else {
		AccountList* cur = accountList;
		while (cur != nullptr) {
			if (cur->accountData->ID == accountData->ID) {
				return false;
			}
			if (cur->nextAccount == nullptr) break;
			cur = cur->nextAccount;
		}
		cur->nextAccount = new AccountList;
		cur = cur->nextAccount;
		cur->accountData = accountData;
		cur->nextAccount = nullptr;
	}
	return true;
}

int changePasswordAccount(string oldPassword, string newPassword, string repeatPassword, Account* account) {
	//Old password incorrect
	if (SHA256(oldPassword) != account->password) return 1;
	
	//Repeat password incorrect
	if (repeatPassword != newPassword) return 2;

	//If maximum length is 20
	if (newPassword.length() > 20) return 3;

	//Change password successful
	account->password = SHA256(newPassword);
	return 0;
}

int getLengthAccountList(AccountList* list) {
	//Counter the length of list
	int count = 0;
	while (list != nullptr) {
		//Run until the end
		count++;
		list = list->nextAccount;
	}
	return count;
}

bool editAccount(Account* account, string lastName, string firstName, bool gender, string dob) {
	if (account == nullptr) return false;
	account->lastName = lastName;
	account->firstName = firstName;
	account->gender = gender;
	account->dob = convertDate(dob);

	return true;
}

void resetAccountPassword(Account* account) {
	string dob = account->dob;
	string password = clearSpecialCharString(dob);
	account->password = SHA256(password);
}

bool removeAccountFromAccountList(string accountID, AccountList*& accountList) {
	AccountList* cur = accountList;

	//1st node
	if (cur && cur->accountData->ID == accountID) {
		accountList = accountList->nextAccount;
		delete cur;
		return true;
	}
	
	//Other node
	while (cur && cur->nextAccount) {
		if (cur->nextAccount->accountData->ID == accountID) {
			AccountList* temp = cur->nextAccount;
			cur->nextAccount = cur->nextAccount->nextAccount;
			delete temp;
			return true;
		}
		cur = cur->nextAccount;	
	}

	//Not found
	return false;
}