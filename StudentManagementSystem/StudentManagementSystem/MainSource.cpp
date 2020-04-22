#include "Account.h"
#include "Display.h"
#include "Constant.h"
#include "Class.h"

Account* login(AccountList* accountList) {
	while (true) {
		//Get input
		string inputAccountID, inputPassword;
		Account* accountLogin;
		displayLogin(inputAccountID, inputPassword);

		//Verify login
		if (accountLogin = findAccountID(inputAccountID, accountList)) {
			if (checkPassword(inputPassword, accountLogin)) {
				system("CLS");
				return accountLogin;
			}
		}

		//Incorrect account
		cout << "Incorrect information\n";
		cout << "Press enter to try again...\n";
		cin.get();
		system("CLS");
	}
	return nullptr;
}

void menu(Account* accountLogin) {
	//Display function menu
	switch (accountLogin->accountType) {
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
	AccountList* accountList = nullptr;
	Account* accountLogin;
	ClassList* classList = nullptr;

	//Import
	importAccountFromStorage(accountList);
	importClassFromStorage(accountList, classList);

	//Display Login
	accountLogin = login(accountList);
	menu(accountLogin);

	//Clear account list
	clearAccountList(accountList);
	clearClassList(classList);
}


int main() {
	demo();
}