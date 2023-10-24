#pragma once
#ifndef LIVENESS_ANALYSIS
#define LIVENESS_ANALYSIS

#include "IR.h"

extern Instructions instructions;
extern Variables variables;

bool isEqual(Variables first, Variables second);

void livenessAnalysis();

#endif