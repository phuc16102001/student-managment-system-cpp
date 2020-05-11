#ifndef _COURSE_HEADER_
#define _COURSE_HEADER_

#include "Constant.h"
#include "Account.h"

struct Score {
	float midScore = -1;
	float bonusScore = -1;
	float finalScore = -1;
	float totalScore = -1;
};

struct ScoreList {
	Score* scoreData = nullptr;
	ScoreList* nextScore = nullptr;
};

struct Course {
	string courseID;
	string courseName;
	string className;
	string lecturerAccount;
	string startDate;
	string endDate;
	int dayOfWeek = -1;
	int startHour = -1;
	int startMinute = -1;
	int endHour = -1;
	int endMinute = -1;
	ScoreList* scoreList = nullptr;
	AccountList* accountList = nullptr;
};

struct CourseList {
	Course* courseData = nullptr;
	CourseList* nextCourse = nullptr;
};

#endif