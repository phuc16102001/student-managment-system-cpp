#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include "Constant.h"
#include "Course.h"
#include "Class.h"
#include "Account.h"

void displayHeaderUI();															//Display UI header
void displayLogin(string& inputAccountID, string& inputPassword);				//Display UI login
void displayProfileInfo(Account* accountDisplay);								//Display UI profile info of an account
int displayBasicMenu();															//Display UI basic menu
void displayChangePassword(Account* account, AccountList* accountListStorage);
int displayStaffMenu(string semester);
int displayLecturerMenu(string semester);
int displayStudentMenu(string semester);
void displayFindStudent(AccountList* accountListStorage);
void displayEditAccount(AccountList* accountListStorage);
void displayResetPassword(AccountList* accountListStorage);
void displayCreateClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayViewListClasses(ClassList* classListStorage);
void displayViewListStudentInClass(ClassList* classListStorage);
void displayAddManuallyStudentToClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayRemoveStudentFromClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayMoveStudentToAnotherClass(AccountList*& accountListStorage, ClassList*& classListStorage);
void displayCreateNewAcademicYearSemester();
void displayChangeAcademicYearSemester(string& currentSemester, AccountList* accountListStorage, CourseList*& courseListStorage);

void outputAccount(Account* account);																		//Output 1 account to console
void outputAccountList(AccountList* list);																	//Output accountList to console
void outputClassList(ClassList* classList);

#endif