#pragma once
#include <cmath>
#include "Demodulator.h"
using namespace std;

class DemodulatorFM : public Demodulator
{
public:
    vector<float> Demodulate(const vector<Complex>& signal);
};