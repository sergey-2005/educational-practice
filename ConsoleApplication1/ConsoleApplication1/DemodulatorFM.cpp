#include "DemodulatorFM.h"
using namespace std;

vector<float> DemodulatorFM::Demodulate(const vector<Complex>& signal)
{
    //предотвращение ошибки если переданный вектор пустой
    if (signal.empty())
        return {};
    vector<float> phase;
    int N = static_cast<int>(signal.size());
    for (int i = 0; i < N; i++)
    {
        phase.push_back(atan2(signal[i].q, signal[i].i));
    }
    vector<float> unwrapped(N);
    unwrapped[0] = phase[0];
    const float PI = 3.14159265358979323846f;
    const float TWO_PI = 2.0f * PI;
    //накопление фазового сдвига
    float offset = 0.0f;
    for (int i = 1; i < N; i++)
    {
        float delta = phase[i] - phase[i - 1];
        if (delta > PI)
            offset -= TWO_PI;
        else if (delta < -PI)
            offset += TWO_PI;
        unwrapped[i] = phase[i] + offset;
    }

    vector<float> demod(N - 1);

    for (int i = 1; i < N; i++)
    {
        demod[i - 1] = unwrapped[i] - unwrapped[i - 1];
    }
    double mean = 0.0;
    for (int i = 0; i < demod.size(); i++)
    {
        mean += demod[i];
    }
    mean /= demod.size();

    for (int i = 0; i < demod.size(); i++)
    {
        demod[i] -= static_cast<float>(mean);
    }
    return demod;

}