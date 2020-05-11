#ifndef _CLASS_HEADER_
#define _CLASS_HEADER_

#include "Constant.h"
#include "Account.h"

struct Class {
	string className = "";
	AccountList* accountList = nullptr;
};

struct ClassList {
	Class* classData = nullptr;
	ClassList* nextClass = nullptr;
};

bool importClassFromStorage(AccountList* accountList, ClassList*& classList);		//Import classList from .txt
bool saveClassToStorage(ClassList* classList);										//Save classList to .txt
bool insertClassToClassList(ClassList*& classList, Class* classData);				//Insert a class to classList
void clearClassList(ClassList*& classList);											//Clear all classList (do not clear accountList)
int getLengthClassList(ClassList* list);											//Return length of a classList
Class* findClassName(string className, ClassList* classList);						//Return a class which className

#endif