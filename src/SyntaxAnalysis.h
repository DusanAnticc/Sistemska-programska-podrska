#ifndef SYNTAX_ANALYSIS
#define SYNTAX_ANALYSIS

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

extern Variables variables;
extern Instructions instructions;

class SyntaxAnalysis
{
private:

	int currentPosition;
	int currentRegVariablePosition;

	
   //Reference to lexical analysis module	
	LexicalAnalysis& lexicalAnalysis;

	//iterarot na token listu koji predstaclja izlaz iz leksicke analize
	TokenList::iterator tokenIterator;

	//token sa kojim radimo
	Token currentToken;

	//neterminalni Q
	void q();

	//neterminalni S
	void s();

	//neterminalni L
	void l();

	//neterminalni E
	void e();

	//sintaksna greska
	bool errorFound;
public:

	vector<string> labels;

	bool labelExists(string);

	bool variableExists(string);

	struct UninitializedVariable : std::runtime_error {
		UninitializedVariable(string s) : runtime_error("\n\nUndefined variable " + s + " is being used!\n\n") {}
	};

	struct UndeclaredLabel : std::runtime_error {
		UndeclaredLabel(string s) : runtime_error("\n\nUndeclared label " + s + " is being used!\n\n") {}
	};

	struct LabelExists : std::runtime_error {
		LabelExists(string s) : runtime_error("\n\nLabels and functions must not have the same name " + s + "!<<\n\n") {}
	};

	struct VariableExists : std::runtime_error {
		VariableExists(string s) : runtime_error("\n\nRedefinition of variable " + s + " is not allowed !\n\n") {}
	};

	//konstruktor
	SyntaxAnalysis(LexicalAnalysis& lex);

	//metoda koja vrsi leksicku analizu
	bool Do();

	//ispis tokena koji je izazvao sintaksnu gresku
	void printSyntaxError(Token& token);

	/*
	jede trenutni token ako mu je tip "t"
	u protivnom greska
	
	 param[in] - t - ocekivani tip tokena
	*/
	void eat(TokenType t);

	//vraca sljedeci token iz liste tokena
	Token getNextToken();
	Variable* getVariable(string name);

	void printVariables();
	void printInstructions();
};

#endif