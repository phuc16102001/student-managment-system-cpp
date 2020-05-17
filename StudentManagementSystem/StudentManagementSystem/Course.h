#ifndef _COURSE_HEADER_
#define _COURSE_HEADER_

#include "Constant.h"
#include "Account.h"
#include "Class.h"
#include "Utils.h"

struct CheckIn {
	bool* checkInResult = nullptr;
};

struct CheckInList {
	CheckIn* checkIn;
	CheckInList* nextCheckIn = nullptr;
};

struct Score {
	float midScore = -1;
	float bonusScore = -1;
	float finalScore = -1;
	float totalScore = -1;
	string studentID;
};

struct ScoreList {
	Score* scoreData = nullptr;
	ScoreList* nextScore = nullptr;
};

struct Course {
	string courseID;
	string courseName;
	string className;
	Account* lecturerAccount;
	int startDate, startMonth, startYear;
	int endDate, endMonth, endYear;
	int dayOfWeek = -1;				//0-6 (with 0 is sunday)
	int startHour, startMinute;
	int endHour, endMinute;
	string roomName;
	ScoreList* scoreList = nullptr;
	AccountList* studentList = nullptr;
	CheckInList* checkInList = nullptr;
};

struct CourseList {
	Course* courseData = nullptr;
	CourseList* nextCourse = nullptr;
};

bool insertCheckInToCheckInList(CheckIn* checkIn, CheckInList*& checkInList);
bool insertScoreToScoreList(Score* scoreData, ScoreList*& scoreList);
bool insertCourseToCourseList(Course* courseData, CourseList*& courseList);
bool importCourseFromStorage(string semester, AccountList* accountList, CourseList*& courseList);
bool saveCourseToStorage(string semester, CourseList* courseList);
void clearScoreList(ScoreList*& scoreList);
void clearCourseList(CourseList*& courseList);
bool changeSemester(string academicYear, string semester, string& currentSemester, AccountList* accountList, CourseList*& courseList);
bool createSemester(string academicYear, string semester);
Course* findCourseIDClassName(string courseID, string className, CourseList* courseList);
bool removeCourseFromCourseList(string courseID, string className, CourseList*& courseList);
int getLengthCourseList(CourseList* courseList);
Course* createCourse(string courseID, string courseName, string className, string lecturerID, string startDate, string endDate, string startTime, string endTime, string dayOfWeekString, string roomName, AccountList* accountListStorage, ClassList* classListStorage);
bool removeScoreAccountID(string accountID, ScoreList*& scoreList);
bool importCourseFromCSV(string path, AccountList* accountList, ClassList* classList, CourseList*& courseList);
Score* findScoreAccountID(string accountID, ScoreList* scoreList);
bool editCourse(string courseName, string lecturerID, string startDate, string endDate, string startTime, string endTime, string dayOfWeekString, string roomName, AccountList* accountList, Course* course);
bool editScore(Score* score, float midTerm, float finalTerm, float bonusPoint, float totalPoint);

#endif