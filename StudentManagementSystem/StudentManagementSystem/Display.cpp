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
	cout << "Press Ctrl+C to exit\n";
	cout << "User ID: ";
	getline(cin, inputAccountID);
	cout << "Password: ";
	getline(cin, inputPassword);
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
			<< "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 21) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
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
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 8) {
		cout << "Please choose again!"; 
		cin >> x;
	}
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
		 << "Choose one function: ";
	cin >> x;
	while (x < 1 || x > 4) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
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