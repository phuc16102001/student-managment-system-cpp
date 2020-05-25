#include "Display.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}

void displayHeaderUI() {
	setColor(colorMint); 
	cout << "--------------------------------\n";
	cout << "|                              |\n";
	cout << "|  Student Management System   |\n";
	cout << "|                              |\n";
	cout << "--------------------------------\n";
	setColor(colorWhite);
}

void displayLoadingUI(int percentage) {
	system("CLS");
	displayHeaderUI();
	setColor(colorMint);
	int k=0;
	if (percentage < 100) k = 1;
	if (percentage < 10) k = 2;

	cout << "|             ";
	setColor(colorOrange);
	cout << percentage << "%";
	setColor(colorMint);
	for (int i = 0; i < k; i++) cout << " ";
	cout << "             |\n";

	k = (percentage * 30) / 100;
	cout << "|";
	setColor(colorGreen);
	for (int i=0;i<k;i++) cout << "*";
	setColor(colorMint);
	for (int i = 0; i < 30-k; i++) cout << " ";

	cout << "|\n";
	cout << "--------------------------------\n";
}

void displayCurrentSemester(string semester) {
	setColor(colorOrange);
	cout << "Current semester: " << semester << endl;
	setColor(colorMint);
	cout << "--------------------------------\n";
	setColor(colorWhite);
}

void outputCurrentDate(int date, int month, int year, int hour, int minute) {
	setColor(colorOrange);
	cout << "Current date and time:\n";
	setColor(colorMint);
	cout << "Date: ";
	setColor(colorWhite);
	cout << dateToString(date, month, year) << endl;
	setColor(colorMint);
	cout << "Time: ";
	setColor(colorWhite);
	cout << timeToString(hour,minute) << endl;
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
	setColor(colorMint);
	cout << "UserID: ";
	setColor(colorWhite);
	cout << account->ID << endl;

	setColor(colorMint);
	cout << "Last name: ";
	setColor(colorWhite);
	cout << account->lastName << endl;
	
	setColor(colorMint);
	cout << "First name: ";
	setColor(colorWhite);
	cout << account->firstName << endl;
	
	setColor(colorMint);
	cout << "Gender: ";
	setColor(colorWhite);
	cout << gender << endl;
	
	setColor(colorMint);
	cout << "Date of birth: ";
	setColor(colorWhite);
	cout << account->dob << endl;
	
	setColor(colorMint);
	cout << "Account type: ";
	setColor(colorWhite);
	cout << accountType << endl;
}

