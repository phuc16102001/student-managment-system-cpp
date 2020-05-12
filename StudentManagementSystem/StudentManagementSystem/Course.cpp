#include "Course.h"

bool importCourseFromStorage(string semester, AccountList* accountList, CourseList*& courseList) {

}

bool saveCourseToStorage(string semester, CourseList* courseList) {

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