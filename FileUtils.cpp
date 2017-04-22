/*
* JSAMP - Java implementation for SA:MP.
* Project started 13/4/15.
* Writted by spell <leandro.barbero122@gmail.com>
*/

#include "FileUtils.h"
#include <iostream>
#include <fstream>

vector<string>* loadFileLines(const char* path) {
	vector<string>* result = new vector<string>;
	string line;
	ifstream optionsFile(path);

	if (optionsFile.is_open()) {
		while (!optionsFile.eof()) {
			getline(optionsFile, line);
			for (unsigned int i = 0; i < line.length(); i++)
				if (line[i] == '\r') line[i] = 0;/* fix line ending */
			if (line.length() > 0) result->push_back(line);
		}
		optionsFile.close();
	} else {
		return NULL;
	}
	return result;
}