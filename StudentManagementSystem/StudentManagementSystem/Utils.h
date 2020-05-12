#ifndef _UTILS_HEADER_
#define _UTILS_HEADER_

#include "Constant.h"

void parseDate(string input, int& date, int& month, int& year);
void parseTime(string input, int& hour, int& minute);
string clearSpecialCharString(string input);
string convertDate(string input);

#endif