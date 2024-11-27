#pragma once
#include <stack>
#include <vector>

class Sorter
{
public:
	Sorter(std::vector<int>& ref) : arr(ref) {}
	virtual bool sort(void) = 0;
protected:
	std::vector<int>& arr;
	std::stack<State*> s;
};