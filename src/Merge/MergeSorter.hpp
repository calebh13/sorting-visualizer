#pragma once
#include "MergeSortState.hpp"
#include "MergeState.hpp"
#include "../Sorter.hpp"

class MergeSorter : public Sorter
{
public:
	MergeSorter(std::vector<int>& arr) : Sorter(arr) 
	{
		s.push(new MergeSortState(MergeSortState::instr::boundsCheck, 0, arr.size() - 1));
	}
	bool sort(void);
private:
	bool merge(void);
};