#include "Account.h"
#include "Constant.h"


void display(AccountList* list) {
	while (list != nullptr) {
		Account account = list->account;
		cout << account.ID << " "
			<< account.lastName << " "
			<< account.firstName << " "
			<< account.password << endl;
		list = list->nextAccount;
	}
	cout << endl;
}

int main() {
	AccountList* accountList = nullptr;
	importAccountFromStorage(accountList);
	display(accountList);
}