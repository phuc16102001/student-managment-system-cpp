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

		//Input score, checkIn, studentID
		int nStudent = -1;
		AccountList* studentAccountList = nullptr;
		ScoreList* studentScoreList = nullptr;
		CheckInList* checkInList = nullptr;
		fin >> nStudent;
		fin.ignore();

		int numberOfWeek = getNumberOfWeek(newCourse->startDate, newCourse->startMonth, newCourse->startYear,
			newCourse->endDate, newCourse->endMonth, newCourse->endYear);
		
		for (int i = 0; i < nStudent; i++) {
			//Each student
			string studentID;
			Score* studentScore = new Score;
			CheckIn* checkIn = new CheckIn;
			checkIn->checkInResult = new bool[numberOfWeek];

			//Input student's ID
			getline(fin, studentID);

			//Input student's score
			fin >> studentScore->midScore >> studentScore->finalScore >> studentScore->bonusScore >> studentScore->totalScore;
		
			//Input student's checkIn
			for (int k = 0; k < numberOfWeek; k++) {
				fin >> checkIn->checkInResult[k];
			}
			fin.ignore();

			//Find account
			Account* studentAccount = findAccountID(studentID, accountList);
			if (studentAccount == nullptr) break;

			//Student ID
			studentScore->studentID = studentAccount->ID;
			checkIn->studentID = studentAccount->ID;

			//Insert to list
			insertAccountToAccountList(studentAccount, studentAccountList);
			insertScoreToScoreList(studentScore, studentScoreList);
			insertCheckInToCheckInList(checkIn, checkInList);
		}
		newCourse->studentList = studentAccountList;
		newCourse->scoreList = studentScoreList;
		newCourse->checkInList = checkInList;

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
		CheckInList* checkInList = courseData->checkInList;
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

		int numberOfWeek = getNumberOfWeek(courseData->startDate, courseData->startMonth, courseData->startYear,
			courseData->endDate, courseData->endMonth, courseData->endYear);
		while (studentList != nullptr && scoreList!=nullptr && checkInList != nullptr) {
			Score* score = scoreList->scoreData;
			CheckIn* checkIn = checkInList->checkIn;

			fout << studentList->accountData->ID << endl;
			fout << score->midScore << " " << score->finalScore << " " << score->bonusScore << " " << score->totalScore << endl;
			
			for (int i = 0; i < numberOfWeek; i++) {
				fout << checkIn->checkInResult[i];
				if (i<numberOfWeek-1) fout << " ";
			}
			fout << endl;

			studentList = studentList->nextAccount;
			scoreList = scoreList->nextScore;
			checkInList = checkInList->nextCheckIn;
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

bool insertCheckInToCheckInList(CheckIn* checkIn, CheckInList*& checkInList) {
	if (checkInList == nullptr) {
		checkInList = new CheckInList;
		checkInList->checkIn = checkIn;
		checkInList->nextCheckIn = nullptr;
	}
	else {
		CheckInList* cur = checkInList;
		while (cur != nullptr) {
			if (cur->nextCheckIn == nullptr) break;
			cur = cur->nextCheckIn;
		}
		cur->nextCheckIn = new CheckInList;
		cur = cur->nextCheckIn;
		cur->checkIn = checkIn;
		cur->nextCheckIn = nullptr;
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
			&& cur->courseData->className == className) {
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
	//Lecturer account
	Account* lecturerAccount = findAccountID(lecturerID, accountListStorage);
	if (lecturerAccount == nullptr) return nullptr;

	//Class 
	Class* classData = findClassName(className, classListStorage);
	if (classData == nullptr) return nullptr;

	//Create new course
	Course* newCourse = new Course;

	//Student list
	AccountList* studentList = classData->accountList;
	newCourse->studentList = studentList;

	//Date and time
	int date, month, year;
	int hour, minute;
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

	//Assign value
	newCourse->courseID = courseID;
	newCourse->courseName = courseName;
	newCourse->className = className;
	newCourse->roomName = roomName;
	newCourse->lecturerAccount = lecturerAccount;

	//Day of week
	int dayOfWeek = getDayOfWeek(dayOfWeekString);
	newCourse->dayOfWeek = dayOfWeek;

	//Scorelist and checkIn
	int numberOfWeek = getNumberOfWeek(newCourse->startDate, newCourse->startMonth, newCourse->startYear,
		newCourse->endDate, newCourse->endMonth, newCourse->endYear);
	AccountList* runnerAccountList = studentList;
	ScoreList* scoreList = nullptr;
	CheckInList* checkInList = nullptr;
	ScoreList* runnerScoreList = scoreList;
	CheckInList* runnerCheckInList = checkInList;

	while (runnerAccountList != nullptr) {
		Account* account = runnerAccountList->accountData;

		Score* score = new Score;
		score->studentID = account->ID;
		insertScoreToScoreList(score, scoreList);

		CheckIn* checkIn = new CheckIn;
		checkIn->checkInResult = new bool[numberOfWeek];
		for (int i = 0; i < numberOfWeek; i++) checkIn->checkInResult[i] = false;
		checkIn->studentID = account ->ID;
		insertCheckInToCheckInList(checkIn, checkInList);

		runnerAccountList = runnerAccountList->nextAccount;
	}
	newCourse->scoreList = scoreList;
	newCourse->checkInList = checkInList;

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

Score* findScoreAccountID(string accountID, ScoreList* scoreList) {
	while (scoreList != nullptr) {
		if (scoreList->scoreData->studentID == accountID) {
			return scoreList->scoreData;
		}
		scoreList = scoreList->nextScore;
	}
	return nullptr;
}

CheckIn* findCheckInAccountID(string accountID, CheckInList* checkInList) {
	while (checkInList != nullptr) {
		if (checkInList->checkIn->studentID == accountID) {
			return checkInList->checkIn;
		}
		checkInList = checkInList->nextCheckIn;
	}
	return nullptr;
}

bool editScore(Score* score, float midTerm, float finalTerm, float bonusPoint, float totalPoint) {
	if (score == nullptr) return false;

	score->bonusScore = bonusPoint;
	score->finalScore = finalTerm;
	score->midScore = midTerm;
	score->totalScore = totalPoint;
	return true;
}

Score* findScoreAccountID(string accountID, ScoreList* scoreList);

bool editScore(Score* score, float midTerm, float finalTerm, float bonusPoint, float totalPoint);

bool checkInCourse(int currentDate, int currentMonth, int currentYear, int currentHour, int currentMinute, string studentID, Course* course) {

	int startHour, startMinute, endHour, endMinute;
	startHour = course->startHour;
	startMinute = course->startMinute;
	endHour = course->endHour;
	endMinute = course->endMinute;
	
	if (isInTime(startHour, startMinute, endHour, endMinute, currentHour, currentMinute)) {
		int startDate, startMonth, startYear, endDate, endMonth, endYear;
		startDate = course->startDate;
		startMonth = course->startMonth;
		startYear = course->startYear;
		endDate = course->endDate;
		endMonth = course->endMonth;
		endYear = course->endYear;

		int k = 0;
		while (isLowerEqualDate(startDate, startMonth, startYear, endDate, endMonth, endYear)) {
			if (isInDate(startDate, startMonth, startYear, currentDate, currentMonth, currentYear)) {
				CheckInList* checkInList = course->checkInList;
				CheckIn* checkIn = findCheckInAccountID(studentID,checkInList);
				if (checkIn == nullptr) {
					return false;
				}

				checkIn->checkInResult[k] = 1;
				return true;
			}
			k++;
			incDate(startDate, startMonth, startYear, 7);
		}
	}

	return false;
}

bool editCourse(string courseName, string lecturerID, string startTime, string endTime, string dayOfWeekString, string roomName, AccountList* accountList, Course* course) {
	if (lecturerID != "") {
		Account* lecturerAccount = findAccountID(lecturerID, accountList);
		if (lecturerAccount == nullptr) return false;
		course->lecturerAccount = lecturerAccount;
	}
	
	if (dayOfWeekString != "") {
		int dayOfWeek = getDayOfWeek(dayOfWeekString);
		course->dayOfWeek = dayOfWeek;
	}

	if (courseName != "") {
		course->courseName = courseName;
	}

	if (roomName != "") {
		course->roomName = roomName;
	}
	
	int date, month, year;
	int hour, minute;

	if (startTime != "") {
		parseTime(startTime, hour, minute);
		course->startHour = hour;
		course->startMinute = minute;
	}

	if (endTime != "") {
		parseTime(endTime, hour, minute);
		course->endHour = hour;
		course->endMinute = minute;
	}

	return true;
}

bool exportScoreBoardToCSV(string path, ScoreList* scoreList) {

	fstream fout(path,ios::out);
	if (!fout.is_open()) return false;

	fout << "StudentID,Midterm,Final,Bonus,Total\n";
	while (scoreList!=nullptr) {
		Score* score = scoreList->scoreData;
		fout << score->studentID << ",";
		fout << score->midScore << ",";
		fout << score->finalScore << ",";
		fout << score->bonusScore << ",";
		fout << score->totalScore << ",\n";
		scoreList = scoreList->nextScore;
	}

	fout.close();
	return true;
}

bool addAccountToCourse(Account* account, Course* course) {
	if (!insertAccountToAccountList(account,course->studentList)) return false;
	
	Score* newScore = new Score;
	newScore->studentID = account->ID;
	if (!insertScoreToScoreList(newScore,course->scoreList)) return false;

	CheckIn* checkIn = new CheckIn;
	checkIn->studentID = account->ID;
	int numberOfWeek = getNumberOfWeek(course->startDate,course->startMonth,course->startYear,course->endDate,course->endMonth,course->endYear);
	checkIn->checkInResult = new bool[numberOfWeek];
	for (int i=0;i<numberOfWeek;i++) checkIn->checkInResult[i]=false;
	if (!insertCheckInToCheckInList(checkIn,course->checkInList)) return false;

	return true;
}

bool importScoreBoardFromCSV(string path, ScoreList* scoreList) {
	fstream fin(path, ios::in);
	if (!fin.is_open()) return false;

	string temp;
	getline(fin, temp);
	while (true) {
		string studentID, midString, finalString, bonusString, totalString;
		float midScore, finalScore, bonusScore, totalScore;
		midScore = finalScore = -1;
		bonusScore = totalScore = -1;

		getline(fin, studentID, ',');
		if (studentID == "") break;
		getline(fin, midString, ',');
		getline(fin, finalString, ',');
		getline(fin, bonusString, ',');
		getline(fin, totalString);

		try {
			midScore = stof(midString);
			finalScore = stof(finalString);
			bonusScore = stof(bonusString);
			totalScore = stof(totalString);

			Score* score = findScoreAccountID(studentID, scoreList);
			if (score == nullptr) continue;

			score->midScore = midScore;
			score->finalScore = finalScore;
			score->bonusScore = bonusScore;
			score->totalScore = totalScore;
		}
		catch (exception e) {
			return false;
		}
	}
	return true;
}