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

void displayFromCSV(AccountList* lst)
{
	int i = 1;
	while (lst->nextAccount != nullptr)
	{
		Account account = lst->account;
		cout << i++ << " ";
		cout << account.ID << " "
			<< account.lastName << " "
			<< account.firstName << " " 
			<< account.dob << endl;
		lst = lst->nextAccount;
	}
	cout << endl;
}
int main() {
	AccountList* accountList = nullptr;
	importAccountFromStorage(accountList);
	display(accountList);
	AccountList* temp = nullptr;
	char path [] = "data.csv";
	importAccountFromCSV(path, temp);
	displayFromCSV(temp);
}