void outputAccountList(AccountList* list) {
	while (list != nullptr) {
		setColor(colorOrange);
		cout << "==========================\n";
		setColor(colorWhite);
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

void outputCourse(Course* course) {
	string startDate, endDate, startTime, endTime;
	startDate = dateToString(course->startDate,course->startMonth,course->startYear);
	endDate = dateToString(course->endDate, course->endMonth, course->endYear);
	startTime = timeToString(course->startHour,course->startMinute);
	endTime = timeToString(course->endHour,course->endMinute);

	setColor(colorMint);
	cout << "Course ID: ";
	setColor(colorWhite);
	cout << course->courseID << endl;

	setColor(colorMint); 
	cout << "Course name: ";
	setColor(colorWhite); 
	cout << course->courseName << endl;
	
	setColor(colorMint);
	cout << "Course class: ";
	setColor(colorWhite); 
	cout << course->className << endl;

	setColor(colorMint);
	cout << "Lecturer account: ";
	setColor(colorWhite);
	cout << course->lecturerAccount->ID << endl;

	setColor(colorMint); 
	cout << "Start date: ";
	setColor(colorWhite);
	cout << startDate << endl;

	setColor(colorMint); 
	cout << "End date: ";
	setColor(colorWhite);
	cout << endDate << endl;

	setColor(colorMint); 
	cout << "Start time: ";
	setColor(colorWhite);
	cout << startTime << endl;

	setColor(colorMint); 
	cout << "End time: ";
	setColor(colorWhite);
	cout << endTime << endl;

	setColor(colorMint); 
	cout << "Day of week: ";
	setColor(colorWhite);
	cout << getDayOfWeekString(course->dayOfWeek) << endl;

	setColor(colorMint); 
	cout << "Room: ";
	setColor(colorWhite);
	cout << course->roomName << endl;
}

void outputCourseList(CourseList* courseList) {
	while (courseList != nullptr) {
		setColor(colorOrange);
		cout << "==========================\n";
		setColor(colorWhite);

		outputCourse(courseList->courseData);
		courseList = courseList->nextCourse;
	}
}

void outputScore(Score* score) {
	setColor(colorOrange);
	cout << "Score board of " << score->studentID << ":\n";

	setColor(colorWhite);
	cout << "Midterm: " << score->midScore << "\n";
	cout << "Final: " << score->finalScore << "\n";
	cout << "Bonus: " << score->bonusScore << "\n";
	cout << "Total: " << score->totalScore << "\n";
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
	setColor(colorOrange);
	cout << "Press Ctrl+C to exit\n";
	setColor(colorWhite);

	//Input
	setColor(colorMint);
	cout << "User ID: ";
	setColor(colorWhite);
	getline(cin, inputAccountID);

	setColor(colorMint); 
	cout << "Password: ";
	setColor(colorWhite); 
	inputHidenText(inputPassword);
}

int displayBasicMenu() {
	displayHeaderUI();
	int x;

	setColor(colorGreen);
	cout << "       Basic menu\n";

	setColor(colorWhite);
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

int displayStaffMenu(string semester) {
	displayHeaderUI();
	displayCurrentSemester(semester);
	int x;
	setColor(colorGreen);
	cout << "           Staff Menu\n\n";

	setColor(colorMint);
	cout << "Account:\n";
	setColor(colorWhite);
	cout << "1. Create account\n\n";


	setColor(colorMint);
	cout << "Student:\n";
	setColor(colorWhite);
	cout << "2. Find student\n"
		 << "3. Edit student information\n"
		 << "4. Reset password\n\n";

	setColor(colorMint);
	cout << "Class:\n";
	setColor(colorWhite);
	cout << "5. Add manual student to a class\n"
		 << "6. Create a class from csv file\n"
		 << "7. Remove student from a class\n"
		 << "8. Move student to another class\n"
		 << "9. View list of classes\n"
		 << "10. View list of students in a class\n\n";
		 
	setColor(colorMint);
	cout << "Course:\n";
	setColor(colorWhite);
	cout << "11. Create academic year and semester\n"
		 << "12. Change current academic year and semester\n"
		 << "13. Import courses\n"
		 << "14. Add new course\n"
		 << "15. Edit course\n"
		 << "16. Remove course\n"
		 << "17. Remove student from a course\n"
		 << "18. Add student to a course\n"
		 << "19. View list of courses\n"
		 << "20. View list of students of a course\n"
		 << "21. View check in result of a course\n\n";
		 
	setColor(colorMint);
	cout << "Scoreboard:\n";
	setColor(colorWhite);
	cout << "22. View scoreboard\n"
		 << "23. Export scoreboard into csv file\n"
		 << "24. Back\n";
	cout << "Choose one function: ";
	cin >> x;

	while (x < 1 || x > 24) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayLecturerMenu(string semester) {
	displayHeaderUI();
	displayCurrentSemester(semester);
	int x;

	setColor(colorGreen);
	cout << "           Lecturer Menu\n\n";
	setColor(colorWhite);

	cout << "1. Change current semester\n"
		 << "2. View list of courses\n"
		 << "3. View list of students of a course\n"
		 << "4. View check in of a course\n"
		 << "5. Add student to course\n"
		 << "6. Remove student from course\n"
		 << "7. Import scoreboard\n"
		 << "8. Edit student grade\n"
		 << "9. View scoreboard\n"
		 << "10. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 10) {
		cout << "Please choose again!"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayStudentMenu(string semester) {
	displayHeaderUI();
	displayCurrentSemester(semester);
	int x;

	setColor(colorGreen);
	cout << "Student Menu\n\n";
	setColor(colorWhite);

	cout << "1. Change current academic year and semester\n"
		 << "2. List of courses\n"
		 <<	"3. Check-in\n"
		 << "4. View check-in result of course\n"
		 << "5. View schedules\n"
		 << "6. View scoreboard\n"
		 << "7. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 7) {
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

void displayChangePassword(Account* account, AccountList* accountListStorage) {
	//Header
	displayHeaderUI();

	setColor(colorOrange);
	cout << "Change password\n";
	setColor(colorWhite);

	//Input
	string oldPassword, newPassword, repeatPassword;
	setColor(colorMint);
	cout << "Old password: ";
	setColor(colorWhite);
	inputHidenText(oldPassword);

	setColor(colorMint);
	cout << "New password: ";
	setColor(colorWhite);
	inputHidenText(newPassword);

	setColor(colorMint);
	cout << "Repeat new password: ";
	setColor(colorWhite);
	inputHidenText(repeatPassword);

	//Try to change password
	cout << endl;
	switch (changePasswordAccount(oldPassword, newPassword, repeatPassword, account)) {
	case (0):
		if (saveAccountListToStorage(accountListStorage)) {
			//Save after change successful
			setColor(colorGreen);
			cout << "Password changed successful\n";
		}
		else {
			//Fail to save
			setColor(colorRed);
			cout << "Fail to open storage\n";
		}
		break;
	case (1):
		//Wrong old password
		setColor(colorRed);
		cout << "Wrong password\n";
		break;
	case (2):
		//Wrong repeat password
		setColor(colorRed);
		cout << "Repeat password is not the same\n";
		break;
	case (3):
		//Maximum length is 20
		setColor(colorRed);
		cout << "Maximum length is 20\n";
		break;
	}

	setColor(colorWhite);
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("CLS");
}

void displayCreateAccount(AccountList*& accountListStorage) {
	//Header
	displayHeaderUI();
	cout << "Create account\n";

	string accountID;
	setColor(colorOrange);
	cout << "UserID: ";
	setColor(colorWhite);
	getline(cin, accountID);

	Account* accountData = findAccountID(accountID, accountListStorage);
	if (accountData != nullptr) {
		cout << "Account existed\n";
		return;
	}

	string lastName, firstName, dob, genderString, accountTypeString;
	setColor(colorOrange);
	cout << "Last name: ";
	setColor(colorWhite);
	getline(cin, lastName);
	
	setColor(colorOrange); 
	cout << "First name: ";
	setColor(colorWhite);
	getline(cin, firstName);
	
	setColor(colorOrange); 
	cout << "Gender (Male/Female): ";
	setColor(colorWhite);
	getline(cin, genderString);
	
	setColor(colorOrange); 
	cout << "Date of birth (DD-MM-YYYY): ";
	setColor(colorWhite);
	getline(cin, dob);
	
	setColor(colorOrange); 
	cout << "Account type (Staff, Lecturer, Student): ";
	setColor(colorWhite);
	getline(cin, accountTypeString);

	accountData = createAccount(accountID, lastName, firstName, genderString, dob, accountTypeString);
	if (insertAccountToAccountList(accountData, accountListStorage)) {
		if (saveAccountListToStorage(accountListStorage)) {
			setColor(colorGreen);
			cout << "Created account successfully\n";
		}
		else {
			setColor(colorRed);
			cout << "Fail to open file\n";
		}
	}
	else {
		setColor(colorRed);
		cout << "Fail to create account\n";
	}

	setColor(colorWhite);
}

void displayEditAccount(AccountList* accountListStorage) {
	///Variable
	string accountID, lastName, firstName, dob, genderText;
	bool gender;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Edit a student\n";
	cout << "Let blank if unchange\n";
	setColor(colorWhite);

	//Input
	setColor(colorMint); 
	cout << "User ID: ";

	setColor(colorWhite);
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);

	if (account == nullptr) {
		//Dont have this account
		setColor(colorRed);
		cout << "Cannot find this account\n";
		setColor(colorWhite);
		return;
	}

	cout << endl;

	setColor(colorOrange);
	cout << "Account found!\n";
	outputAccount(account);

	cout << endl;
	setColor(colorOrange);
	cout << "Edit information\n";

	//Last name
	setColor(colorMint); 
	cout << "Last name: ";
	setColor(colorWhite);
	getline(cin, lastName);
	if (lastName == "") {
		lastName = account->lastName;
	}

	//First name
	setColor(colorMint);
	cout << "First name: ";
	setColor(colorWhite);
	getline(cin, firstName);
	if (firstName == "") {
		firstName = account->firstName;
	}

	//Gender
	setColor(colorMint);
	cout << "Gender: ";
	setColor(colorWhite);
	getline(cin, genderText);

	//LowerCase 
	for (int i = 0; i < genderText.length(); i++) {
		genderText[i] = tolower(genderText[i]);
	}

	gender = account->gender;
	if (genderText == "male") {
		gender = 1;
	}
	else if (genderText == "female") {
		gender = 0;
	}

	//Dob input
	setColor(colorMint);
	cout << "Date of birth: ";
	setColor(colorWhite);
	getline(cin, dob);
	if (dob == "") {
		dob = account->dob;
	}

	if (editAccount(account, lastName, firstName, gender, dob)) {
		if (saveAccountListToStorage(accountListStorage)) {
			//Successful 
			setColor(colorGreen);
			cout << "Success to edit informaton\n";
		}
		else {
			//Open storage failed
			setColor(colorRed);
			cout << "Fail to open storage\n";
		}
	}
	else {
		//Not exist
		setColor(colorRed);
		cout << "Fail to edit information\n";
	}
	setColor(colorWhite);
}

void displayFindStudent(AccountList* accountListStorage) {
	///Variable
	string accountID;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Find a student\n";
	setColor(colorWhite);

	//Input
	setColor(colorMint);
	cout << "User ID: ";
	setColor(colorWhite);
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);
	if (account == nullptr) {
		setColor(colorRed);
		cout << "Cannot find this student\n";
	}
	else {
		system("CLS");
		displayHeaderUI();
		outputAccount(account);
	}
	setColor(colorWhite);
}

void displayResetPassword(AccountList* accountListStorage) {
	///Variable
	string accountID;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Reset password\n";
	
	//Input
	setColor(colorMint);
	cout << "User ID: ";

	setColor(colorWhite);
	getline(cin, accountID);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);
	if (account == nullptr) {
		setColor(colorRed);
		cout << "Cannot find this student\n";
		setColor(colorWhite);
		return;
	}

	resetAccountPassword(account);
	if (saveAccountListToStorage(accountListStorage)) {
		setColor(colorGreen);
		cout << "Reset successfully\n";
	}
	else {
		setColor(colorRed);
		cout << "Fail to open file\n";
	}

	setColor(colorWhite);
}

void displayAddManuallyStudentToClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	//Init variable
	string className, accountID;
	Class* classData;
	Account* accountData;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Add student to class\n";
	setColor(colorWhite);

	//Input className
	setColor(colorMint);
	cout << "Class Name: ";
	
	setColor(colorWhite);
	getline(cin, className);
	classData = findClassName(className, classListStorage);

	//Find class
	if (!classData) {
		setColor(colorRed);
		cout << "Class does not exist\n";
		setColor(colorWhite);
		return;
	}

	//Input userID
	setColor(colorMint);
	cout << "UserID: ";
	setColor(colorWhite);
	getline(cin, accountID);

	//Find account
	accountData = findAccountID(accountID, accountListStorage);
	if (!accountData) {
		//Not existed
		string lastName, firstName, dob, genderString;
		bool gender;

		//Input
		setColor(colorMint);
		cout << "Last name: ";
		setColor(colorWhite);
		getline(cin, lastName);

		setColor(colorMint);
		cout << "First name: ";
		setColor(colorWhite);
		getline(cin, firstName);

		setColor(colorMint);
		cout << "Gender (Male/Female): ";
		setColor(colorWhite);
		getline(cin, genderString);

		setColor(colorMint);
		cout << "Date of birth (DD-MM-YYYY): ";
		setColor(colorWhite); 
		getline(cin, dob);

		//Create new account
		accountData = createAccount(accountID, lastName, firstName, genderString, dob, "Student");

		//Add to storage
		insertAccountToAccountList(accountData, accountListStorage);
		saveAccountListToStorage(accountListStorage);
	}

	//Add to student list
	insertAccountToAccountList(accountData, classData->accountList);
	saveClassToStorage(classListStorage);
	setColor(colorGreen);
	cout << "Added successfully\n";
	setColor(colorWhite);
}

void displayRemoveStudentFromClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	string className, studentID;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Remove student from class\n";
	setColor(colorWhite);

	//Input
	setColor(colorMint);
	cout << "Class Name: ";
	setColor(colorWhite);
	getline(cin, className);

	Class* findClass = findClassName(className, classListStorage);
	if (!findClass) {
		setColor(colorRed);
		cout << "Class does not existed\n";
		setColor(colorWhite);
		return;
	}

	//Input
	setColor(colorMint);
	cout << "Student ID: ";
	setColor(colorWhite);
	getline(cin, studentID);

	if (removeAccountFromAccountList(studentID, findClass->accountList)) {
		if (saveClassToStorage(classListStorage)) {
			setColor(colorGreen);
			cout << "Removed successfully\n";
			setColor(colorWhite);
		}
		else {
			setColor(colorRed);
			cout << "Fail to open file\n";
			setColor(colorWhite);
		}
	}
	else {
		setColor(colorRed);
		cout << "Cannot find this student\n";
		setColor(colorWhite);
	}
}

void displayMoveStudentToAnotherClass(AccountList*& accountListStorage, ClassList*& classListStorage) {
	//Variable
	string oldClassName, newClassName, studentID;
	Class* oldClass,* newClass;
	Account* account;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Remove student from class\n";
	setColor(colorWhite);

	//Old class
	setColor(colorMint);
	cout << "Old class Name: ";
	setColor(colorWhite);
	getline(cin, oldClassName);
	
	oldClass = findClassName(oldClassName, classListStorage);
	if (!oldClass) {
		setColor(colorRed);
		cout << "Class does not existed\n";
		setColor(colorWhite);
		return;
	}

	//New class
	setColor(colorMint);
	cout << "New class Name: ";
	setColor(colorWhite);
	getline(cin, newClassName);

	newClass = findClassName(newClassName, classListStorage);
	if (!newClass) {
		setColor(colorRed);
		cout << "Class does not existed\n";
		setColor(colorWhite);
		return;
	}

	//Account
	setColor(colorMint);
	cout << "Student ID: ";
	setColor(colorWhite);
	getline(cin, studentID);
	account = findAccountID(studentID, accountListStorage);

	if (account == nullptr) {
		setColor(colorRed);
		cout << "Account not existed\n";
		setColor(colorWhite);
		return;
	}

	if (removeAccountFromAccountList(studentID, oldClass->accountList) && insertAccountToAccountList(account, newClass->accountList)) {
		if (saveClassToStorage(classListStorage)) {
			setColor(colorGreen);
			cout << "Changed successfully\n";
			setColor(colorWhite);
		}
		else {
			setColor(colorRed);
			cout << "Fail to open file\n";
			setColor(colorWhite);
		}
	}
	else {
		setColor(colorRed);
		cout << "Moved fail\n";
		setColor(colorWhite);
	}
}

void displayImportClassFromCSV(AccountList*& accountListStorage, ClassList*& classListStorage) {
	string className, pathFile;
	AccountList* importList = nullptr;

	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "Create class from csv file\n";
	setColor(colorWhite);

	//Input
	setColor(colorMint);
	cout << "Class Name: ";
	setColor(colorWhite);
	getline(cin, className);

	//Check if existed
	Class* findClass = findClassName(className, classListStorage);
	if (findClass) {
		setColor(colorRed);
		cout << "Class existed\n";
		setColor(colorWhite);
		return;
	}

	setColor(colorMint);
	cout << "Path of .csv file: ";
	setColor(colorWhite);
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
				setColor(colorGreen);
				cout << "Create new class successful\n";
				setColor(colorWhite);
			}
			else {
				//Fail to save account and class
				setColor(colorRed);
				cout << "Fail to save\n";
				setColor(colorWhite);
			}
		}
	}
	else {
		//Fail to open file csv
		setColor(colorRed);
		cout << "Fail to open file\n";
		setColor(colorWhite);
	}
}

