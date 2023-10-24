#ifndef __CONSTANTS__
#define __CONSTANTS__

//stanja simbola
const int IDLE_STATE = 0;
const int START_STATE = 1;
const int INVALID_STATE = -2;

//broj stanja u FSM
const int NUM_STATES = 48;

//koliko ima karaktera
const int NUM_OF_CHARACTERS = 47;

//ukoliko ima smetnji izmedju instukcija
const int __INTERFERENCE__ = 1;

//nema smetnji
const int __EMPTY__ = 0;

//broj registara (boja)
const int __REG_NUMBER__ = 5;

//zivotni vijek
const int __DUMPS__ = 1;
const int __NO_DUMPS__ = 0;

//poravnanje za ljepsi ispis
const int LEFT_ALIGN = 20;
const int RIGHT_ALIGN = 25;

#endif
