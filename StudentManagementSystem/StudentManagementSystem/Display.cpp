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
	cout << "What do you want to do ?\n";
	cout << "Course:" << endl;
	cout << "1.Looking for a student" << endl
		<< "2.Add a student" << endl
		<< "3.Edit information of a student" << endl
		<< "4.Remove a student" << endl
		<< "5.Change students to another class" << endl
		<< "6.View list of classes" << endl
		<< "7.View list of students in a class" << endl
		<< "8.Create/ Update/ Delete/ View academic year, and semester" << endl
		<< "9.Import courses from a semester" << endl
		<< "10.Manually add a new course" << endl
		<< "11.Edit an existing course " << endl
		<< "12.Remove course" << endl
		<< "13.Remove a specific student from a course" << endl
		<< "14.Add a specific student to a course" << endl
		<< "15.View list of course in the current semester" << endl
		<< "16.View list of students of a course " << endl
		<< "17.View attendance list of a course" << endl
		<< "18.Create/ Update/ Delete/ View all lecturers"
		<< endl << endl;
	cout << "Scoreboard: \n";
	cout << "19.Search and view attendance list of a course" << endl
		<< "20.Export a scoreboard into a csv file" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 20) {
		cout << "Please, re-enter your choice\n"; 
		cin >> x;
	}
	return x;
}

int displayLectureMenu()
{
	displayHeaderUI();
	int x;
	cout << "What do you want to do ?\n";
	cout << "1.View list of courses in the current semester" << endl
		<< "2.View list of students of a course" << endl
		<< "3.View attendance list of a course" << endl
		<< "4.Edit attendance" << endl
		<< "5.Import scoreboard of a course" << endl
		<< "6.Edit grade of a student" << endl
		<< "7.View a scoreboard" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 7) {
		cout << "Please, re-enter your choice"; 
		cin >> x;
	}
	return x;
}

int displayStudentMenu()
{
	displayHeaderUI();
	int x;
	cout << "What do you want to do ?\n";
	cout << "1.Check-in" << endl
		<< "2.View check-in result" << endl
		<< "3.View schedules" << endl
		<< "4.View your scores of a course" << endl << endl;
	cout << "Choose one function: ";
	cin >> x;
	while (x < 0 || x > 4) {
		cout << "Please, re-enter your choice\n"; 
		cin >> x;
	}
	return x;
}