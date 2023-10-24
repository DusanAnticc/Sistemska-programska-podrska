#include "IR.h"
#include "Types.h"


Variable::Variable() :
	m_type(NO_TYPE),
	m_name(""),
	m_position(-1),
	m_assignment(no_assign) {}

Variable::Variable(std::string name, int pos, VariableType type) :
	m_type(type),
	m_name(name),
	m_position(pos),
	m_assignment(no_assign) {}

Variable::Variable(std::string name, int pos, VariableType type, int n) :
	m_type(type),
	m_name(name),
	m_position(pos),
	m_assignment(no_assign),
	number(n) {}

string Variable::getName() { return m_name; }
Variable::VariableType Variable::getType() { return m_type; }
int Variable::getPosition() { return m_position; }
Regs Variable::getAssignment() { return m_assignment; }
int Variable::getValue() { return number; }

void Variable::setAssignment(Regs r) { m_assignment = r; }
void Variable::setValue(int n) { number = n; }



void Variable::print() {
	cout << "\nType: " << vTypeToS(m_type) << " " << m_name << " Position: " << m_position << " Assignment: " << regsToS(m_assignment) << endl;
}

//========================================


Instruction::Instruction() :
	m_position(0),
	m_type(I_NO_TYPE),
	label() {}

Instruction::Instruction(int pos, InstructionType type, Variables& dst, Variables& src, string is) :
	m_position(pos),
	m_type(type),
	m_dst(dst),
	m_src(src),
	label(),
	instructionString(is) {}


Instruction::Instruction(int pos, InstructionType type, Variables& dst, Variables& src, int num, string is) :
	m_position(pos),
	m_type(type),
	m_dst(dst),
	m_src(src),
	label(),
	number(num),
	instructionString(is) {}


Instruction::Instruction(int pos, InstructionType type, Variables& dst, Variables& src, string s, string is) :
	m_position(pos),
	m_type(type),
	m_dst(dst),
	m_src(src),
	label(s),
	instructionString(is) {}

void Instruction::setNum(int n) { number = n; }
void Instruction::setLabel(string s) { label = s; }
void Instruction::setPred(Instruction* instr) { m_pred.push_back(instr); }
void Instruction::setSucc(Instruction* instr) { m_succ.push_back(instr); }
void Instruction::setDef(Variable* v) { m_def.push_back(v); }
void Instruction::setUse(Variable* v) { m_use.push_back(v); }

std::list<Instruction*>* Instruction::getPred() { return &m_pred; }
std::list<Instruction*>* Instruction::getSucc() { return &m_succ; }
Variables* Instruction::getDest() { return &m_dst; }
Variables* Instruction::getSrc() { return &m_src; }
Variables* Instruction::getIn() { return &m_in; }
Variables* Instruction::getOut() { return &m_out; }
Variables* Instruction::getUse() { return &m_use; }
Variables* Instruction::getDef() { return &m_def; }
InstructionType Instruction::getType() { return m_type; }
string Instruction::getLabel() { return label; }
int Instruction::getNumber() { return number; }
Instruction* Instruction::getLabelInstruction(string l) {
	for (auto it = instructions.begin(); it != instructions.end(); it++) {
		if ((*it)->getLabel() == l && (*it)->getType() == I_NO_TYPE) return *it;
	}
	throw exception("Greska");

}


void Instruction::print() {
	string dest = "";
	string src = "";
	for (auto it = m_dst.begin(); it != m_dst.end(); it++) dest += (*it)->getName() + " ";
	for (auto it = m_src.begin(); it != m_src.end(); it++) src += (*it)->getName() + " ";
	cout << "\n" << typeToS(m_type) << " " << " position: " << m_position <<
		" destination: " << dest << " source: " << src << " number: " << (number == -842150451 ? "NULL" : std::to_string(number)) << " label: " << label
		<< endl;
}



//=============================================================================================

