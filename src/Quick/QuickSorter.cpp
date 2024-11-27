#include "QuickSorter.hpp"

bool QuickSorter::sort(void)
{
    bool arrUpdated = false;
    while (!arrUpdated && !s.empty())
    {
        QuickSortState* qstate = dynamic_cast<QuickSortState*>(s.top());
        if (qstate != nullptr)
        {
            switch (qstate->nextInstruction)
            {
            case QuickSortState::instr::boundsCheck:
                if (qstate->left + 10 <= qstate->right)
                    s.push(new Median3State(Median3State::instr::checkCenterAndLeft, qstate->left, qstate->right));
                else
                {
                    qstate->nextInstruction = QuickSortState::instr::insertionSort;
                    ins.changeBounds(qstate->left, qstate->right);
                }
                break;

            case QuickSortState::instr::whileLoop:
                while (arr[++qstate->i] < qstate->pivot); // gives arr[i] >= pivot
                while (qstate->pivot < arr[--qstate->j]); // gives arr[j] <= pivot
                if (qstate->i < qstate->j)
                {
                    std::swap(arr[qstate->i], arr[qstate->j]); // if they haven't crossed, swap
                    arrUpdated = (arr[qstate->i] != arr[qstate->j]);
                }
                else
                {
                    std::swap(arr[qstate->i], arr[qstate->right - 1]); // otherwise restore pivot
                    arrUpdated = (arr[qstate->i] != arr[qstate->right - 1]);
                    qstate->nextInstruction = QuickSortState::instr::sortLeft; // and begin sorting subarrays
                }
                break;

            case QuickSortState::sortLeft:
                s.push(new QuickSortState(QuickSortState::instr::boundsCheck, qstate->left, qstate->i - 1));
                qstate->nextInstruction = QuickSortState::instr::sortRight;
                break;

            case QuickSortState::sortRight:
                s.push(new QuickSortState(QuickSortState::instr::boundsCheck, qstate->i + 1, qstate->right));
                qstate->nextInstruction = QuickSortState::instr::none;
                break;

            case QuickSortState::instr::insertionSort:
                if (ins.sort()) // perform a single step of insertion sort, and if qstate subarray is now sorted
                    qstate->nextInstruction = QuickSortState::instr::none;
                arrUpdated = true;
                break;

            case QuickSortState::instr::none:
                s.pop();
                break;
            }
        }

        Median3State* mstate = nullptr;
        if(!s.empty()) mstate = dynamic_cast<Median3State*>(s.top());
        if (mstate != nullptr)
        {
            std::pair<int, bool> ret = median3();
            arrUpdated = true;
            if (ret.second)
            {
                QuickSortState* qstate = dynamic_cast<QuickSortState*>(s.top());
                qstate->pivot = ret.first;
                qstate->i = qstate->left;
                qstate->j = qstate->right - 1;
                qstate->nextInstruction = QuickSortState::instr::whileLoop;
            }
        }
    }

    return s.empty();
}

std::pair<int, bool> QuickSorter::median3(void)
{
    Median3State* state = dynamic_cast<Median3State*>(s.top());
    state->center = (state->left + state->right) / 2;
    while (true)
    {
        switch (state->nextInstruction)
        {
        case Median3State::instr::checkCenterAndLeft:
            state->nextInstruction = Median3State::instr::checkRightAndLeft;
            if (arr[state->center] < arr[state->left])
            {
                std::swap(arr[state->left], arr[state->center]);
                return std::pair<int, bool>(0, false);
            }
            break;
        case Median3State::instr::checkRightAndLeft:
            state->nextInstruction = Median3State::instr::checkRightAndCenter;
            if (arr[state->right] < arr[state->left])
            {
                std::swap(arr[state->left], arr[state->right]);
                return std::pair<int, bool>(0, false);
            }
            break;
        case Median3State::instr::checkRightAndCenter:
            state->nextInstruction = Median3State::instr::placePivot;
            if (arr[state->right] < arr[state->center])
            {
                std::swap(arr[state->center], arr[state->right]);
                return std::pair<int, bool>(0, false);
            }
            break;
        case Median3State::instr::placePivot:
            std::swap(arr[state->center], arr[state->right - 1]);
            s.pop();
            return std::pair<int, bool>(arr[state->right - 1], true);
            break;
        }
    }
}