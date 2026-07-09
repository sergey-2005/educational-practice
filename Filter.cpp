#include "Filter.h"
using namespace std;

vector<float> Filter::Process(const vector<float>& signal)
{
    if (type == FilterType::Recursive)
        return RecursiveFilter(signal);
    return NonRecursiveFilter(signal);
}

Filter::Filter(int size, FilterType t)
{
    windowSize = size;
    type = t;
}

vector<float> Filter::NonRecursiveFilter(const vector<float>& signal)
{
    vector<float> result;

    if (signal.size() < windowSize)
        return result;

    for (int i = windowSize - 1; i < signal.size(); i++)
    {
        float sum = 0.0f;
        for (int j = 0; j < windowSize; j++)
        {
            sum += signal[i - j];
        }
        result.push_back(sum / windowSize);
    }

    return result;
}

vector<float> Filter::RecursiveFilter(const vector<float>& signal)
{
    vector<float> result;

    if (signal.size() < windowSize)
        return result;

    float firstMean = 0.0f;

    for (int i = 0; i < windowSize; i++)
        firstMean += signal[i];

    firstMean /= windowSize;

    result.push_back(firstMean);

    float current = firstMean;

    for (int i = windowSize; i < signal.size(); i++)
    {
        current += (signal[i] - signal[i - windowSize]) / windowSize;
        result.push_back(current);
    }

    return result;
}