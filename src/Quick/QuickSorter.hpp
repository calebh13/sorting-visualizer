#pragma once
#include "QuickSortState.hpp"
#include "Median3State.hpp"
#include "../Insertion/InsertionSorter.hpp"

class QuickSorter : public Sorter
{
public:
	QuickSorter(std::vector<int>& arr) : Sorter(arr), ins(arr)
	{
		s.push(new QuickSortState(QuickSortState::instr::boundsCheck, 0, arr.size() - 1));
	};
	bool sort(void);
private:
	std::pair<int, bool> median3(void);
	InsertionSorter ins;
};