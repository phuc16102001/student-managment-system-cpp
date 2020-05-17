#include "Course.h"

bool importCourseFromStorage(string semester, AccountList* accountList, CourseList*& courseList) {
	//Open file
	string path = string(_courseStorage) + semester + ".txt";
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
		fin.ignore();

		//Input room name
		getline(fin, newCourse->roomName);

		//Input student list
		int nStudent = -1;
		AccountList* studentAccountList = nullptr;
		ScoreList* studentScoreList = nullptr;
		fin >> nStudent;
		fin.ignore();

		for (int i = 0; i < nStudent; i++) {
			//Each student
			string studentID;
			Score* studentScore = new Score;

			//Input student's ID
			getline(fin, studentID);

			//Input student's score
			fin >> studentScore->midScore >> studentScore->finalScore >> studentScore->bonusScore >> studentScore->totalScore;
			fin.ignore();

			//Find account
			Account* studentAccount = findAccountID(studentID, accountList);
			if (studentAccount == nullptr) break;

			studentScore->studentID = studentAccount->ID;

			//Insert to list
			insertAccountToAccountList(studentAccount, studentAccountList);
			insertScoreToScoreList(studentScore, studentScoreList);
		}
		newCourse->studentList = studentAccountList;
		newCourse->scoreList = studentScoreList;

		//Insert to list
		insertCourseToCourseList(newCourse, courseList);
	}

	fin.close();
	return true;
}

