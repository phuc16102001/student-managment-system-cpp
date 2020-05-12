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

void parseTime(string input, int& hour, int& minute) {
	//Find the index of ':'
	int index = input.find(':');

	//Parse into int
	hour = stoi(input.substr(0, index));
	minute = stoi(input.substr(index + 1, input.length() - index - 1));
}

//Convert string input into format DD-MM-YYYY
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