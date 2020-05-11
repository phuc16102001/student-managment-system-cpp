#ifndef _COURSE_HEADER_
#define _COURSE_HEADER_

#include "Constant.h"
#include "Account.h"

struct Score {
	float midScore;
	float bonusScore;
	float finalScore;
	float totalScore;
};

struct ScoreList {
	Score* scoreData;
	ScoreList* nextScore;
};

struct Course {
	string courseID;
	string courseName;
	string className;
	string lecturerAccount;
	string startDate;
	string endDate;
	int dayOfWeek;
	int startHour;
	int startMinute;
	int endHour;
	int endMinute;
	ScoreList* scoreList = nullptr;
	AccountList* accountList = nullptr;
};

struct CourseList {
	Course* courseData;
	CourseList* nextCourse;
};

#endif