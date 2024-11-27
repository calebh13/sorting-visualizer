#include "InsertionSorter.hpp"

// Returns true if array is fully sorted, false otherwise
bool InsertionSorter::sort(void)
{
    bool swap = false;
    while (!s.empty())
    {
        InsertionSortState* state = dynamic_cast<InsertionSortState*>(s.top());
        switch (state->nextInstruction)
        {
        case InsertionSortState::instr::boundsCheck:
            if (state->i <= state->right)
            {
                state->tmp = arr[state->i], state->j = state->i;
                state->nextInstruction = InsertionSortState::instr::rightShift;
            }
            else
                state->nextInstruction = InsertionSortState::instr::none;
            break;
        case InsertionSortState::rightShift:
            if (state->j > state->left && state->tmp < arr[state->j - 1])
            {
                swap = (arr[state->j] != arr[state->j - 1]);
                arr[state->j] = arr[state->j - 1];
                state->j--;
                if (swap) return false; // an actual swap occurred, so return, but arr is still not sorted
            }
            else
                state->nextInstruction = InsertionSortState::instr::tmpPlace;
            break;
        case InsertionSortState::tmpPlace:
            swap = (arr[state->j] != state->tmp);
            arr[state->j] = state->tmp;
            state->nextInstruction = InsertionSortState::instr::endLoop;
            if (swap) return false; 
            break;
        case InsertionSortState::endLoop:
            state->i++;
            state->nextInstruction = InsertionSortState::instr::boundsCheck;
            break;
        case InsertionSortState::instr::none:
            s.pop();
            break;
        }
    }
    return s.empty();
}

void InsertionSorter::changeBounds(int left, int right)
{
    while (!s.empty()) s.pop();
    s.push(new InsertionSortState(InsertionSortState::instr::boundsCheck, left, right));
}
