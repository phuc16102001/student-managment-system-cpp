#ifndef _UTILS_HEADER_
#define _UTILS_HEADER_

#include "Constant.h"

void parseDate(string input, int& date, int& month, int& year);
void parseTime(string input, int& hour, int& minute);
string dateToString(int date, int month, int year);
string timeToString(int hour, int minute);
string clearSpecialCharString(string input);
string convertTime(string input);
string convertDate(string input);
string getDayOfWeekString(int input);
int getDayOfWeek(string input);
void incDate(int& date, int& month, int& year, int numberOfDay);
bool isLowerEqual(int date1, int month1, int year1, int date2, int month2, int year2);
int getNumberOfWeek(int date1, int month1, int year1, int date2, int month2, int year2);
void getCurrentTime(int& hour, int& minute);
bool isInTime(int hour1, int minute1, int hour2, int minute2, int curHour, int curMin);
void getCurrentDate(int& date, int& month, int& year);
bool isInDate(int date1, int month1, int year1, int date2, int month2, int year2);

#endif