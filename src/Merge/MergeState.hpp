#pragma once
#include <vector>
#include "../State.hpp"
class MergeState : public State
{
public:
	enum instr { mainLoop, leftSubarrayCopy, rightSubarrayCopy };
	// figure out the weird 223 constructor thing.
	MergeState(std::vector<int>& parentArr, MergeState::instr i, int left, int mid, int right)
		: nextInstruction(i), leftIndex(0), rightIndex(0), mainIndex(left), left(left), mid(mid), right(right)
	{
		this->leftArr = std::vector<int>(parentArr.begin() + left, parentArr.begin() + mid + 1);
		this->rightArr = std::vector<int>(parentArr.begin() + mid + 1, parentArr.begin() + right + 1);
	}

	instr nextInstruction;
	std::vector<int> leftArr;
	std::vector<int> rightArr;
	int left, leftIndex, mid, right, rightIndex, mainIndex;
};