#ifndef RESOURCE_ALLOCATION
#define RESOURCE_ALLOCATION

#include<map>
#include "Constants.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"

/**
* Performs resource allocation based on simplification stack and the interference matrix.
* @param - ss
*	Reference to simplification stack
* @param - ig
*	Reference to interference graph
* @return
*	true - allocation without spills, otherwise false
*/
bool doResourceAllocation(SimplificationStack ss, InterferenceGraph ig);

/**
* Checks whether the allocation was successful by going through variables and interference matrix.
* If variables are in interference and have same assignment the allocation did not succeed.
* @param - ig
*	Reference to interference graph
* @return
*	true - allocation successful, otherwise false
*/
bool checkResourceAllocation(InterferenceGraph ig);

#endif

