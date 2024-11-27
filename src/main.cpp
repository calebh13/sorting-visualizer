#include "SortingWrapper.hpp"

int main(void)
{
    srand((unsigned int)time(nullptr));
    SortingWrapper wrapper;
    wrapper.getInput();
    wrapper.runAlg();
}