#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum class FilterType
{
    Recursive,
    NonRecursive
};

class Filter
{
private:
    int windowSize;
    FilterType type;

    vector<float> RecursiveFilter(const vector<float>& signal);
    vector<float> NonRecursiveFilter(const vector<float>& signal);
public:
    Filter(int windowSize, FilterType type);
    vector<float> Process(const vector<float>& signal);
};

