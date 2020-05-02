#include "Display.h"

void displayHeaderUI() {
	cout << "--------------------------------\n";
	cout << "|                              |\n";
	cout << "|  Student Management System   |\n";
	cout << "|                              |\n";
	cout << "--------------------------------\n";
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
		cout << "==========================\n";
		outputAccount(list->accountData);
		list = list->nextAccount;
	}
	cout << endl;
}

void outputClassList(ClassList* classList) {
	while (classList) {
		cout << "+ " << classList->classData->className << endl;
		classList = classList->nextClass;
	}
}

void outputClass(Class* classData) {
	cout << "Members of " << classData->className << ":\n";
	AccountList* accountList = classData->accountList;
	outputAccountList(accountList);
}

void inputHidenText(string& text) {
	text = "";
	char c;
	while (c = _getch()) {
		if (c == 13) {
			//Enter press
			cout << endl;
			return;
		}
		if (c == 8 || c == 127) {
			//Backspace
			if (text.length() > 0) {
				//Still have text
				cout << "\b \b"; //Backward write space then backward
				text.erase(text.length() - 1);
			}
		}
		else {
			//Other key
			cout << "*";
			text += c;
		}
	}
	return;
}

void displayLogin(string& inputAccountID,string& inputPassword) {
	//Header
	displayHeaderUI();
	cout << "Press Ctrl+C to exit\n";

	//Input
	cout << "User ID: ";
	getline(cin, inputAccountID);
	cout << "Password: ";
	inputHidenText(inputPassword);
}

int displayBasicMenu() {
	displayHeaderUI();
	int x;
	cout	<< "1. View profile info\n"
			<< "2. Change password\n"
			<< "3. Function menu\n"
			<< "4. Logout\n"
			<< "Choose one function: ";
	cin		>> x;
	while (x < 1 || x>4) {
		cout << "Please choose again!\n";
		cin >> x;
	}
	return x;
}

void displayChangePassword(Account* account, AccountList* accountListStorage) {
	//Header
	displayHeaderUI();
	
	//Input
	string oldPassword, newPassword, repeatPassword;
	cout << "Old password: ";
	inputHidenText(oldPassword);
	cout << "New password: ";
	inputHidenText(newPassword);
	cout << "Repeat new password: ";
	inputHidenText(repeatPassword);

	//Try to change password
	switch (changePasswordAccount(oldPassword, newPassword, repeatPassword, account)) {
		case (0):
			if (saveAccountListToStorage(accountListStorage)) {
				//Save after change successful
				cout << "Password change successful\n";
			}
			else {
				//Fail to save
				cout << "Fail to open storage\n";
			}
			break;
		case (1):
			//Wrong old password
			cout << "Wrong password\n";
			break;
		case (2):
			//Wrong repeat password
			cout << "Repeat password is not the same\n";
			break;
	}
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("CLS");
}

