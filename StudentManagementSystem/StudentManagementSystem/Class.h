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

bool importClassFromStorage(AccountList* accountList, ClassList*& classList);
bool saveClassToStorage(ClassList* classList);
bool insertClassToClassList(ClassList*& classList, Class* classData);
void clearClassList(ClassList*& classList);
int getLengthClassList(ClassList* list);
Class* findClassName(string className, ClassList* classList);

#endif