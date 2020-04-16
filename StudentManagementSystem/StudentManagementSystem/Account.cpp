#include "Account.h"

bool importAccountFromStorage(AccountList*& accountList) {
	fstream fin;
	fin.open(_accountStorage, ios::in);
	if (!fin.is_open()) return false;

	AccountList* cur = accountList;
	while (!fin.eof()) {
		Account readAccount;
		fin.get(readAccount.ID, sizeof(readAccount.ID), ',');
		fin.ignore(1, ',');

		readAccount.lastName = readCharPointerUntil(fin, ',');
		fin.ignore(1, ',');

		readAccount.firstName = readCharPointerUntil(fin, ',');
		fin.ignore(1, ',');

		fin >> readAccount.gender;
		fin.ignore(1, ',');

		fin.get(readAccount.dob, sizeof(readAccount.dob), ',');
		fin.ignore(1, ',');

		readAccount.password = readCharPointerUntil(fin, ',');
		fin.ignore(1, ',');

		fin >> readAccount.accountType;
		fin.ignore(1, '\n');

		if (cur == nullptr) {
			accountList = new AccountList;
			cur = accountList;
		}
		else {
			cur->nextAccount = new AccountList;
			cur = cur->nextAccount;
		}
		cur->account = readAccount;
	}

	return true;
}

bool importAccountFromCSV(char* path, AccountList*& accountList) {
	fstream fin;
	fin.open(_data, ios::in);
	if (!fin.is_open()) return false;

	AccountList* cur = accountList;
	while (!fin.eof()) {
		Account readAccount;
		fin.get(readAccount.ID, sizeof(readAccount.ID), ',');
		fin.ignore(1, ',');

		readAccount.lastName = readCharPointerUntil(fin, ',');
		fin.ignore(1, ',');

		readAccount.firstName = readCharPointerUntil(fin, ',');
		fin.ignore(1, ',');

		fin >> readAccount.gender;
		fin.ignore(1, ',');

		fin.get(readAccount.dob, sizeof(readAccount.dob), '\n');


		fin.ignore(1, '\n');

		if (cur == nullptr) {
			accountList = new AccountList;
			cur = accountList;
		}
		else {
			cur->nextAccount = new AccountList;
			cur = cur->nextAccount;
		}
		cur->account = readAccount;
	}

	return true;
}

bool findAccountID(char* accountID, AccountList* accountList, Account &result) {
	while (accountList != nullptr) {
		Account account = accountList->account;
		if (strcmp(account.ID, accountID) == 0) {
			result = account;
			return true;
		}
		accountList = accountList->nextAccount;
	}
	return false;
}

bool checkPassword(char* passwordInput, Account account) {
	if (strcmp(passwordInput, account.password) == 0) return true;
	return false;
}