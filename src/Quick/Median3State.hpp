#pragma once
#include "../State.hpp"

class Median3State : public State
{
public:
	enum instr { checkCenterAndLeft, checkRightAndLeft, checkRightAndCenter, placePivot };

	Median3State(Median3State::instr i, int left, int right)
		: nextInstruction(i), left(left), center((left + right / 2)), right(right) {}

	instr nextInstruction;
	int left, center, right;
};