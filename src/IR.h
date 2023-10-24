#ifndef __IR__
#define __IR__

#include "Types.h"
#include <string>
#include<iostream>

using namespace std;

//klasa predstavlja jednu varijablu iz programskog koda
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};
	static string vTypeToS(VariableType v) {
		switch (v) {
		case MEM_VAR:
			return "MEM_VAR";
			break;
		case REG_VAR:
			return "REG_VAR";
			break;
		case NO_TYPE:
			return "NO_TYPE";
			break;
		default:
			return "Error";
			break;
		}
	}
	Variable();
	Variable(std::string name, int pos, VariableType type);
	Variable(std::string name, int pos, VariableType type, int num);

	string getName();
	VariableType getType();
	int getPosition();
	Regs getAssignment();
	int getValue();

	void setValue(int n);
	void setAssignment(Regs);

	void print();
private:
	int number;
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
};

//lista varijabli iz programskog koda
typedef std::list<Variable*> Variables;


// klasa predstavlja jednu instrukciju iz programa
class Instruction
{
public:
	string instructionString;

	Instruction();
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src, string is);
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src, int num, string is);
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src, string s, string is);

	void setNum(int);
	void setLabel(string);
	void setPred(Instruction*);
	void setSucc(Instruction*);
	void setDef(Variable*);
	void setUse(Variable*);

	std::list<Instruction*>* getPred();
	std::list<Instruction*>* getSucc();
	Variables* getIn();
	Variables* getOut();
	Variables* getUse();
	Variables* getDef();
	Variables* getDest();
	Variables* getSrc();
	InstructionType getType();
	string getLabel();
	int getNumber();
	Instruction* getLabelInstruction(string);


	void print();
private:

	int number = -842150451;
	string label;

	int m_position;
	InstructionType m_type;

	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
};


//lista instrukcija iz programskog koda
typedef std::list<Instruction*> Instructions;

extern Variables variables;
extern Instructions instructions;

#endif
