#pragma once
#include "Demodulator.h"
#include <cmath>
using namespace std;

class DemodulatorAM : public Demodulator
{
public:
    vector<float> Demodulate(const vector<Complex>& signal);
};