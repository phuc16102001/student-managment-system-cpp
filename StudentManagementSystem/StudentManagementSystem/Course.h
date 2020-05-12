#ifndef _COURSE_HEADER_
#define _COURSE_HEADER_

#include "Constant.h"
#include "Account.h"
#include "Utils.h"

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
	int dayOfWeek = -1;				//1-7 (with 1 is sunday)
	int startHour, startMinute;
	int endHour, endMinute;
	string roomName;
	ScoreList* scoreList = nullptr;
	AccountList* accountList = nullptr;
};

struct CourseList {
	Course* courseData = nullptr;
	CourseList* nextCourse = nullptr;
};

void insertScoreToScoreList(Score* scoreData, ScoreList*& scoreList);
bool insertCourseToCourseList(Course* courseData, CourseList*& courseList);
bool importCourseFromStorage(string semester, AccountList* accountList, CourseList*& courseList);
bool saveCourseToStorage(string semester, CourseList* courseList);
void clearCourseList(CourseList*& courseList);
bool changeSemester(string academicYear, string semester, string& currentSemester, AccountList* accountList, CourseList*& courseList);
bool createSemester(string academicYear, string semester);
Course* findCourseID(string courseID, CourseList* courseList);
bool removeCourseFromCourseList(string courseID, CourseList*& courseList);

#endif