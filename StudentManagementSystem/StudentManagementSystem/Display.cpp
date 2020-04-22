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

int displayStaffMenu()
{
	displayHeaderUI();
	int x;
	cout << "Staff Menu?\n";
	cout << "Course:" << endl;
	cout << "0.Log out and close" << endl
		<< "1. Find student" << endl
		<< "2. Add student to a class" << endl
		<< "3. Edit student information" << endl
		<< "4. Remove student from a class" << endl
		<< "5. Move student to another class" << endl
		<< "6. View list of classes" << endl
		<< "7. View list of students in a class" << endl
		<< "8. Create/Update/Delete/View academic year and semester" << endl
		<< "9. Import courses from a semester" << endl
		<< "10. Add new course" << endl
		<< "11. Edit existing course" << endl
		<< "12. Remove course" << endl
		<< "13. Remove student from a course" << endl
		<< "14. Add student to a course" << endl
		<< "15. View list of course in the current semester" << endl
		<< "16. View list of students of a course " << endl
		<< "17. View attendance list of a course" << endl
		<< "18. Create/Update/Delete/View all lecturers"
		<< endl << endl;
	cout << "Scoreboard: \n";
	cout << "19. Search and view attendance list of a course" << endl
		<< "20. Export scoreboard into csv file" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 20) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	return x;
}

int displayLectureMenu()
{
	displayHeaderUI();
	int x;
	cout << "Lecturer Menu\n";
	cout << "0.Log out and close" << endl
		<< "1. View list of courses in the current semester" << endl
		<< "2. View list of students of a course" << endl
		<< "3. View attendance list of a course" << endl
		<< "4. Edit attendances" << endl
		<< "5. Import scoreboard" << endl
		<< "6. Edit student grade" << endl
		<< "7. Scoreboard" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 7) {
		cout << "Please choose again!"; 
		cin >> x;
	}
	return x;
}

int displayStudentMenu()
{
	displayHeaderUI();
	int x;
	cout << "Student Menu\n";
	cout << "0.Log out and close" << endl
		<< "1. Check-in" << endl
		<< "2. View check-in result" << endl
		<< "3. View schedules" << endl
		<< "4. View your scores" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 4) {
		cout << "Please choose again!\n"; 
		cin >> x;
	}
	return x;
}