#include "Course.h"

bool importCourseFromStorage(string semester, AccountList* accountList, CourseList*& courseList) {
	//Open file
	string path = _courseStorage + semester + ".course.txt";
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;

	while (!fin.eof()) {
		//Read data input
		string tempID;
		getline(fin, tempID);
		if (tempID == "") break;

		//Create and input a new course
		Course* newCourse = new Course;
		newCourse->courseID = tempID;
		getline(fin, newCourse->courseName);
		getline(fin, newCourse->className);

		//Find lecturer account
		string lecturerID;
		getline(fin, lecturerID);
		Account* lecturerAccount = findAccountID(lecturerID, accountList);
		newCourse->lecturerAccount = lecturerAccount;

		//Variable for time
		int date, month, year;
		int hour, minute;
		string input;
		
		//Input startDate
		getline(fin, input);
		parseDate(input, date, month, year);
		newCourse->startDate = date;
		newCourse->startMonth = month;
		newCourse->startYear = year;

		//Input endDate
		getline(fin, input);
		parseDate(input, date, month, year);
		newCourse->endDate = date;
		newCourse->endMonth = month;
		newCourse->endYear = year;

		//Input startTime
		getline(fin, input);
		parseTime(input, hour, minute);
		newCourse->startHour = hour;
		newCourse->startMinute = minute;

		//Input endTime
		getline(fin, input);
		parseTime(input, hour, minute);
		newCourse->endHour = hour;
		newCourse->endMinute = minute;

		//Input dayOfWeek
		fin >> newCourse->dayOfWeek;

		//Input room name
		getline(fin, newCourse->roomName);

		//Input student list
		int nStudent = -1;
		AccountList* studentAccountList = nullptr;
		ScoreList* studentScoreList = nullptr;
		fin >> nStudent;

		for (int i = 0; i < nStudent; i++) {
			string studentID;
			Score* studentScore = new Score;

			getline(fin, studentID);
			fin >> studentScore->midScore >> studentScore->finalScore >> studentScore->bonusScore >> studentScore->totalScore;

			Account* studentAccount = findAccountID(studentID, accountList);
			if (studentAccount == nullptr) break;
		
			studentScore->studentID = studentAccount->ID;

			insertAccountToAccountList(studentAccount, studentAccountList);
			insertScoreToScoreList(studentScore, studentScoreList);
		}
		newCourse->accountList = studentAccountList;
		newCourse->scoreList = studentScoreList;

		//Insert to list
		insertCourseToCourseList(newCourse, courseList);
	}

	fin.close();
	return true;
}

bool insertCourseToCourseList(Course* courseData, CourseList*& courseList) {
	if (courseList == nullptr) {
		courseList = new CourseList;
		courseList->courseData = courseData;
		courseList->nextCourse = nullptr;
	}
	else {
		CourseList* cur = courseList;
		while (cur != nullptr) {
			if (cur->courseData->courseID == courseData->courseID) {
				return false;
			}
			if (cur->nextCourse == nullptr) break;
			cur = cur->nextCourse;
		}
		cur->nextCourse = new CourseList;
		cur = cur->nextCourse;
		cur->courseData = courseData;
		cur->nextCourse = nullptr;
	}
	return true;
}

bool saveCourseToStorage(string semester, CourseList* courseList) {
	return false;
}

void clearCourseList(CourseList*& courseList) {
	while (courseList != nullptr) {
		CourseList* tempCourse = courseList;
		courseList = courseList->nextCourse;

		ScoreList* scoreList = tempCourse->courseData->scoreList;
		while (scoreList != nullptr) {
			ScoreList* tempScore = scoreList;
			scoreList = scoreList->nextScore;
			
			delete tempScore->scoreData;
			delete tempScore;
		}

		delete tempCourse->courseData;
		delete tempCourse;
	}
}

void insertScoreToScoreList(Score* scoreData, ScoreList*& scoreList) {
	if (scoreList == nullptr) {
		scoreList = new ScoreList;
		scoreList->scoreData = scoreData;
		scoreList->nextScore = nullptr;
	}
	else {
		ScoreList* cur = scoreList;
		while (cur != nullptr) {
			if (cur->nextScore == nullptr) break;
			cur = cur->nextScore;
		}
		cur->nextScore = new ScoreList;
		cur = cur->nextScore;
		cur->scoreData = scoreData;
		cur->nextScore = nullptr;
	}
}

bool changeSemester() {
	return false;
}

bool createSemester(string academicYear, string semester) {
	string path = _courseStorage + academicYear + '-' + semester + ".course.txt";

	//Check existed
	fstream fin(path, ios::in);
	if (fin.is_open()) return false;
	fin.close();

	//Create new file
	fstream fout(path, ios::out);
	fout << "";
	fout.close();
}