#include "Display.h"

void displayHeaderUI() {
	cout << "--------------------------------\n";
	cout << "|                              |\n";
	cout << "|  Student Management System   |\n";
	cout << "|                              |\n";
	cout << "--------------------------------\n";
}

void inputHidenText(string& text) {
	text = "";
	char c;
	while (c = _getch()) {
		if (c == 13) {
			//Enter press
			cout << endl;
			return;
		}
		if (c == 8 || c == 127) {
			//Backspace
			if (text.length() > 0) {
				//Still have text
				cout << "\b \b"; //Backward write space then backward
				text.erase(text.length() - 1);
			}
		}
		else {
			//Other key
			cout << "*";
			text += c;
		}
	}
	return;
}

void displayLogin(string& inputAccountID,string& inputPassword) {
	//Header
	displayHeaderUI();
	cout << "Press Ctrl+C to exit\n";

	//Input
	cout << "User ID: ";
	getline(cin, inputAccountID);
	cout << "Password: ";
	inputHidenText(inputPassword);
}

int displayBasicMenu() {
	displayHeaderUI();
	int x;
	cout	<< "1. View profile info\n"
			<< "2. Change password\n"
			<< "3. Function menu\n"
			<< "4. Logout\n"
			<< "Choose one function: ";
	cin		>> x;
	while (x < 1 || x>4) {
		cout << "Please choose again!\n";
		cin >> x;
	}
	return x;
}

void displayChangePassword(Account* account, AccountList* accountListStorage) {
	//Header
	displayHeaderUI();
	
	//Input
	string oldPassword, newPassword, repeatPassword;
	cout << "Old password: ";
	inputHidenText(oldPassword);
	cout << "New password: ";
	inputHidenText(newPassword);
	cout << "Repeat new password: ";
	inputHidenText(repeatPassword);

	//Try to change password
	switch (changePasswordAccount(oldPassword, newPassword, repeatPassword, account)) {
		case (0):
			if (saveAccountListToStorage(accountListStorage)) {
				//Save after change successful
				cout << "Password change successful\n";
			}
			else {
				//Fail to save
				cout << "Fail to open storage\n";
			}
			break;
		case (1):
			//Wrong old password
			cout << "Wrong password\n";
			break;
		case (2):
			//Wrong repeat password
			cout << "Repeat password is not the same\n";
			break;
	}
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("CLS");
}

int displayStaffMenu() {
	displayHeaderUI();
	int x;
	cout	<< "Staff Menu?\n"
			<< "Course:\n"
			<< "1. Find student\n"
			<< "2. Add student to a class\n"
			<< "3. Edit student information\n"
			<< "4. Remove student from a class\n"
			<< "5. Move student to another class\n"
			<< "6. View list of classes\n"
			<< "7. View list of students in a class\n"
			<< "8. Create/Update/Delete/View academic year and semester\n"
			<< "9. Import courses from a semester\n"
			<< "10. Add new course\n"
			<< "11. Edit existing course\n"
			<< "12. Remove course\n"
			<< "13. Remove student from a course\n"
			<< "14. Add student to a course\n"
			<< "15. View list of course in the current semester\n"
			<< "16. View list of students of a course\n"
			<< "17. View attendance list of a course\n"
			<< "18. Create/Update/Delete/View all lecturers\n\n"
			<< "Scoreboard:\n"
			<< "19. Search and view attendance list of a course\n"
			<< "20. Export scoreboard into csv file\n"
			<< "21. Back\n"
			<< "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 21) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayLectureMenu() {
	displayHeaderUI();
	int x;
	cout << "Lecturer Menu\n";
	cout << "1. View list of courses in the current semester\n"
		 << "2. View list of students of a course\n"
		 << "3. View attendance list of a course\n"
		 << "4. Edit attendances\n"
		 << "5. Import scoreboard\n"
		 << "6. Edit student grade\n"
		 << "7. Scoreboard\n"
		 << "8. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 8) {
		cout << "Please choose again!"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

int displayStudentMenu() {
	displayHeaderUI();
	int x;
	cout << "Student Menu\n";
	cout << "1. Check-in\n"
		 << "2. View check-in result\n"
		 << "3. View schedules\n"
		 << "4. View your scores\n"
		 << "5. Back\n"
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 5) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	cin.ignore();
	return x;
}

void displayProfileInfo(Account* accountDisplay) {
	displayHeaderUI();
	outputAccount(accountDisplay);
	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("CLS");
}

void displayEditAccount(AccountList* accountListStorage) {
	///Variable
	string accountID, lastName, firstName, dob;
	bool gender;

	//Header
	displayHeaderUI();
	cout << "Edit an student\n";

	//Input
	cout << "User ID: ";
	getline(cin, accountID);
	cout << "Last name: ";
	getline(cin, lastName);
	cout << "First name: ";
	getline(cin, firstName);

	//Gender input
	string genderText;
	gender = 0;
	cout << "Gender: ";
	getline(cin, genderText);

	//LowerCase 
	for (int i = 0; i < genderText.length(); i++) {
		genderText[i] = tolower(genderText[i]);
	}
	if (genderText == "male") {
		gender = 1;
	}

	//Dob input
	cout << "Date of birth: ";
	getline(cin, dob);

	//Find account
	Account* account = findAccountID(accountID, accountListStorage);

	if (editAccount(account, lastName, firstName, gender, dob)) {
		if (saveAccountListToStorage(accountListStorage)) {
			//Successful 
			cout << "Success to edit informaton\n";
		}
		else {
			//Open storage failed
			cout << "Fail to open storage\n";
		}
	}
	else {
		//Not exist
		cout << "Fail to edit information\n";
	}
}