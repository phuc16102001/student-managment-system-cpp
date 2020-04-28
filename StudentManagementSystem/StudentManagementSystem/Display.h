#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include "Constant.h"
#include "Account.h"

void displayHeaderUI();
void displayLogin(string& inputAccountID, string& inputPassword);
void displayProfileInfo(Account* accountDisplay);
int displayBasicMenu();
void displayChangePassword(Account* account, AccountList* accountListStorage);
int displayStaffMenu();
int displayLectureMenu();
int displayStudentMenu();
void displayFindStudent(AccountList* accountListStorage);
void displayEditAccount(AccountList* accountListStorage);


#endif