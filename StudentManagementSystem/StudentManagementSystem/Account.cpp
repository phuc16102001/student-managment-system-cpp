#include "Account.h"

bool importAccountFromStorage(AccountList*& accountList) {
	//Open file
	fstream fin(_accountStorage, ios::in);
	if (!fin.is_open()) return false;

	AccountList* cur = nullptr;
	while (!fin.eof()) {
		//Read data input
		Account* newAccount = new Account;
		getline(fin, newAccount->ID);
		getline(fin, newAccount->lastName);
		getline(fin, newAccount->firstName);
		fin >> newAccount->gender;
		fin.ignore();
		getline(fin, newAccount->dob);
		getline(fin, newAccount->password);
		fin >> newAccount->accountType;
		fin.ignore();

		//Insert to list
		insertAccountToAccountList(accountList, newAccount);
	}
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
		fout << nowAccount->accountType;
		if (accountList->nextAccount != nullptr) {
			fout << endl;
		}
		accountList = accountList->nextAccount;
	}
	return true;
}

bool importStudentFromCSV(string path, AccountList*& accountList) {
	//Open file
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;

	//Ignore the first line
	string temp;
	getline(fin, temp);

	AccountList* cur = nullptr;
	while (!fin.eof()) {
		//Read data input
		Account* newAccount = new Account;

		//Number of record
		getline(fin, temp, ',');
		if (temp == "") break;

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
		getline(fin, newAccount->dob);
		newAccount->password = newAccount->dob;

		//Clear all '-' in password
		int pos = 0;
		while ((pos = newAccount->password.find('-')) != -1) {
			newAccount->password.replace(pos, 1, "");
		}

		//Student account
		newAccount->accountType = 2;

		//Insert to list
		insertAccountToAccountList(accountList, newAccount);
	}
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
	return passwordInput == account->password;
}

void outputAccount(Account* account) {
	//Gender string
	string gender = "Female";
	if (account->gender) {
		gender = "Male";
	}

	//Account type string
	string accountType;
	switch (account->accountType) {
	case (0): {
		accountType = "Staff";
		break;
	}
	case (1): {
		accountType = "Lecture";
		break;
	}
	case (2): {
		accountType = "Student";
		break;
	}
	}

	//Output
	cout << "UserID: " << account->ID << endl;
	cout << "Last name: " << account->lastName << endl;
	cout << "First name: " << account->firstName << endl;
	cout << "Gender: " << gender << endl;
	cout << "Date of birth: " << account->dob << endl;
	cout << "Account type: " << accountType << endl;
}

void outputAccountList(AccountList* list) {
	while (list != nullptr) {
		outputAccount(list->accountData);
		list = list->nextAccount;
	}
	cout << endl;
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

void insertAccountToAccountList(AccountList*& accountList, Account* accountData) {
	if (accountList == nullptr) {
		accountList = new AccountList;
		accountList->accountData = accountData;
	}
	else {
		AccountList* cur = accountList;
		while (cur != nullptr && cur->nextAccount != nullptr) {
			cur = cur->nextAccount;
		}
		cur->nextAccount = new AccountList;
		cur = cur->nextAccount;
		cur->accountData = accountData;
	}
}

int changePasswordAccount(string oldPassword, string newPassword, string repeatPassword, Account* account) {

}