#ifndef _DISPLAY_HEADER_
#define _DISPLAY_HEADER_

#include "Constant.h"
#include "Account.h"

void displayHeaderUI();															//Display UI header
void displayLogin(string& inputAccountID, string& inputPassword);				//Display UI login
void displayProfileInfo(Account* accountDisplay);								//Display UI profile info of an account
int displayBasicMenu();															//Display UI basic menu
void displayChangePassword(Account* account, AccountList* accountListStorage);
int displayStaffMenu();
int displayLectureMenu();
int displayStudentMenu();
void displayFindStudent(AccountList* accountListStorage);
void displayEditAccount(AccountList* accountListStorage);
void displayResetPassword(AccountList* accountListStorage);

#endif