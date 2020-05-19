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
	system("CLS");
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
			displayCreateAccount(accountListStorage);
			break;
		case (2):
			displayFindStudent(accountListStorage);
			break;
		case (3):
			displayEditAccount(accountListStorage);
			break;
		case (4):
			displayResetPassword(accountListStorage);
			break;
		case (5):
			displayAddManuallyStudentToClass(accountListStorage, classListStorage);
			break;
		case (6):
			displayImportClassFromCSV(accountListStorage,classListStorage);
			break;
		case (7):
			displayRemoveStudentFromClass(accountListStorage, classListStorage);
			break;
		case (8):
			displayMoveStudentToAnotherClass(accountListStorage, classListStorage);
			break;
		case (9):
			displayViewListClasses(classListStorage);
			break;
		case (10):
			displayViewListStudentInClass(classListStorage);
			break;
		case (11):
			displayCreateNewAcademicYearSemester();
			break;
		case (12):
			displayChangeAcademicYearSemester(currentSemester,accountListStorage,courseListStorage);
			break;
		case (13):
			displayImportCourseFromCSV(accountListStorage, classListStorage);
			break;
		case (14):
			displayAddNewCourse(currentSemester, accountListStorage, classListStorage, courseListStorage);
			break;
		case (15):
			displayEditCourse(currentSemester, accountListStorage, courseListStorage);
			break;
		case (16):
			displayRemoveCourse(currentSemester, courseListStorage);
			break;
		case (17):
			displayRemoveStudentFromCourse(currentSemester, courseListStorage);
			break;
		case (18):
			displayAddStudentToCourse(currentSemester, accountListStorage, courseListStorage);
			break;
		case (19):
			displayCurrentCourseList(currentSemester, courseListStorage);
			break;
		case (20):
			displayStudentListFromCourse(currentSemester, courseListStorage);
			break;
		case (21):
			displayCheckInBoard(currentSemester, courseListStorage);
			break;
		case (22):
			displayViewScoreBoard(currentSemester, courseListStorage);
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
		case (1):
			displayChangeAcademicYearSemester(currentSemester, accountListStorage, courseListStorage); 
			break;
		case (2):
			displayCurrentCourseList(currentSemester, courseListStorage);
			break;
		case (3):
			displayStudentListFromCourse(currentSemester, courseListStorage);
			break;
		case (4):
			displayCheckInBoard(currentSemester, courseListStorage);
			break;
		case (5):
			displayAddStudentToCourse(currentSemester, accountListStorage, courseListStorage);
			break;
		case (6):
			displayRemoveStudentFromCourse(currentSemester, courseListStorage);
			break;
		case (9):
			displayViewScoreBoard(currentSemester, courseListStorage);
			break;
		case (10):
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
		case (1): 
			displayChangeAcademicYearSemester(currentSemester, accountListStorage, courseListStorage);
			break;
		case (2): 
			displayCurrentCourseList(currentSemester, courseListStorage);
			break;
		case (4):
			displayCheckInBoard(currentSemester, courseListStorage);
			break;
		case (6):
			displayViewScoreBoard(currentSemester, courseListStorage);
			break;
		case (7):
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
	displayLoadingUI(0);
	accountListStorage = nullptr;

	displayLoadingUI(20);
	accountLoginStorage = nullptr;

	displayLoadingUI(40);
	classListStorage = nullptr;

	//Import
	displayLoadingUI(60);
	importAccountFromStorage(accountListStorage);

	displayLoadingUI(80);
	importClassFromStorage(accountListStorage, classListStorage);

	//Display Login
	displayLoadingUI(100);
	login();

	//Clear account list
	clearAccountList(accountListStorage);
	clearClassList(classListStorage);
}

void test() {
	for (int i = 0; i <= 100; i++) displayLoadingUI(i);
}

int main() {
	demo();
}