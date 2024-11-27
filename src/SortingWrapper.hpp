#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <iostream>

#include "Merge/MergeSorter.hpp"
#include "Quick/QuickSorter.hpp"

#define uint unsigned int

class SortingWrapper
{

public:
	enum algorithm { insertion, mergesort, quicksort, _default };

	SortingWrapper(int size = 2500, algorithm alg = algorithm::_default, int fps = -1, int max_val = 50000)
		: list(size), rectList(size), size(size), alg(alg), fps(fps), max_val(max_val) {}

	void getInput(void);
	void runAlg(void);

private:
	int size, fps, max_val;
	algorithm alg;

	std::vector<int> list;
	std::unordered_map<int, sf::RectangleShape*> rectList;
};