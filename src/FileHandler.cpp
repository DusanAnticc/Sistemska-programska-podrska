#include "FileHandler.h"


FileHandler::FileHandler() :inputFile(".\\..\\examples\\slt.mavn"), outputFile(".\\..\\examples\\slt.s") {}

void FileHandler::setInput(string s) { inputFile = ".\\..\\examples\\" + s + ".mavn"; }

void FileHandler::setOutput(string s) { outputFile = ".\\..\\examples\\" + s + ".s"; }

string FileHandler::getInput() { return inputFile; }

string FileHandler::getOutput() { return outputFile; }

string replace(Instruction* inst) {

	string str = inst->instructionString;

	size_t start_pos;
	if ((start_pos = str.find("`d")) != std::string::npos) {

		Variable* v = *(*inst->getDest()).begin();

		str.replace(start_pos, 2, regsToS(v->getAssignment()));
	}
	while ((start_pos = str.find("`s")) != string::npos) {

		Variable* v = *(*inst->getSrc()).begin();

		if (v->getType() == Variable::VariableType::MEM_VAR) {

			str.replace(start_pos, 2, v->getName());
		}
		else {
			int as = v->getAssignment();
			str.replace(start_pos, 2, regsToS(v->getAssignment()));
		}
		(*inst->getSrc()).remove(v);
	}

	if ((start_pos = str.find("`l")) != std::string::npos) {
		str.replace(start_pos, 2, inst->getLabel());

	}
	if ((start_pos = str.find("`n")) != std::string::npos) {

		ostringstream temp;
		temp << inst->getNumber();
		str.replace(start_pos, 2, temp.str());
	}

	return str;
}


void FileHandler::writeToFile() {

	ofstream of(outputFile);
	if (of)
	{
		of << ".globl main" << endl << endl;
		of << ".data" << endl;
		for (auto m = variables.begin(); m != variables.end(); m++)
		{
			if ((*m)->getType() == Variable::VariableType::MEM_VAR)
				of << (*m)->getName() << ":  .word  " << (*m)->getValue() << endl;
		};
		of << endl << ".text" << endl;

		for (auto i = instructions.begin(); i != instructions.end(); i++)
		{
			if ((*i)->getType() == I_NO_TYPE && (*i)->getLabel() != "") {
				of << (*i)->getLabel() << ":" << endl;
			}

			if ((*i)->getType() != I_NO_TYPE) {
				(*i)->instructionString = replace(*i);
				of << "\t" << (*i)->instructionString << endl;
			}
		}

	}
}