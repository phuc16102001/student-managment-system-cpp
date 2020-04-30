#include "Class.h"

bool importClassFromStorage(AccountList* accountList, ClassList*& classList) {
	//Open file
	fstream fin(_classStorage, ios::in);
	if (!fin.is_open()) return false;

	while (!fin.eof()) {
		//Read data input
		string tempName;
		getline(fin, tempName);
		if (tempName == "") break;
	
		Class* newClass = new Class;
		newClass->className = tempName;
		int numberOfStudent;
		fin >> numberOfStudent;
		fin.ignore();

		//Read student list
		AccountList* newAccountList = nullptr;
		for (int i = 0; i < numberOfStudent; i++) {
			string accountID;
			getline(fin, accountID);
			Account* account = findAccountID(accountID, accountList);
			if (account) {
				insertAccountToAccountList(newAccountList, account);
			}
		}
		newClass->accountList = newAccountList;

		//Insert
		insertClassToClassList(classList, newClass);
	}
	return true;
}

bool saveClassToStorage(ClassList* classList) {
	//Open file
	fstream fout(_classStorage, ios::out);
	if (!fout.is_open()) return false;

	while (classList != nullptr) {
		//Get accountList of current classList
		AccountList* accountList = classList->classData->accountList;
		int number = getLengthAccountList(accountList);
		fout << classList->classData->className << endl;
		fout << number << endl;

		while (accountList != nullptr) {
			//Witch each account, write down accountID
			fout << accountList->accountData->ID << endl;
			accountList = accountList->nextAccount;
		}

		classList = classList->nextClass;
	}

	fout.close();
	return true;
}

bool insertClassToClassList(ClassList*& classList, Class* classData) {
	if (classList == nullptr) {
		classList = new ClassList;
		classList->classData = classData;
	}
	else {
		ClassList* cur = classList;
		while (cur != nullptr) {
			if (cur->classData->className == classData->className) {
				return false;
			}
			if (cur->nextClass == nullptr) break;
			cur = cur->nextClass;
		}
		cur->nextClass = new ClassList;
		cur = cur->nextClass;
		cur->classData = classData;
	}
	return true;
}

void clearClassList(ClassList*& classList) {
	while (classList != nullptr) {
		ClassList* temp = classList;
		Class* classData = temp->classData;
		classList = classList->nextClass;
		delete classData;
		delete temp;
	}
}

int getLengthClassList(ClassList* list) {
	int count = 0;
	while (list != nullptr) {
		count++;
		list = list->nextClass;
	}
	return count;
}

Class* findClassName(string className, ClassList* classList) {
	if (classList == nullptr) return nullptr;
	while (classList != nullptr) {
		if (classList->classData->className == className) return classList->classData;
		classList = classList->nextClass;
	}
	return nullptr;
}
