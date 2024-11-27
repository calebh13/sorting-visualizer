#include "MergeSorter.hpp"

// Returns true if arr is fully sorted, false otherwise
bool MergeSorter::sort(void)
{
    bool arrUpdated = false;
    while (!arrUpdated && !s.empty())
    {
        // todo: change this to be more like pa9 and quicksorter code (if != nullptr)
        MergeSortState* state = dynamic_cast<MergeSortState*>(s.top());
        if (state == nullptr)
        {
            // If it's a nullptr, we need to jump straight back into merging
            arrUpdated = MergeSorter::merge();
        }
        else
        {
            size_t mid = (state->left + state->right) / 2;
            switch (state->nextInstruction)
            {
            case MergeSortState::instr::boundsCheck:
                if (state->left >= state->right) s.pop();
                else state->nextInstruction = MergeSortState::instr::sortLeft;
                break;
            case MergeSortState::instr::sortLeft:
                s.push(new MergeSortState(MergeSortState::instr::boundsCheck, state->left, mid));
                state->nextInstruction = MergeSortState::instr::sortRight;
                break;
            case MergeSortState::instr::sortRight:
                s.push(new MergeSortState(MergeSortState::instr::boundsCheck, mid + 1, state->right));
                state->nextInstruction = MergeSortState::instr::merge;
                break;
            case MergeSortState::instr::merge:
                s.push(new MergeState(arr, MergeState::instr::mainLoop, state->left, mid, state->right));
                state->nextInstruction = MergeSortState::instr::none;
                break;
            case MergeSortState::instr::none:
                s.pop();
                break;
            }
        }
    }
    return s.empty();
}

// Maybe make this return a bool that shows if it needs updating
// that way we don't have unnecessary updates after every complete merge of 2 subarrays
bool MergeSorter::merge(void)
{
    // remember to make this a while loop as well
    MergeState* state = dynamic_cast<MergeState*>(s.top());
    while (true)
    {
        switch (state->nextInstruction)
        {
        case MergeState::instr::mainLoop:
            if (state->leftIndex < state->leftArr.size() && state->rightIndex < state->rightArr.size())
            {
                if (state->leftArr[state->leftIndex] <= state->rightArr[state->rightIndex])
                    arr[state->mainIndex++] = state->leftArr[state->leftIndex++];
                else
                    arr[state->mainIndex++] = state->rightArr[state->rightIndex++];
                return true;
            }
            else
                state->nextInstruction = MergeState::instr::leftSubarrayCopy;
            break;
        case MergeState::instr::leftSubarrayCopy:
            if (state->leftIndex < state->leftArr.size())
            {
                arr[state->mainIndex++] = state->leftArr[state->leftIndex++];
                return true;
            }
            else
                state->nextInstruction = MergeState::instr::rightSubarrayCopy;
            break;
        case MergeState::instr::rightSubarrayCopy:
            if (state->rightIndex < state->rightArr.size())
            {
                arr[state->mainIndex++] = state->rightArr[state->rightIndex++];
                return true;
            }
            else
            {
                s.pop();
                return false;
            }
            break;
        }
    }
}