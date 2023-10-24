#ifndef __FINITE_STATE_MACHINE__
#define __FINITE_STATE_MACHINE__

#include <map>
#include <string>

#include "Constants.h"
#include "Types.h"

typedef std::map<int, std::map<char, int>> StateMachine;

class FiniteStateMachine
{
public:
	//sljedece stanje, na osnovu trenutnog i transitionLetter
	int getNextState(int currentState, char transitionLetter);

	//inicijalizacija FSM (mora prije getNextLexToken)
	void initStateMachine();

	//tip tokena od stateNumber
	static TokenType getTokenType(int stateNumber);

private:
	/*
		State machine mapa, sadrzi moguca FSM stanja i transition matricu 
		map<StateNumber, map<TransitionCharacter, NextStateNumber>>
		map1 key:		state number
		map1 value:	map2 key -> next letter in the stream, identifies the transition to the next state
					map2 value -> next state number
	*/
	StateMachine stateMachine;

	//stanje u token(48)
	static const TokenType stateToTokenTable[NUM_STATES];

	//niz mogucih karaktera
	static const char supportedCharacters[NUM_OF_CHARACTERS];

	/*
	 State transition matrica:
		red predstavlja sadasnje stanje a colona sljedece
		Transition characters (symbols) za svaki prelaz su definisani pomocu supportedCharacters niza
		uvodimo stanja od A-M koja su definisana kao brojevi od 10-22 radi lakseg razumijevanja matrice
	
		primjer:
			row [1] -> stanje 1 mijenja se u stanje D ako je naredni karakter 0..9
	*/
	static const int stateMatrix[NUM_STATES][NUM_OF_CHARACTERS];
};

#endif
