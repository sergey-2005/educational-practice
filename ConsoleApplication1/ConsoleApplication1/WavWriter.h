#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class WavWriter
{
public:
    void Save(const vector<float>& signal, const string& fileName, int sampleRate);
};
