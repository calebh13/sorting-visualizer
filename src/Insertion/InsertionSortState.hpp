#pragma once
#include "../State.hpp"

class InsertionSortState : public State
{
public:
	enum instr { boundsCheck, rightShift, tmpPlace, endLoop, none };

	InsertionSortState(InsertionSortState::instr inst, int left, int right, int i = 0, int j = 0, int tmp = 0)
		: nextInstruction(inst), left(left), right(right), i(i), j(j), tmp(tmp) {}
	
	instr nextInstruction;
	int left, right, i, j, tmp;
};