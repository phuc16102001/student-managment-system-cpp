#include "Account.h"
#include "Constant.h"


void display(AccountList* list) {
	while (list != nullptr) {
		cout << "-----\n";
		outputAccount(list->account);
		list = list->nextAccount;
	}
	cout << endl;
}

int main() {
	AccountList* accountList = nullptr;
	
	//importAccountFromStorage(accountList);

	string path;
	cout << "Path?";
	getline(cin, path);
	importStudentFromCSV(path,accountList);

	display(accountList);

	clearAccountList(accountList);
}