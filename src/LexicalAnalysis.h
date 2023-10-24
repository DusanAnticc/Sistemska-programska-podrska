#ifndef __LEXICAL_ANALYSIS__
#define __LEXICAL_ANALYSIS__

#include <fstream>
#include <vector>
#include <list>

#include "Token.h"
#include "FiniteStateMachine.h"


typedef std::list<Token> TokenList;


class LexicalAnalysis
{
public:

	//inicijalizacija leksickog analizatora i FSM
	void initialize();

	//izvrsavanje leksicke analize
	bool Do();

	//citanje input fajla
	bool readInputFile(std::string fileName);

	/**
	* Use this function to get next lexical token from program source code.
	*
	* @return next lexical token in program source code
	*/
	Token getNextTokenLex();


	/*
		lista tokena procitana iz source code
		return list of tekens
	*/
	TokenList& getTokenList();

	//ispis liste tokena
	void printTokens();

	//baratanje erorom
	void printLexError();

private:
	//input fajl koji sadrzi tekst za analizu
	std::ifstream inputFile;

	//buffer sa sadrzajem input fajla
	std::vector<char> programBuffer;

	//trenutna pozicija programskog buffera
	unsigned int programBufferPosition;

	//Finite state machine objekat
	FiniteStateMachine fsm;

	//lista parsiranih tokena
	TokenList tokenList;

	//ako se desi error prilikom parsiranja
	Token errorToken;

	//ispis testne liste
	void printMessageHeader();
};

#endif