void displayViewListClasses(ClassList* classListStorage) {
	//Header
	displayHeaderUI();
	setColor(colorOrange);
	cout << "List of classes\n";
	setColor(colorWhite);

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

void displayCreateNewAcademicYearSemester() {
	displayHeaderUI();

	string academicYear, semester;
	setColor(colorOrange);
	cout << "Create academic year and semester\n";
	setColor(colorWhite);

	setColor(colorMint);
	cout << "Academic year: ";
	setColor(colorWhite);
	getline(cin, academicYear);
	
	setColor(colorMint);
	cout << "Semester: ";
	setColor(colorWhite);
	getline(cin, semester);
	
	if (createSemester(academicYear, semester)) {
		setColor(colorGreen);
		cout << "Created successfully\n";
		setColor(colorWhite);
	}
	else {
		setColor(colorRed);
		cout << "Fail to create semester\n";
		setColor(colorWhite);
	}
}

void displayChangeAcademicYearSemester(string& currentSemester, AccountList* accountListStorage, CourseList*& courseListStorage) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	
	setColor(colorOrange);
	cout << "Change academic year and semester\n";
	setColor(colorWhite);

	string academicYear, semester;
	setColor(colorMint);
	cout << "Academic year: "; 
	setColor(colorWhite);
	getline(cin, academicYear);
	
	setColor(colorMint);
	cout << "Semester: ";
	setColor(colorWhite);
	getline(cin, semester);
	
	if (changeSemester(academicYear, semester, currentSemester, accountListStorage, courseListStorage)) {
		setColor(colorGreen);
		cout << "Change successfully\n";
		setColor(colorWhite);
	}
	else {
		setColor(colorRed);
		cout << "Cannot find this academic year and semester\n";
		setColor(colorWhite);
	}
}

