#pragma once
#include "../State.hpp"

class MergeSortState : public State
{
public:
	enum instr { boundsCheck, sortLeft, sortRight, merge, none };

	MergeSortState(MergeSortState::instr i, int left, int right)
		: nextInstruction(i), left(left), right(right) {}
	
	instr nextInstruction;
	int left;
	int right;
};