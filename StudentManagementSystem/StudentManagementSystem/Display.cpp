#include "Display.h"

void displayHeaderUI() {
	cout << "--------------------------------\n";
	cout << "|                              |\n";
	cout << "|  Student Management System   |\n";
	cout << "|                              |\n";
	cout << "--------------------------------\n";
}

void displayLogin(string& inputAccountID,string& inputPassword) {
	displayHeaderUI();
	cout << "User ID: ";
	getline(cin, inputAccountID);
	cout << "Password: ";
	getline(cin, inputPassword);
}