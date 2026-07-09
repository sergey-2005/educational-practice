#pragma once

#include <vector>
#include "Complex.h"
using namespace std;

class Demodulator
{
public:
    //чисто виртуальная, нету реализации
    virtual vector<float> Demodulate(const vector<Complex>& signal) = 0;
    //диструктор
    virtual ~Demodulator() {};
};
