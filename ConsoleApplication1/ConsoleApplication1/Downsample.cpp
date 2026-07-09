#include "Downsample.h"
using namespace std;

vector<float> Downsample(const vector<float>& signal, int factor)
{
    vector<float> result;

    if (factor <= 0)
        return result;

    for (int i = 0; i < signal.size(); i += factor)
    {
        result.push_back(signal[i]);
    }

    return result;
}
