#include "SyntaxAnalysis.h"
#include <iostream>

using namespace std;


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex) : lexicalAnalysis(lex), errorFound(false), currentPosition(0),
currentRegVariablePosition(0)
{
	tokenIterator = lexicalAnalysis.getTokenList().begin();
}


bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();
	q();

	// check if anything has been analyzed:
	if (--tokenIterator == lexicalAnalysis.getTokenList().begin())
		return false;
	else
		return !errorFound;
}


void SyntaxAnalysis::printSyntaxError(Token& token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (currentToken.getType() == t)
	{
		//currentToken.printTokenValue();
		if (t != T_END_OF_FILE)
			currentToken = getNextToken();
	}
	else
	{
		printSyntaxError(currentToken);
		errorFound = true;
		return;
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}


void SyntaxAnalysis::q()
{
	s();
	eat(T_SEMI_COL);
	l();
}


void SyntaxAnalysis::s()
{
	string IS = "";

	if (currentToken.getType() == T_MEM) {
		eat(T_MEM);
		Variables dest, src;
		Variable* var = new Variable(currentToken.getValue(), -1, Variable::VariableType::MEM_VAR);
		int num;

		if (variableExists(currentToken.getValue())) throw VariableExists(currentToken.getValue());

		if (currentToken.getType() == T_M_ID) variables.push_back(var);
		eat(T_M_ID);

		if (currentToken.getType() == T_NUM) num = stoi(currentToken.getValue());
		eat(T_NUM);

		var->setValue(num);

		dest.push_back(var);

		instructions.push_back(new Instruction(currentPosition++, I_NO_TYPE, dest, src, num, IS));

	}
	else if (currentToken.getType() == T_REG) {
		eat(T_REG);
		Variable* var = new Variable(currentToken.getValue(), -1, Variable::VariableType::MEM_VAR);

		if (variableExists(currentToken.getValue())) throw VariableExists(currentToken.getValue());

		Variables dest, src;

		if (currentToken.getType() == T_R_ID) variables.push_back(
			new Variable(currentToken.getValue(), currentRegVariablePosition++, Variable::VariableType::REG_VAR));
		eat(T_R_ID);

		dest.push_back(var);
		instructions.push_back(new Instruction(currentPosition++, I_NO_TYPE, dest, src, IS));

	}
	else if (currentToken.getType() == T_FUNC) {
		eat(T_FUNC);
		Variables dest, src;
		string s = "main";

		if (labelExists(s)) throw LabelExists(s);
		eat(T_ID);

		instructions.push_back(new Instruction(currentPosition++, I_NO_TYPE, dest, src, s, IS));
	}
	else if (currentToken.getType() == T_ID) {
		Variables dest, src;
		string s;

		if (currentToken.getType() == T_ID) s = currentToken.getValue();
		eat(T_ID);
		eat(T_COL);

		if (labelExists(s)) throw LabelExists(s);

		labels.push_back(s);

		instructions.push_back(new Instruction(currentPosition++, I_NO_TYPE, dest, src, s, IS));
		e();
	}
	else e();

}


void SyntaxAnalysis::l()
{
	if (currentToken.getType() == T_END_OF_FILE) eat(T_END_OF_FILE);
	else q();
}

Variable* SyntaxAnalysis::getVariable(string name) {

	for (auto it = variables.begin(); it != variables.end(); it++) {
		//(*it)->print();
		if ((*it)->getName() == name) return *it;
	}

	throw UninitializedVariable(name);
}

void SyntaxAnalysis::e()
{
	string IS = "";
	if (currentToken.getType() == T_ADD) {
		eat(T_ADD);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);

		IS = "add  `d, `s, `s";
		instructions.push_back(new Instruction(currentPosition++, I_ADD, dest, src, IS));

	}
	else if (currentToken.getType() == T_ADDI) {
		eat(T_ADDI);
		Variables dest, src;
		int num;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_NUM)  num = stoi(currentToken.getValue()); //src->push_back(getVariable(currentToken.getValue()));
		eat(T_NUM);

		IS = "addi  `d, `s, `n";
		instructions.push_back(new Instruction(currentPosition++, I_ADDI, dest, src, num, IS));


	}
	else if (currentToken.getType() == T_ADDU) {
		eat(T_ADDU);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);

		IS = "and  `d, `s, `s";
		instructions.push_back(new Instruction(currentPosition++, I_ADDU, dest, src, IS));

	}
	else if (currentToken.getType() == T_SUB) {
		eat(T_SUB);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);

		IS = "sub  `d, `s, `s";
		instructions.push_back(new Instruction(currentPosition++, I_SUB, dest, src, IS));

	}
	else if (currentToken.getType() == T_LA) {
		eat(T_LA);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_M_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_M_ID);

		IS = "la  `d, `s";
		instructions.push_back(new Instruction(currentPosition++, I_LA, dest, src, IS));

	}
	else if (currentToken.getType() == T_LW) {
		eat(T_LW);
		Variables dest, src;
		int num;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_NUM)  num = stoi(currentToken.getValue()); //src->push_back(getVariable(currentToken.getValue()));
		eat(T_NUM);
		eat(T_L_PARENT);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_R_PARENT);

		IS = "lw  `d, `n(`s)";
		instructions.push_back(new Instruction(currentPosition++, I_LW, dest, src, num, IS));

	}
	else if (currentToken.getType() == T_LI) {
		eat(T_LI);
		Variables dest, src;
		int num;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_NUM)  num = stoi(currentToken.getValue()); //src->push_back(getVariable(currentToken.getValue()));
		eat(T_NUM);

		IS = "li  `d, `n";
		instructions.push_back(new Instruction(currentPosition++, I_LI, dest, src, num, IS));

	}
	else if (currentToken.getType() == T_SW) {
		eat(T_SW);
		Variables dest, src;
		int num;

		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_NUM) num = stoi(currentToken.getValue());//src->push_back(getVariable(currentToken.getValue()));
		eat(T_NUM);
		eat(T_L_PARENT);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue())); //NE ZNAM STA SA ZAGRADAMA
		eat(T_R_ID);
		eat(T_R_PARENT);

		IS = "sw  `s, `n(`s)";
		instructions.push_back(new Instruction(currentPosition++, I_SW, dest, src, num, IS));

	}
	else if (currentToken.getType() == T_B) {
		eat(T_B);
		Variables dest, src;
		string s;

		if (currentToken.getType() == T_ID) s = currentToken.getValue();
		eat(T_ID);

		if (!labelExists(s)) throw UndeclaredLabel(s);

		IS = "b  `l";

		instructions.push_back(new Instruction(currentPosition++, I_B, dest, src, s, IS));

	}
	else if (currentToken.getType() == T_BLTZ) {
		eat(T_BLTZ);
		Variables dest, src;
		string s;

		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_ID)  s = currentToken.getValue();
		eat(T_ID);

		if (!labelExists(s)) throw UndeclaredLabel(s);

		IS = "bltz  `s, `l";
		instructions.push_back(new Instruction(currentPosition++, I_BLTZ, dest, src, s, IS));

	}
	else if (currentToken.getType() == T_SLT) {
		eat(T_SLT);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);

		IS = "slt  `d, `s, `s";
		instructions.push_back(new Instruction(currentPosition++, I_SLT, dest, src, IS));

	}
	else if (currentToken.getType() == T_NOR) {
		eat(T_NOR);
		Variables dest, src;

		if (currentToken.getType() == T_R_ID) dest.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);
		eat(T_COMMA);
		if (currentToken.getType() == T_R_ID) src.push_back(getVariable(currentToken.getValue()));
		eat(T_R_ID);

		IS = "nor  `d, `s, `s";
		instructions.push_back(new Instruction(currentPosition++, I_NOR, dest, src, IS));

	}
	else {
		Variables dest, src;
		IS = "nop  ";

		if (currentToken.getType() == T_NOP) instructions.push_back(new Instruction(currentPosition++, I_NOP, dest, src, IS));
		eat(T_NOP);
	}

}

void SyntaxAnalysis::printVariables() {
	for (auto it = variables.begin(); it != variables.end(); it++) (*it)->print();
}

void SyntaxAnalysis::printInstructions() {
	for (auto it = instructions.begin(); it != instructions.end(); it++) (*it)->print();

	//for (auto it = instructions.begin(); it != instructions.end(); it++) cout << (*it)->instructionString << endl;

}

bool SyntaxAnalysis::labelExists(string s) {
	for (int i = 0; i< labels.size(); i++) {
		if (labels[i] == s) return true;
	}
	return false;
}

bool SyntaxAnalysis::variableExists(string s) {
	for (auto i = variables.begin(); i != variables.end(); i++) {
		if ((*i)->getName() == s) return true;
	}
	return false;
}