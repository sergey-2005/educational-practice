#include "Normalize.h"
using namespace std;

vector<float> Normalize(const vector<float>& signal)
{
    vector<float> result = signal;

    if (result.empty())
        return result;
    // fabs возвращает модуь числа
    float maxValue = fabs(result[0]);
    // поиск максимума
    for (int i = 0; i < result.size(); i++)
    {
        if (fabs(result[i]) > maxValue)
            maxValue = fabs(result[i]);
    }

    if (maxValue == 0.0f)
        return result;

    for (int i = 0; i < result.size(); i++)
    {
        result[i] /= maxValue;
    }

    return result;
}