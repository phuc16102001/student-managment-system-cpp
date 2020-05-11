#ifndef _COURSE_HEADER_
#define _COURSE_HEADER_

#include "Constant.h"

struct Course {
	string courseID;
	string courseName;
	string className;
	string lecturerAccount;
	string startDate;
	string endDate;
	int dayOfWeek;
	int startHour, startMinute;
	int endHour, endMinute;
};

struct CourseList {
	Course* courseData;
	CourseList* nextCourse;
};

struct Score {
	float midScore, bonusScore, finalScore, totalScore;
};

struct ScoreList {
	Score* scoreData;
	ScoreList* nextScore;
};

#endif