#ifndef __TYPES__
#define __TYPES__

#include "Constants.h"

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>

using namespace std;

/**
* Supported token types.
*/
enum TokenType
{
	T_NO_TYPE,

	T_ID,			// abcd...
	T_M_ID,			// m123...
	T_R_ID,			// r123...
	T_NUM,			// 123...
	T_WHITE_SPACE,

	// reserved words
	T_MEM,			// _mem
	T_REG,			// _reg
	T_FUNC,			// _func
	T_ADD,			// add
	T_ADDI,			// addi
	T_SUB,			// sub
	T_LA,			// la
	T_LI,			// li
	T_LW,			// lw
	T_SW,			// sw
	T_BLTZ,			// bltz
	T_B,			// b
	T_NOP,			// nop

	// operators
	T_COMMA,		//,
	T_L_PARENT,		//(
	T_R_PARENT,		//)
	T_COL,			//:
	T_SEMI_COL,		//;

	// utility
	T_COMMENT,
	T_END_OF_FILE,
	T_ERROR,

	//my reserved words
	T_SLT,
	T_NOR,
	T_ADDU
};


/**
* Instruction type.
*/
enum InstructionType
{
	I_NO_TYPE = 0,
	I_ADD,
	I_ADDI,
	I_SUB,
	I_LA,
	I_LI,
	I_LW,
	I_SW,
	I_BLTZ,
	I_B,
	I_NOP,
	I_SLT,
	I_NOR,
	I_ADDU
};

/**
* Reg names.
*/
enum Regs
{
	no_assign = 0,
	t0,
	t1,
	t2,
	t3,
	t4
};

static string regsToS(Regs r) {

	switch (r) {
	case no_assign:
		return "no_assign";
		break;
	case t0:
		return "$t0";
		break;
	case t1:
		return "$t1";
		break;
	case t2:
		return "$t2";
		break;
	case t3:
		return "$t3";
		break;
	case t4:
		return "$t4";
		break;
	default:
		return "Error";
		break;
	}
}

static string typeToS(InstructionType t) {
	switch (t) {
	case I_NO_TYPE:
		return "I_NO_TYPE";
		break;
	case I_ADD:
		return "I_ADD";
		break;
	case I_ADDI:
		return "I_ADDI";
		break;
	case I_SUB:
		return "I_SUB";
		break;
	case I_LA:
		return "I_LA";
		break;
	case I_LI:
		return "I_LI";
		break;
	case I_LW:
		return "I_LW";
		break;
	case I_SW:
		return "I_SW";
		break;
	case I_BLTZ:
		return "I_BLTZ";
		break;
	case I_B:
		return "I_B";
		break;
	case I_NOP:
		return "I_NOP";
		break;
	case I_SLT:
		return "I_SLT";
		break;
	case I_NOR:
		return "I_NOR";
		break;
	case I_ADDU:
		return "I_ADDU";
		break;
	default:
		return "ERROR";

	}

}

#endif