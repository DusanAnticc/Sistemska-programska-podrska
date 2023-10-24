#ifndef FILE_HANDLER
#define FILE_HANDLER
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "IR.h"
#include "Types.h"

using namespace std;

extern Variables variables;
extern Instructions instructions;

class FileHandler {

	string inputFile;
	string outputFile;

public:
	FileHandler();

	void setInput(string);

	void setOutput(string);

	string getInput();

	string getOutput();

	void writeToFile();
};

#endif