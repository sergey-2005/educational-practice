#include <gtest/gtest.h>
#include "DemodulatorFM.h"
using namespace std;

//Проверяет обработку пустого входного сигнала
TEST(DemodulatorFM, EmptySignal)
{
    DemodulatorFM demod;

    std::vector<Complex> signal;

    vector<float> result = demod.Demodulate(signal);

    EXPECT_TRUE(result.empty());
}

//Проверяет размер выходного сигнала при FM-демодуляции
TEST(DemodulatorFM, OutputSize)
{
    DemodulatorFM demod;

    std::vector<Complex> signal =
    {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1}
    };

    vector<float> result = demod.Demodulate(signal);

    EXPECT_EQ(result.size(), signal.size() - 1);
}

//Проверяет демодуляцию сигнала с постоянной фазой
TEST(DemodulatorFM, ConstantPhase)
{
    DemodulatorFM demod;

    vector<Complex> signal =
    {
        {1, 0},
        {1, 0},
        {1, 0},
        {1, 0}
    };

    vector<float> result = demod.Demodulate(signal);

    for (float value : result)
    {
        EXPECT_FLOAT_EQ(value, 0.0f);
    }
}


//Проверяет обработку сигнала из одного отсчета
TEST(DemodulatorFM, OneSample)
{
    DemodulatorFM demod;

    vector<Complex> signal =
    {
        {1, 0}
    };

    vector<float> result = demod.Demodulate(signal);

    EXPECT_TRUE(result.empty());
}
