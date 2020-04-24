#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include "Constant.h"
#include "Account.h"

void displayHeaderUI();
void displayLogin(string& inputAccountID, string& inputPassword);
void displayProfileInfo(Account* accountDisplay);
int displayBasicMenu();
int displayStaffMenu();
int displayLectureMenu();
int displayStudentMenu();

#endif