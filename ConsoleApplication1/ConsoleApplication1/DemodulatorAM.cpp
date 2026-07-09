#include "DemodulatorAM.h"
using namespace std;

vector<float> DemodulatorAM::Demodulate(const vector<Complex>& signal)
{
    vector<float> result;
    int N = static_cast<int>(signal.size());
    for (int i = 0; i < N; i++)
    {
        result.push_back(sqrt(signal[i].i * signal[i].i + signal[i].q * signal[i].q));
    }
    return result;
}