void displayRemoveCourse(string currentSemester, CourseList*& courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Remove course\n";

	string courseID, className;
	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);

	if (removeCourseFromCourseList(courseID, className,courseList)) {
		if (saveCourseToStorage(currentSemester, courseList)) {
			cout << "Remove successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
	else {
		cout << "Cannot find this course\n";
	}
}

void displayAddNewCourse(string currentSemester, AccountList* accountList, ClassList* classList, CourseList*& courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	cout << "Add new course\n";
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}

	string courseID, courseName, className, lecturerID, startDate, endDate, startTime, endTime, dayOfWeekString, roomName;
	cout << "CourseID: "; getline(cin, courseID);
	cout << "Course name: "; getline(cin, courseName);
	cout << "Class name: "; getline(cin, className);
	cout << "Lecturer ID: "; getline(cin, lecturerID);
	cout << "Start date: "; getline(cin, startDate);
	cout << "End date: "; getline(cin, endDate);
	cout << "Start time: "; getline(cin, startTime);
	cout << "End time: "; getline(cin, endTime);

	cout << "Date of week (MON,TUE,WED,THU,FRI,SAT,SUN): "; getline(cin, dayOfWeekString);

	cout << "Room name: "; getline(cin, roomName);

	Course* newCourse = createCourse(courseID, courseName, className, lecturerID, startDate, endDate, startTime, endTime, dayOfWeekString, roomName, accountList, classList);
	if (newCourse != nullptr) {
		insertCourseToCourseList(newCourse, courseList);
		if (saveCourseToStorage(currentSemester, courseList)) {
			cout << "Created successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
	else {
		cout << "Fail to create course\n";
	}
}

void displayEditCourse(string currentSemester, AccountList* accountList, CourseList*& courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	cout << "Edit course\n";
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}

	string courseID, className;
	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);

	Course* findCourse = findCourseIDClassName(courseID, className, courseList);
	if (findCourse == nullptr) {
		cout << "Course not found\n";
		return;
	}

	cout << "Found class, please input new information:\n";
	string courseName, lecturerID, startDate, endDate, startTime, endTime, dayOfWeekString, roomName;
	cout << "Leave blank if unchange\n";
	cout << "Course name: "; getline(cin, courseName);
	cout << "Lecturer ID: "; getline(cin, lecturerID);
	cout << "Start time: "; getline(cin, startTime);
	cout << "End time: "; getline(cin, endTime);
	cout << "Date of week (MON,TUE,WED,THU,FRI,SAT,SUN): "; getline(cin, dayOfWeekString);
	cout << "Room name: "; getline(cin, roomName);

	if (editCourse(courseName, lecturerID, startTime, endTime, dayOfWeekString, roomName, accountList, findCourse)) {
		if (saveCourseToStorage(currentSemester, courseList)) {
			cout << "Edited successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
	else {
		cout << "Fail to edit\n";
	}
}

void displayCurrentCourseList(string currentSemester, CourseList* courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Course list: \n";

	outputCourseList(courseList);
}

void displayRemoveStudentFromCourse(string currentSemester, CourseList* courseListStorage) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Remove a student from course\n";

	string courseID, className, studentID;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* courseData = findCourseIDClassName(courseID, className, courseListStorage);
	if (courseData == nullptr) {
		cout << "Course not found\n";
		return;
	}

	cout << "StudentID: "; getline(cin, studentID);


	if (removeAccountFromAccountList(studentID, courseData->studentList) && removeScoreAccountID(studentID, courseData->scoreList)) {
		if (saveCourseToStorage(currentSemester, courseListStorage)) {
			cout << "Remove successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	} else {
	}
}

void displayAddStudentToCourse(string currentSemester, AccountList* accountListStorage, CourseList* courseListStorage) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Add a student to course\n";

	string courseID, className, studentID;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* courseData = findCourseIDClassName(courseID, className,courseListStorage);
	if (courseData == nullptr) {
		cout << "Course not found\n";
		return;
	}

	cout << "StudentID: "; getline(cin, studentID);


	Account* studentAccount = findAccountID(studentID, accountListStorage);
	if (studentAccount == nullptr) {
		cout << "Student not found\n";
		return;
	}

	Score* newScore = new Score;
	if (insertAccountToAccountList(studentAccount, courseData->studentList) && insertScoreToScoreList(newScore,courseData->scoreList)) {
		if (saveCourseToStorage(currentSemester, courseListStorage)) {
			cout << "Added successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
	else {
		cout << "Fail to add\n";
	}
}

void displayStudentListFromCourse(string currentSemester, CourseList* courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Student from course\n";

	string courseID, className;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* courseData = findCourseIDClassName(courseID, className, courseList);
	if (courseData == nullptr) {
		cout << "Course not found\n";
		return;
	}

	outputAccountList(courseData->studentList);
}

void displayImportCourseFromCSV(AccountList* accountList, ClassList* classList) {
	string academicYear, semester, pathFile;

	//Header
	displayHeaderUI();
	cout << "Create semester from csv file\n";

	//Input
	cout << "Academic year: ";
	getline(cin, academicYear);
	cout << "Semester: ";
	getline(cin, semester);
	cout << "Path CSV file: ";
	getline(cin, pathFile);
	
	//Check if existed
	if (createSemester(academicYear, semester)) {
		CourseList* newCourseList = nullptr;
		if (importCourseFromCSV(pathFile, accountList, classList, newCourseList)) {
			if (saveCourseToStorage(academicYear + "-" + semester, newCourseList)) {
				cout << "Import successfully\n";
			}
			else {
				cout << "Fail to open file\n";
			}
		}
		else {
			cout << "Fail to import\n";
		}
	}
	else {
		cout << "Semester already existed\n";
	}
}

void displayCheckInBoard(string currentSemester, CourseList* courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Check in result: \n";

	string courseID, className;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* course = findCourseIDClassName(courseID, className, courseList);
	if (course == nullptr) {
		cout << "Course not found\n";
		return;
	}

	int numberOfWeek = getNumberOfWeek(	course->startDate, course->startMonth, course->startYear,
		course->endDate, course->endMonth, course->endYear);
	
	//Check in header
	int date, month, year;
	date = course->startDate;
	month = course->startMonth;
	year = course->startYear;
	setColor(colorOrange);
	cout << "========= Check in =========\n";

	setColor(colorWhite);
	cout << setw(15) << setfill(' ') << "Date:";
	for (int i = 0; i < numberOfWeek; i++) {
		setColor(colorMint);
		cout << " " << dateToString(date, month, year) << " ";
		
		setColor(colorWhite);
		cout << "|";
		incDate(date, month, year, 7);
	}
	cout << endl;

	//Check in result
	CheckInList* checkInList = course->checkInList;
	while (checkInList != nullptr) {
		CheckIn* checkIn = checkInList->checkIn;

		setColor(colorWhite);
		cout << setw(15) << setfill(' ') << checkIn->studentID;
	
		for (int i = 0; i < numberOfWeek; i++) {
			setColor(colorGreen);
			cout << "      " << (checkIn->checkInResult[i] ? 'X' : ' ') << "     ";
			
			setColor(colorWhite);
			cout << "|";
		}
		cout << endl;
		checkInList = checkInList->nextCheckIn;
	}
}

void displayViewScoreBoard(string currentSemester, CourseList* courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "View scoreboard\n";

	string courseID, className;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* course = findCourseIDClassName(courseID, className, courseList);
	if (course == nullptr) {
		cout << "Course not found\n";
		return;
	}

	setColor(colorOrange);
	cout << setw(15) << setfill(' ') << "Score";
	cout << setw(10) << setfill(' ') << "Midterm";
	cout << setw(10) << setfill(' ') << "Final";
	cout << setw(10) << setfill(' ') << "Bonus";
	cout << setw(10) << setfill(' ') << "Total";
	cout << endl;
	setColor(colorWhite);
	ScoreList* scoreList = course->scoreList;
	while (scoreList != nullptr) {
		Score* score = scoreList->scoreData;
		cout << setw(15) << setfill(' ') << score->studentID;
		cout << setw(10) << setfill(' ') << score->midScore;
		cout << setw(10) << setfill(' ') << score->finalScore;
		cout << setw(10) << setfill(' ') << score->bonusScore;
		cout << setw(10) << setfill(' ') << score->totalScore;
		cout << endl;
		scoreList = scoreList->nextScore;
	}
}

void displayEditScore(string currentSemester, CourseList* courseList) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Edit student's score\n";

	string courseID, className, studentID;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* course = findCourseIDClassName(courseID, className, courseList);
	if (course == nullptr) {
		cout << "Course not found\n";
		return;
	}

	ScoreList* scoreList = course->scoreList;
	cout << "Student ID: "; getline(cin, studentID);
	Score* studentScore = findScoreAccountID(studentID, scoreList);
	if (studentScore == nullptr) {
		cout << "Student not found\n";
		return;
	}

	cout << endl;
	outputScore(studentScore);

	cout << endl;
	float midScore, finalScore, bonusScore, totalScore;
	setColor(colorOrange);
	cout << "Enter new score:\n";
	setColor(colorWhite);
	cout << "Midterm: "; cin >> midScore;
	cout << "Final: "; cin >> finalScore;
	cout << "Bonus: "; cin >> bonusScore;
	cout << "Total: "; cin >> totalScore;
	if (editScore(studentScore, midScore, finalScore, bonusScore, totalScore)) {
		if (saveCourseToStorage(currentSemester, courseList)) {
			cout << "Edited successfully\n";
		}
		else {
			cout << "Fail to open file\n";
		}
	}
	else {
		cout << "Fail to edit\n";
	}
}

void displayCheckIn(string currentSemester, CourseList* courseList, Account* loginAccount) {
	displayHeaderUI();
	displayCurrentSemester(currentSemester);
	if (currentSemester == "") {
		cout << "Please choose semester\n";
		return;
	}
	cout << "Check in\n";

	string courseID, className;

	cout << "CourseID: "; getline(cin, courseID);
	cout << "Class name: "; getline(cin, className);
	Course* course = findCourseIDClassName(courseID, className, courseList);
	if (course == nullptr) {
		cout << "Course not found\n";
		return;
	}

	cout << endl;
	setColor(colorOrange);
	cout << "Course found!\n";
	setColor(colorWhite); 

	outputCourse(course);
	cout << endl;

	int date, month, year, hour, minute;
	getCurrentDate(date, month, year);
	getCurrentTime(hour, minute);
	outputCurrentDate(date,month,year,hour,minute);

	cout << endl;
	if (checkInCourse(date, month, year, hour, minute, loginAccount->ID, course)) {
		if (saveCourseToStorage(currentSemester, courseList)) {
			setColor(colorGreen);
			cout << "Check-in successfully\n";
		}
		else {
			setColor(colorRed);
			cout << "Fail to open file\n";
		}
	}
	else {
		setColor(colorRed);
		cout << "Check-in failed\n";
	}
	setColor(colorWhite);
}