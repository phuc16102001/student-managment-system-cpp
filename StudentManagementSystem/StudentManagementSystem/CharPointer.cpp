#include "CharPointer.h"

char* readCharPointerUntil(fstream& fin, char delim) {
	char buffer[1024];
	fin.get(buffer, sizeof(buffer), delim);
	char* result = new char[strlen(buffer) + 1];
	if (result == nullptr) return result;
	for (int i = 0; i <= strlen(buffer); i++) {
		result[i] = buffer[i];
	}
	return result;
}