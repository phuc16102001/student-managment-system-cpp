#include "Account.h"
#include "Display.h"
#include "Constant.h"

void login(AccountList* accountList, Account& accountLogin) {
	while (true) {
		//Get input
		string inputAccountID, inputPassword;
		displayLogin(inputAccountID, inputPassword);
		
		//Verify login
		if (findAccountID(inputAccountID, accountList, accountLogin)) {
			if (checkPassword(inputPassword, accountLogin)) break;
		}

		//Incorrect account
		cout << "Incorrect information\n";
		cout << "Press enter to try again...\n";
		cin.get();
		system("CLS");
	}

	system("CLS");
}

void menu(Account accountLogin) {
	//Display function menu
	switch (accountLogin.accountType) {
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
	Account accountLogin;
	importAccountFromStorage(accountList);

	//Display Login
	login(accountList, accountLogin);
	menu(accountLogin);

	//Clear account list
	clearAccountList(accountList);
}


int main() {
	demo();
}