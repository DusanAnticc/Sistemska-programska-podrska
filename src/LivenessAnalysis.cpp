#include "LivenessAnalysis.h"

bool isEqual(Variables first, Variables second) {
	bool ret = true;

	if (first.size() != second.size()) return false;

	for (auto it = first.begin(), it2 = second.begin(); it != first.end(), it2 != second.end(); it++, it2++) {
		if ((*it)->getName() != (*it2)->getName()) ret = false;
	}
	return ret;
}

void livenessAnalysis()
{
	Variables* in = new Variables;
	Variables* out = new Variables;

	Instructions::iterator it2;
	Variables::iterator itV;
	Variables::iterator itV2;
	Variables inP;
	Variables outP;

	do {

		for (auto it = instructions.rbegin(); it != instructions.rend(); ++it) {

			in = (*it)->getIn();
			out = (*it)->getOut();

			inP.clear();
			for (auto o = in->begin(); o != in->end(); o++) inP.push_back(*o);

			outP.clear();
			for (auto l = out->begin(); l != out->end(); l++) outP.push_back(*l);

			//OUT

			it2 = (*it)->getSucc()->begin();
			for (; it2 != (*it)->getSucc()->end(); it2++) {

				for (itV = (*it2)->getIn()->begin(); itV != (*it2)->getIn()->end(); itV++) {
					out->push_back(*itV);
				}
			}
			out->sort();
			out->unique();

			//IN

			//USE
			for (itV = (*it)->getUse()->begin(); itV != (*it)->getUse()->end(); itV++) {

				in->push_back(*itV);
			}
			//OUT - DEF
			bool minus;
			for (itV = out->begin(); itV != out->end(); itV++) {
				minus = true;
				for (itV2 = (*it)->getDef()->begin(); itV2 != (*it)->getDef()->end(); itV2++) {
					if (*itV == *itV2) {
						minus = false;
						break;
					}
				}
				if (minus) in->push_back(*itV);
			}

			in->sort();
			in->unique();
		}

	} while (!isEqual(inP, *in) || !isEqual(outP, *out));

}