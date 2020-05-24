#include "Utils.h"

//Clear all special string, just contain alphabet and number
string clearSpecialCharString(string input) {
	string validString = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = input.length() - 1; i > -1; i--) {
		if (validString.find(input[i]) == -1) {
			input.erase(i, 1);
		}
	}
	return input;
}

//Parse input from DD-MM-YYYY to int
void parseDate(string input, int& date, int& month, int& year) {
	//Find the index of '-'
	int index1, index2;
	index1 = input.find('-');
	index2 = input.find_last_of('-');

	//Parse into int
	date = stoi(input.substr(0, index1));
	month = stoi(input.substr(index1 + 1, index2 - index1 - 1));
	year = stoi(input.substr(index2 + 1, input.length() - index2 - 1));
}

//Parse input from HH:MM to int
void parseTime(string input, int& hour, int& minute) {
	//Find the index of ':'
	int index = input.find(':');

	//Parse into int
	hour = stoi(input.substr(0, index));
	minute = stoi(input.substr(index + 1, input.length() - index - 1));
}

//Convert to DD-MM-YYYY
string convertDate(string input) {
	//Date of birth
	int dd, mm, yyyy;
	dd = 0;
	mm = 0;
	yyyy = 0;

	//Find the index of '-'
	int index1, index2;
	index1 = input.find('-');
	index2 = input.find_last_of('-');

	//Parse into int
	dd = stoi(input.substr(0, index1));
	mm = stoi(input.substr(index1 + 1, index2 - index1 - 1));
	yyyy = stoi(input.substr(index2 + 1, input.length() - index2 - 1));

	//Combine new string
	input = "";
	if (dd < 10) input += "0";
	input += to_string(dd) + "-";
	if (mm < 10) input += "0";
	input += to_string(mm) + "-";
	input += to_string(yyyy);

	return input;
}

//Convert to HH:MM
string convertTime(string input) {
	int hour, minute;

	//Find the index of ':'
	int index = input.find(':');

	//Parse into int
	hour = stoi(input.substr(0, index));
	minute = stoi(input.substr(index + 1, input.length() - index - 1));

	input = "";
	if (hour < 10) input += "0";
	input += to_string(hour) + ":";
	if (minute < 10) input += "0";
	input += to_string(minute);

	return input;
}

//Convert to date string
string dateToString(int date, int month, int year) {
	return convertDate(to_string(date) + "-" + to_string(month) + "-" + to_string(year));
}

//Convert to time string
string timeToString(int hour, int minute) {
	return convertTime(to_string(hour) + ":" + to_string(minute));
}

//Get dayOfWeek int
int getDayOfWeek(string input) {
	string dayString[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
	for (int i = 0; i < 7; i++) {
		if (dayString[i] == input) {
			return i;
		}
	}
}

//Get dayOfWeek string
string getDayOfWeekString(int input) {
	string dayString[7] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	return dayString[input];
}

//Check leap year
bool isLeap(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

//Inc date from date-month-year + numberOfDay day
void incDate(int& date, int& month, int& year, int numberOfDay) {
	int dayInMonth[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (isLeap(year)) dayInMonth[2] = 29;

	date += numberOfDay;
	while (date > dayInMonth[month]) {
		date -= dayInMonth[month];
		month += 1;
		while (month > 12) {
			month -= 12;
			year += 1;
			if (isLeap(year)) {
				dayInMonth[2] = 29;
			}
			else {
				dayInMonth[2] = 28;
			}
		}
	}
}

//Check 2 date1<=date2
bool isLowerEqual(int date1, int month1, int year1, int date2, int month2, int year2) {
	if (year1 < year2) return true; else
		if (year1 > year2) return false; else

			if (month1 < month2) return true; else
				if (month1 > month2) return false; else

					if (date1 < date2) return true; else
						if (date1 > date2) return false;

		return true;
}

//Get number of week between 2 date (count full week)
int getNumberOfWeek(int date1, int month1, int year1, int date2, int month2, int year2) {
	int count = -1;
	while (isLowerEqual(date1, month1, year1, date2, month2, year2)) {
		incDate(date1, month1, year1, 7);
		count++;
	}
	return count;
}

//Check if current time is between 2 time
bool isInTime(int hour1, int minute1, int hour2, int minute2, int curHour, int curMin) {
	minute1 += hour1 * 60;
	minute2 += hour2 * 60;
	curMin += curHour * 60;
	return (minute1 <= curMin && curMin <= minute2);
}

//Get current hour and time integer
void getCurrentTime(int& hour, int& minute) {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	hour = ltm->tm_hour;
	minute = ltm->tm_min;
	return;
}

void getCurrentDate(int& date, int& month, int& year) {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	date = ltm->tm_mday;
	month = ltm->tm_mon + 1;
	year = ltm->tm_year + 1900;
	return;
}

bool isInDate(int date1, int month1, int year1, int date2, int month2, int year2) {
	date1 += month1 * 31 + year1 * 365;
	date2 += month2 * 31 + year2 * 365;
	return (date1 == date2);
}