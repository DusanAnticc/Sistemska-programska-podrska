#ifndef SIMPLIFICATION_STACK
#define SIMPLIFICATION_STACK

#include "IR.h"
#include <stack>
#include "InterferenceGraph.h"

extern Variables variables;
extern Instructions instructions;

typedef std::stack<Variable*> SimplificationStack;


/**
* Performs simplification of the interference graph by removing variable nodes from it.
* @param - ig
*	Reference of the interference graph
* @param - degree
*	Number of available registers
* @return
*	Reference to the simplification stack
*/
SimplificationStack* doSimplification(InterferenceGraph ig, int degree);

struct NotEnughRegisters : std::runtime_error {
	NotEnughRegisters() : runtime_error("\n\nThere is not enough registers to complete the program!\n\n") {}
};

#endif