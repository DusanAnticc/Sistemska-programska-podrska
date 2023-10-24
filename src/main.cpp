#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "ControlFlowGraph.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"
#include "ResourceAllocation.h"
#include "FileHandler.h"

Variables variables;
Instructions instructions;

using namespace std;


int main(int argc, char *argv[])
{
	try {
		FileHandler fileHandler;

		if (argc == 3) {
			fileHandler.setInput(argv[1]);
			fileHandler.setOutput(argv[2]);
		}
		else if (argc == 2) {
			fileHandler.setInput(argv[1]);
		}

		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileHandler.getInput()))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal) {
			cout << "\n\nLexical analysis finished successfully!" << endl << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syntax(lex);

		retVal = syntax.Do();

		if (retVal) {
			cout << "\n\nSyntax analysis finished successfully!" << endl << endl;
			syntax.printInstructions();
		}

		else throw runtime_error("\n\nException! Syntax analysis failed!\n");


		defineDefUse();
		defineSuccPred();
		livenessAnalysis();

		InterferenceGraph ig = makeInterferenceGraph();
		ig.printInterferenceMatrix();

		SimplificationStack* stack = doSimplification(ig, __REG_NUMBER__);

		doResourceAllocation(*stack, ig);
		if (checkResourceAllocation(ig)) {
			cout << "\n\nResource allocation is successfull!\n" << endl;
			syntax.printVariables();
		}
		else throw runtime_error("\n\nException! Resource allocation failed!\n");


		fileHandler.writeToFile();

	}
	catch (const SyntaxAnalysis::UninitializedVariable& excp) {
		cerr << excp.what() << endl;
	}
	catch (const SyntaxAnalysis::UndeclaredLabel& excp) {
		cerr << excp.what() << endl;
	}
	catch (const SyntaxAnalysis::LabelExists& excp) {
		cerr << excp.what() << endl;
	}
	catch (const SyntaxAnalysis::VariableExists& excp) {
		cerr << excp.what() << endl;
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
	}
	system("PAUSE");
}
