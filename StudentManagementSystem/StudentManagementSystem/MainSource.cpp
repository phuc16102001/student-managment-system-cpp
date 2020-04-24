#include "Account.h"
#include "Display.h"
#include "Constant.h"
#include "Class.h"

//Static variable import from storage and login
static AccountList* accountListStorage;
static Account* accountLoginStorage;
static ClassList* classListStorage;

void login();
void menu();
void functionMenu();
void demo();

void menu() {
	while (true) {
		int input = displayBasicMenu();
		system("CLS");
		switch (input) {
		case (1):
			displayProfileInfo(accountLoginStorage);
			break;
		case (2):
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
	while (true) {
		//Get input
		string inputAccountID, inputPassword;
		Account* accountLogin;
		displayLogin(inputAccountID, inputPassword);

		//Verify login
		if (accountLogin = findAccountID(inputAccountID, accountListStorage)) {
			if (checkPassword(inputPassword, accountLogin)) {
				system("CLS");
				accountLoginStorage = accountLogin;
				menu();
				return;
			}
		}

		//Incorrect account
		cout << "Incorrect information\n";
		cout << "Press enter to try again...\n";
		cin.get();
		system("CLS");
	}
}

void functionMenu() {
	//Display function menu
	switch (accountLoginStorage->accountType) {
		case (0): {
			//Display staff menu
			displayStaffMenu();
			break;
		}
		case (1): {
			//Display lecture menu
			displayLectureMenu();
			break;
		}
		case (2): {
			//Display student menu
			displayStudentMenu();
			break;
		}
	}
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
	menu();

	//Clear account list
	clearAccountList(accountListStorage);
	clearClassList(classListStorage);
}


int main() {
	demo();
}