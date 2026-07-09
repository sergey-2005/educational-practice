#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint> // для использования тиипов с фиксированным размером int32_t и int16_t
#include "Complex.h"
using namespace std;

class FileManager
{
public:
    vector<Complex> LoadSignal(const string& fileName);
    void SaveSignal(const vector<float>& signal, const string& fileName);
};