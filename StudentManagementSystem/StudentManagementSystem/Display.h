#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include "Constant.h"
#include "Course.h"
#include "Class.h"
#include "Account.h"

#define colorGreen 2
#define colorBlue 3
#define colorRed 4
#define colorPurple 5
#define colorOrange 6
#define colorWhite 7
#define colorMint 11

void displayHeaderUI();																					//Display UI header
void displayLoadingUI(int percentage);
void displayLogin(string& inputAccountID, string& inputPassword);										//Display UI login
void displayProfileInfo(Account* accountDisplay);														//Display UI profile info of an account
int displayBasicMenu();																					//Display UI basic menu
void displayChangePassword(Account* account, AccountList* accountListStorage);
int displayStaffMenu(string semester);
int displayLecturerMenu(string semester);
int displayStudentMenu(string semester);
void displayCreateAccount(AccountList*& accountListStorage);
void displayFindStudent(AccountList* accountListStorage);
void displayEditAccount(AccountList* accountListStorage);
void displayResetPassword(AccountList* accountListStorage);
void displayImportClassFromCSV(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayViewListClasses(ClassList* classListStorage);
void displayViewListStudentInClass(ClassList* classListStorage);
void displayAddManuallyStudentToClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayRemoveStudentFromClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayMoveStudentToAnotherClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayCreateNewAcademicYearSemester();
void displayChangeAcademicYearSemester(string& currentSemester, AccountList* accountListStorage, CourseList*& courseListStorage);
void displayRemoveCourse(string currentSemester, CourseList*& courseList);
void displayAddNewCourse(string currentSemester, AccountList* accountList, ClassList* classList, CourseList*& courseList);
void displayCurrentCourseList(string currentSemester, CourseList* courseList);
void displayRemoveStudentFromCourse(string currentSemester, CourseList* courseListStorage);
void displayAddStudentToCourse(string currentSemester, AccountList* accountListStorage, CourseList* courseListStorage);
void displayStudentListFromCourse(string currentSemester, CourseList* courseList);
void displayImportCourseFromCSV(AccountList* accountList, ClassList* classList);
void displayEditCourse(string currentSemester, AccountList* accountList, CourseList*& courseList);
void displayCheckInBoard(string currentSemester, CourseList* courseList);
void displayViewScoreBoard(string currentSemester, CourseList* courseList);
void displayEditScore(string currentSemester, CourseList* courseList);
void displayCheckIn(string currentSemester, CourseList* courseList);

void outputAccount(Account* account);																		//Output 1 account to console
void outputAccountList(AccountList* list);																	//Output accountList to console
void outputClassList(ClassList* classList);
void outputCourse(Course* course);

#endif