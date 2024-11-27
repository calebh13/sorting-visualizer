#pragma once
#include "../State.hpp"
#include "../Insertion/InsertionSorter.hpp"

class QuickSortState : public State
{
public:
	enum instr { boundsCheck, whileLoop, sortLeft, sortRight, insertionSort, none };

	QuickSortState(QuickSortState::instr inst, int left, int right, int i = 0, int j = 0, int pivot = 0)
		: nextInstruction(inst), left(left), right(right), i(i), j(j), pivot(pivot) {}

	instr nextInstruction;
	int left, right, i, j, pivot;
};