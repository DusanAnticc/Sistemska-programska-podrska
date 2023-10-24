#include "ResourceAllocation.h"

Variables izbacene;
list<Regs> slobodni_registri{ t0, t1, t2, t3, t4 }; //t4
bool doResourceAllocation(SimplificationStack ss, InterferenceGraph ig) {

	// napraviti registre, proci kroz stek i napraviti nekoliko promena
	while (!ss.empty())
	{
		slobodni_registri.push_back(t4);
		slobodni_registri.push_back(t3);
		slobodni_registri.push_back(t2);
		slobodni_registri.push_back(t1);
		slobodni_registri.push_back(t0);
		//uzima se promenljiva sa vrha steka
		Variable* v = ss.top();
		ss.pop();//skida se ta promenljiva sa steka

		if (!izbacene.empty()) {//ako ta promenljiva nije izbacena
			for (Variables::iterator iter = izbacene.begin(); iter != izbacene.end(); iter++) {//prodji kroz sve izbacene
				if (ig.matrix[v->getPosition()][(*iter)->getPosition()] == __INTERFERENCE__) {//ako su u smetnji
																							  // ako su susedi, trenutnoj promenljivoj ne moze da bude dodeljen prvi "slobodan" registar
					slobodni_registri.remove((*iter)->getAssignment());//izbaci registar iz slobodnih registara
				}
			}
		}
		izbacene.push_back(v);//izbaci proverenu promenljivu
		if (slobodni_registri.empty()) return false; //ako nema vise slobodnih registara vrati netacno (prekini izvrsavanje)
		else {
			Regs reg = slobodni_registri.back(); //ako ima slobodni registar
			slobodni_registri.clear(); //obrisi sve slobodne registre (gore ih opet dodaje)
			v->setAssignment(reg); //dodaj slobodni registar promenljivoj...
		}

	}//vrti petlju dokle god ima promenljivih na steku
	izbacene.clear(); //vrati sve na pocetno stanje..
	return true;//vrati tacno
}

bool checkResourceAllocation(InterferenceGraph ig) {
	Variable var1, var2;

	for (int i = 0; i < ig.matrix.size(); i++) {
		for (int j = 0; j < ig.matrix.size(); j++)
			if (ig.matrix[i][j] == __INTERFERENCE__) {

				for (auto it = ig.variables->begin(); it != ig.variables->end(); it++) {
					if ((*it)->getPosition() == i) { var1 = *(*it); }
					if ((*it)->getPosition() == j) { var2 = *(*it); }
				}

				if (var1.getAssignment() == var2.getAssignment()) return false;

			}
	}
	return true;

}