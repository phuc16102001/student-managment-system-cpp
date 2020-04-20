#include "Account.h"
#include "Display.h"
#include "Constant.h"

void login(AccountList* accountList, Account& accountLogin) {
	while (true) {
		string inputAccountID, inputPassword;
		displayLogin(inputAccountID, inputPassword);
		if (findAccountID(inputAccountID, accountList, accountLogin)) {
			if (checkPassword(inputPassword, accountLogin)) return;
		}
		cout << "Incorrect information\n";
		cout << "Press enter to try again...\n";
		cin.get();
		system("CLS");
	}
}

void demo() {
	//Init account
	AccountList* accountList = nullptr;
	Account accountLogin;
	importAccountFromStorage(accountList);

	login(accountList, accountLogin);

	clearAccountList(accountList);
}


int main() {
	demo();
}