int displayStaffMenu() {
	displayHeaderUI();
	int x;
	cout	<< "Staff Menu?\n"
			<< "Student:\n"
			<< "1. Find student\n"
			<< "2. Edit student information\n"
			<< "3. Reset password\n\n"
			<< "Class:\n"
			<< "4. Add manual student to a class\n"
			<< "5. Create a class from csv file\n"
			<< "6. Remove student from a class\n"
			<< "7. Move student to another class\n"
			<< "8. View list of classes\n"
			<< "9. View list of students in a class\n\n"
			<< "Course:\n"
			<< "10. Create/Update/Delete/View academic year and semester\n"
			<< "11. Import courses from a semester\n"
			<< "12. Add new course\n"
			<< "13. Edit existing course\n"
			<< "14. Remove course\n"
			<< "15. Remove student from a course\n"
			<< "16. Add student to a course\n"
			<< "17. View list of course in the current semester\n"
			<< "18. View list of students of a course\n"
			<< "19. View attendance list of a course\n"
			<< "20. Create/Update/Delete/View all lecturers\n\n"
			<< "Scoreboard:\n"
			<< "21. Search and view attendance list of a course\n"
			<< "22. Export scoreboard into csv file\n"
			<< "23. Back\n"
			<< "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 23) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayLecturerMenu() {
	displayHeaderUI();
	int x;
	cout << "Lecturer Menu\n";
	cout << "1. View list of courses in the current semester\n"
		 << "2. View list of students of a course\n"
		 << "3. View attendance list of a course\n"
		 << "4. Edit attendances\n"
		 << "5. Import scoreboard\n"
		 << "6. Edit student grade\n"
		 << "7. Scoreboard\n"
		 << "8. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 8) {
		cout << "Please choose again!"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayStudentMenu() {
	displayHeaderUI();
	int x;
	cout << "Student Menu\n";
	cout << "1. Check-in\n"
		 << "2. View check-in result\n"
		 << "3. View schedules\n"
		 << "4. View your scores\n"
		 << "5. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 5) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

void displayProfileInfo(Account* accountDisplay) {
	displayHeaderUI();
	outputAccount(accountDisplay);
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("CLS");
}

void displayEditAccount(AccountList* accountListStorage) {
	///Variable
	string accountID, lastName, firstName, dob;
	bool gender;

	//Header
	displayHeaderUI();
	cout << "Edit a student\n";

	//Input
	cout << "User ID: ";
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);

	if (account == nullptr) {
		//Dont have this account
		cout << "Cannot find this account\n";
		return;
	}

	cout << "Last name: ";
	getline(cin, lastName);
	cout << "First name: ";
	getline(cin, firstName);

	//Gender input
	string genderText;
	gender = 0;
	cout << "Gender: ";
	getline(cin, genderText);

	//LowerCase 
	for (int i = 0; i < genderText.length(); i++) {
		genderText[i] = tolower(genderText[i]);
	}
	if (genderText == "male") {
		gender = 1;
	}

	//Dob input
	cout << "Date of birth: ";
	getline(cin, dob);


	if (editAccount(account, lastName, firstName, gender, dob)) {
		if (saveAccountListToStorage(accountListStorage)) {
			//Successful 
			cout << "Success to edit informaton\n";
		}
		else {
			//Open storage failed
			cout << "Fail to open storage\n";
		}
	}
	else {
		//Not exist
		cout << "Fail to edit information\n";
	}
}

void displayFindStudent(AccountList* accountListStorage) {
	///Variable
	string accountID;

	//Header
	displayHeaderUI();
	cout << "Find a student\n";

	//Input
	cout << "User ID: ";
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);
	if (account == nullptr) {
		cout << "Cannot find this student\n";
	}
	else {
		system("CLS");
		displayHeaderUI();
		outputAccount(account);
	}
}

void displayResetPassword(AccountList* accountListStorage) {
	///Variable
	string accountID;

	//Header
	displayHeaderUI();
	cout << "Reset password\n";

	//Input
	cout << "User ID: ";
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);
	if (account == nullptr) {
		cout << "Cannot find this student\n";
	}
	else {
		resetAccountPassword(account);
		if (saveAccountListToStorage(accountListStorage)) {
			cout << "Reset successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
}

void displayAddManuallyStudentToClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	//Init variable
	string className, accountID;
	Class* classData;
	Account* accountData;

	//Header
	displayHeaderUI();
	cout << "Create class from csv file\n";

	//Input className
	cout << "Class Name: ";
	getline(cin, className);
	classData = findClassName(className, classListStorage);

	//Find class
	if (!classData) {
		cout << "Class does not exist\n";
		return;
	}

	//Input userID
	cout << "UserID: ";
	getline(cin, accountID);

	//Find account
	accountData = findAccountID(accountID, accountListStorage);
	if (!accountData) {
		//Not existed
		string lastName, firstName, dob, genderText;
		bool gender;

		//Input
		cout << "Last name: ";
		getline(cin, lastName);
		cout << "First name: ";
		getline(cin, firstName);
		cout << "Gender: ";
		getline(cin, genderText);
		cout << "Date of birth: ";
		getline(cin, dob);

		//Create new account
		accountData = createAccount(accountID, lastName, firstName, genderText, dob, 2);

		//Add to storage
		insertAccountToAccountList(accountData, accountListStorage);
		saveAccountListToStorage(accountListStorage);
	}

	//Add to student list
	insertAccountToAccountList(accountData, classData->accountList);
	saveClassToStorage(classListStorage);
	cout << "Added successfully\n";
}

void displayRemoveStudentFromClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	string className, studentID;

	//Header
	displayHeaderUI();
	cout << "Remove student from class\n";

	//Input
	cout << "Class Name: ";
	getline(cin, className);

	Class* findClass = findClassName(className, classListStorage);
	if (!findClass) {
		cout << "Class does not existed\n";
		return;
	}

	//Input
	cout << "Student ID: ";
	getline(cin, studentID);

	if (removeAccountFromAccountList(studentID, findClass->accountList)) {
		cout << "Removed successfully\n";
	}
	else {
		cout << "Cannot find this student\n";
	}
}

void displayMoveStudentToAnotherClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	//Variable
	string oldClassName, newClassName, studentID;
	Class* oldClass,* newClass;
	Account* account;

	//Header
	displayHeaderUI();
	cout << "Remove student from class\n";

	//Old class
	cout << "Old class Name: ";
	getline(cin, oldClassName);
	oldClass = findClassName(oldClassName, classListStorage);
	if (!oldClass) {
		cout << "Class does not existed\n";
		return;
	}

	//New class
	cout << "New class Name: ";
	getline(cin, newClassName);
	newClass = findClassName(newClassName, classListStorage);
	if (!newClass) {
		cout << "Class does not existed\n";
		return;
	}

	//Account
	cout << "Student ID: ";
	getline(cin, studentID);
	account = findAccountID(studentID, accountListStorage);

	//If account exist and remove success
	if (removeAccountFromAccountList(studentID, oldClass->accountList) && account) {
		//Insert to new class
		if (insertAccountToAccountList(account, newClass->accountList)) {
			cout << "Changed successfully\n";
			return;
		}
	}

	//Cannot find student neither account nor in class
	cout << "Cannot find this student\n";
}

void displayCreateClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	string className, pathFile;
	AccountList* importList = nullptr;

	//Header
	displayHeaderUI();
	cout << "Create class from csv file\n";

	//Input
	cout << "Class Name: ";
	getline(cin, className);

	//Check if existed
	Class* findClass = findClassName(className, classListStorage);
	if (findClass) {
		cout << "Class existed\n";
		return;
	}

	cout << "Path of .csv file: ";
	getline(cin, pathFile);

	//Import student to importList
	if (importStudentFromCSV(pathFile, importList, accountListStorage)) {
		//Create new class
		Class* newClass = new Class;
		newClass->className = className;
		newClass->accountList = importList;

		//Add class
		if (insertClassToClassList(classListStorage, newClass)) {
			//Save classStorage
			if (saveAccountListToStorage(accountListStorage) && saveClassToStorage(classListStorage)) {
				cout << "Create new class successful\n";
			}
			else {
				//Fail to save account and class
				cout << "Fail to save\n";
			}
		}
	}
	else {
		//Fail to open file csv
		cout << "Fail to open file\n";
	}
}

void displayViewListClasses(ClassList* classListStorage) {
	//Header
	displayHeaderUI();
	cout << "List of classes\n";

	//Output list of classes
	outputClassList(classListStorage);
}

void displayViewListStudentInClass(ClassList* classListStorage){
	//Header
	displayHeaderUI();
	cout << "List of student in class\n";

	//Input
	string className;
	Class* classFind;
	cout << "Class name: ";
	getline(cin, className);

	//Find class
	classFind = findClassName(className, classListStorage);

	//Output class
	if (classFind) {
		outputClass(classFind);
	}
	else {
		cout << "Class does not exist\n";
	}
}