#include "Account.h"
#include "Display.h"
#include "Constant.h"
#include "Class.h"
#include "Course.h"

//Variable import from storage
AccountList* accountListStorage = nullptr;
Account* accountLoginStorage = nullptr;
ClassList* classListStorage = nullptr;
string currentSemester = "";
CourseList* courseListStorage = nullptr;

//Prototype
void login();
void basicMenu();
void functionMenu();
void functionStaff(int number);
void functionLecturer(int number);
void functionStudent(int number);
void demo();

void basicMenu() {
	while (true) {
		int input = displayBasicMenu();
		system("CLS");
		switch (input) {
			case (1):
				displayProfileInfo(accountLoginStorage);
				break;
			case (2):
				displayChangePassword(accountLoginStorage, accountListStorage);
				break;
			case (3):
				functionMenu();
				return;
			case (4):
				cin.ignore();
				login();
				return;
			}
	}
}

void login() {
	//Get input
	string inputAccountID, inputPassword;
	Account* accountLogin;
	displayLogin(inputAccountID, inputPassword);

	//Verify login
	if (accountLogin = findAccountID(inputAccountID, accountListStorage)) {
		if (checkPassword(inputPassword, accountLogin)) {
			system("CLS");
			accountLoginStorage = accountLogin;
			basicMenu();
			return;
		}
	}

	//Incorrect account
	cout << "Incorrect information\n";
	cout << "Press enter to try again...\n";
	cin.get();
	system("CLS");
	login();
}

void functionMenu() {
	//Display function menu
	int accountType = accountLoginStorage->accountType;
	switch (accountType) {
		case (0): {
			//Display staff menu
			int number = displayStaffMenu(currentSemester);
			system("CLS");
			functionStaff(number);	
			break;
		}

		case (1): {
			//Display lecturer menu
			int number = displayLecturerMenu(currentSemester);
			system("CLS");
			functionLecturer(number);
			break;
		}

		case (2): {
			//Display student menu
			int number = displayStudentMenu(currentSemester);
			system("CLS");
			functionStudent(number);
			break;
		}
	}
}

void functionStaff(int number) {
	switch (number) {
		case (1):
			displayFindStudent(accountListStorage);
			break;
		case (2):
			displayEditAccount(accountListStorage);
			break;
		case (3):
			displayResetPassword(accountListStorage);
			break;
		case (4):
			displayAddManuallyStudentToClass(accountListStorage, classListStorage);
			break;
		case (5):
			displayCreateClass(accountListStorage,classListStorage);
			break;
		case (6):
			displayRemoveStudentFromClass(accountListStorage, classListStorage);
			break;
		case (7):
			displayMoveStudentToAnotherClass(accountListStorage, classListStorage);
			break;
		case (8):
			displayViewListClasses(classListStorage);
			break;
		case (9):
			displayViewListStudentInClass(classListStorage);
			break;
		case(10):
			displayCreateNewAcademicYearSemester();
			break;
		case (11):
			displayChangeAcademicYearSemester(currentSemester,accountListStorage,courseListStorage);
			break;
		case (24):
			basicMenu();
			return;
	}

	cout << "Press enter to continue...\n";
	cin.get();
	system("CLS");
	functionMenu();
}

void functionLecturer(int number) {
	switch (number) {
		case (8):
			basicMenu();
			return;
	}
	cout << "Press enter to continue...\n";
	cin.get();
	system("CLS");
	functionMenu();
}

void functionStudent(int number) {
	switch (number) {
		case (5):
			basicMenu();
			return;
	}
	cout << "Press enter to continue...\n";
	cin.get();
	system("CLS");
	functionMenu();
}

void demo() {
	//Init account
	accountListStorage = nullptr;
	accountLoginStorage = nullptr;
	classListStorage = nullptr;

	//Import
	importAccountFromStorage(accountListStorage);
	importClassFromStorage(accountListStorage, classListStorage);

	//Display Login
	login();

	//Clear account list
	clearAccountList(accountListStorage);
	clearClassList(classListStorage);
}

void test() {
	string academicYear;
	string semester;
	cout << "year: "; getline(cin, academicYear);
	cout << "semester: "; getline(cin, semester);
	if (createSemester(academicYear, semester)) {
		cout << "Success\n";
	}
	else {
		cout << "Fail\n";
	}
}

int main() {
	demo();
}