bool importCourseFromCSV(string path, AccountList* accountList, ClassList* classList, CourseList*& courseList) {
	//Open file
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;

	//Ignore the first line
	string temp;
	getline(fin, temp);

	while (!fin.eof()) {

		//Number of record
		getline(fin, temp, ',');
		if (temp == "") break;

		string courseID, courseName, className, lecturerID, startDate, endDate, startTime, endTime, roomName, dayOfWeekString;

		//Read input
		getline(fin, courseID, ',');
		getline(fin, courseName, ',');
		getline(fin, className, ',');
		getline(fin, lecturerID, ',');
		getline(fin, startDate, ',');
		getline(fin, endDate, ',');
		getline(fin, dayOfWeekString, ',');
		getline(fin, startTime, ',');
		getline(fin, endTime, ',');
		getline(fin, roomName);

		//Create course
		Course* newCourse = createCourse(courseID, courseName, className, lecturerID, startDate, endDate, startTime, endTime, dayOfWeekString, roomName, accountList,classList);

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
			if (cur->courseData->courseID == courseData->courseID 
				&& cur->courseData->className == courseData->className) {
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
	//Open file
	string path = _courseStorage + semester + ".txt";
	fstream fout(path, ios::out);
	if (!fout.is_open()) return false;

	while (courseList != nullptr) {
		Course* courseData = courseList->courseData;
		AccountList* studentList = courseData->studentList;
		ScoreList* scoreList = courseData->scoreList;
		int nStudent = getLengthAccountList(studentList);

		string startDate, endDate, startTime, endTime;
		startDate = dateToString(courseData->startDate, courseData->startMonth, courseData->startYear);
		endDate = dateToString(courseData->endDate, courseData->endMonth, courseData->endYear);
		startTime = timeToString(courseData->startHour, courseData->startMinute);
		endTime = timeToString(courseData->endHour, courseData->endMinute);

		fout << courseData->courseID << endl;
		fout << courseData->courseName << endl;
		fout << courseData->className << endl;
		fout << courseData->lecturerAccount->ID << endl;
		fout << startDate << endl;
		fout << endDate << endl;
		fout << startTime << endl;
		fout << endTime << endl;
		fout << courseData->dayOfWeek << endl;
		fout << courseData->roomName << endl;
		fout << nStudent << endl;

		while (studentList != nullptr && scoreList!=nullptr) {
			Score* score = scoreList->scoreData;
			fout << studentList->accountData->ID << endl;
			fout << score->midScore << " " << score->finalScore << " " << score->bonusScore << " " << score->totalScore << endl;

			studentList = studentList->nextAccount;
			scoreList = scoreList->nextScore;
		}
		
		courseList = courseList->nextCourse;
	}

	fout.close();
	return true;
}

void clearScoreList(ScoreList*& scoreList) {
	while (scoreList != nullptr) {
		ScoreList* tempScore = scoreList;
		scoreList = scoreList->nextScore;

		delete tempScore->scoreData;
		delete tempScore;
	}
}

void clearCourseList(CourseList*& courseList) {
	while (courseList != nullptr) {
		CourseList* tempCourse = courseList;
		courseList = courseList->nextCourse;

		ScoreList* scoreList = tempCourse->courseData->scoreList;
		clearScoreList(scoreList);

		delete tempCourse->courseData;
		delete tempCourse;
	}
}

bool insertScoreToScoreList(Score* scoreData, ScoreList*& scoreList) {
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
	return true;
}

bool changeSemester(string academicYear, string semester, string& currentSemester, AccountList* accountList, CourseList*& courseList) {
	string path = _courseStorage + academicYear + '-' + semester + ".txt";

	//Check existed
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;
	fin.close();

	//Import current semester courses
	if (courseList != nullptr) clearCourseList(courseList);
	currentSemester = academicYear + '-' + semester;
	importCourseFromStorage(currentSemester, accountList, courseList);

	return true;
}

bool createSemester(string academicYear, string semester) {
	string path = _courseStorage + academicYear + '-' + semester + ".txt";

	//Check existed
	fstream fin(path, ios::in);
	if (fin.is_open()) return false;
	fin.close();

	//Create new file
	fstream fout(path, ios::out);
	fout << "";
	fout.close();
}

Course* findCourseIDClassName(string courseID, string className, CourseList* courseList) {
	while (courseList != nullptr) {
		if (courseList->courseData->courseID == courseID
			&& courseList->courseData->className == className) {
			return courseList->courseData;
		}
		courseList = courseList->nextCourse;
	}
	return nullptr;
}

bool removeCourseFromCourseList(string courseID, string className, CourseList*& courseList) {
	//1st node
	if (courseList!=nullptr
		&& courseList->courseData->courseID == courseID
		&& courseList->courseData->className == className) {
		CourseList* tempCourse = courseList;
		courseList = courseList->nextCourse;

		clearScoreList(tempCourse->courseData->scoreList);
		delete tempCourse;
		return true;
	}

	//Other node
	CourseList* cur = courseList;
	while (cur != nullptr && cur->nextCourse!=nullptr) {
		if (cur->nextCourse->courseData->courseID == courseID
			&& courseList->courseData->className == className) {
			CourseList* tempCourse = cur->nextCourse;
			cur->nextCourse = tempCourse->nextCourse;

			clearScoreList(tempCourse->courseData->scoreList);
			delete tempCourse->courseData;
			delete tempCourse;
			return true;
		}
		cur = cur->nextCourse;
	}
	
	return false;
}

int getLengthCourseList(CourseList* courseList) {
	//Counter the length of list
	int count = 0;
	while (courseList != nullptr) {
		//Run until the end
		count++;
		courseList = courseList->nextCourse;
	}
	return count;
}

Course* createCourse(string courseID, string courseName, string className, string lecturerID, string startDate, string endDate, string startTime, string endTime, string dayOfWeekString, string roomName, AccountList* accountListStorage, ClassList* classListStorage) {

	string dayString[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	Account* lecturerAccount = findAccountID(lecturerID, accountListStorage);
	if (lecturerAccount == nullptr) return nullptr;

	Class* classData = findClassName(className, classListStorage);
	if (classData == nullptr) return nullptr;

	AccountList* studentList = classData->accountList;
	ScoreList* scoreList = nullptr;

	Course* newCourse = new Course;
	int date, month, year;
	int hour, minute;

	newCourse->courseID = courseID;
	newCourse->courseName = courseName;
	newCourse->className = className;
	newCourse->roomName = roomName;
	newCourse->studentList = studentList;
	newCourse->lecturerAccount = lecturerAccount;

	for (int i = 0; i < 7; i++) {
		if (dayString[i] == dayOfWeekString) {
			newCourse->dayOfWeek = i;
			break;
		}
	}


	AccountList* runnerAccountList = studentList;
	ScoreList* runnerScoreList = scoreList;
	while (runnerAccountList != nullptr) {
		Score* score = new Score;
		if (runnerScoreList == nullptr) {
			scoreList = new ScoreList;
			runnerScoreList = scoreList;
		}
		else {
			runnerScoreList->nextScore = new ScoreList;
			runnerScoreList = runnerScoreList->nextScore;
		}
		runnerScoreList->scoreData = score;

		runnerAccountList = runnerAccountList->nextAccount;
	}
	newCourse->scoreList = scoreList;

	parseDate(startDate, date, month, year);
	newCourse->startDate = date;
	newCourse->startMonth = month;
	newCourse->startYear = year;

	parseDate(endDate, date, month, year);
	newCourse->endDate = date;
	newCourse->endMonth = month;
	newCourse->endYear = year;

	parseTime(startTime, hour, minute);
	newCourse->startHour = hour;
	newCourse->startMinute = minute;

	parseTime(endTime, hour, minute);
	newCourse->endHour = hour;
	newCourse->endMinute = minute;

	return newCourse;
}

bool removeScoreAccountID(string accountID, ScoreList*& scoreList) {
	//1st node
	if (scoreList->scoreData->studentID == accountID) {
		ScoreList* tempScore = scoreList;
		scoreList = scoreList->nextScore;

		delete tempScore->scoreData;
		delete tempScore;
		return true;
	}

	//Other node
	ScoreList* cur = scoreList;
	while (cur != nullptr && cur->nextScore != nullptr) {
		if (scoreList->scoreData->studentID == accountID) {
			ScoreList* tempScore = scoreList;
			scoreList = scoreList->nextScore;

			delete tempScore->scoreData;
			delete tempScore;
			return true;
		}
		cur = cur->nextScore;
	}

	return false;
}

Score* findScoreAccountID(string accountID, ScoreList* scoreList);

bool editScore(Score* score, float midTerm, float finalTerm, float bonusPoint, float totalPoint);