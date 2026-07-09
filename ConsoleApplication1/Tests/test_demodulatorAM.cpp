#include <gtest/gtest.h>
#include "DemodulatorAM.h"
using namespace std;

//Проверяет обработку пустого входного сигнала
TEST(DemodulatorAM, EmptySignal)
{
    DemodulatorAM demod;

    vector<Complex> signal;

     vector<float> result = demod.Demodulate(signal);

    EXPECT_TRUE(result.empty());
}

//Проверяет сохранение размера сигнала после демодуляци
TEST(DemodulatorAM, SizeCheck)
{
    DemodulatorAM demod;

    vector<Complex> signal =
    {
        {1,0},
        {0,1},
        {1,1}
    };

    vector<float> result = demod.Demodulate(signal);

    EXPECT_EQ(result.size(), signal.size());
}

// Проверяет демодуляцию сигнала с постоянной амплитудой
TEST(DemodulatorAM, ConstantAmplitude)
{
    DemodulatorAM demod;

    vector<Complex> signal =
    {
        {3, 4},
        {3, 4},
        {3, 4}
    };

    vector<float> result = demod.Demodulate(signal);

    EXPECT_FLOAT_EQ(result[0], 5.0f);
    EXPECT_FLOAT_EQ(result[1], 5.0f);
    EXPECT_FLOAT_EQ(result[2], 5.0f);
}
