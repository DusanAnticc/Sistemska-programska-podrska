#include "ControlFlowGraph.h"

//povezivanje - cvorovi prethodnici i naslednici
void defineSuccPred() {
	auto it = instructions.begin();
	Instruction* instr;

	for (; it != instructions.end(); it++) {
		if (it != instructions.begin()) (*it)->setPred(*prev(it));
		//u slucaju bezuslovnog skoka
		if ((*it)->getType() == I_B) {
			for (auto labela = instructions.begin(); labela != instructions.end(); labela++) {
				if ((*labela)->getLabel() == (*it)->getLabel() && (*labela)->getType() == I_NO_TYPE) {
					(*it)->setSucc(*next(labela));
					(*next(labela))->setPred(*it);
				}
			}

		}
		//u slucaju skoka ako je registar manji od nule
		else if ((*it)->getType() == I_BLTZ) {

			for (Instructions::iterator labela = instructions.begin(); labela != instructions.end(); labela++) {
				if ((*labela)->getType() == I_NO_TYPE && (*it)->getLabel() == (*labela)->getLabel()) {
					(*it)->setSucc(*next(labela));
					(*next(labela))->setPred(*it);
				}
			}

			if (next(it) != instructions.end()) (*it)->setSucc(*next(it));

		}
		else {
			auto nextic = next(it, 1);
			if (next(it) != instructions.end()) (*it)->setSucc(*next(it));
		}

	}

}

void defineDefUse() {
	for (auto it = instructions.begin(); it != instructions.end(); it++) {
		Variables* destVars = (*it)->getDest();
		Variables* useVars = (*it)->getSrc();

		for (auto var = destVars->begin(); var != destVars->end(); var++) {
			(*it)->setDef(*var);
		}
		(*it)->getDef()->unique();

		for (auto var = useVars->begin(); var != useVars->end(); var++) {
			(*it)->setUse(*var);
		}
		(*it)->getUse()->unique();

	}
}