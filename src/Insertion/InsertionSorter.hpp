#pragma once
#include "InsertionSortState.hpp"
#include "../Sorter.hpp"

class InsertionSorter : public Sorter
{
public:
	// If right is left as default value, it will default to size - 1
	InsertionSorter(std::vector<int>& arr, int left = 0, int right = -1) : Sorter(arr)
	{
		if (right == -1) right = arr.size() - 1;
		s.push(new InsertionSortState(InsertionSortState::instr::boundsCheck, left, right, left));
	};
	bool sort(void);
	void changeBounds(int left, int right);
};