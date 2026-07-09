#include <gtest/gtest.h>
#include "DemodulatorFM.h"

TEST(DemodulatorFM, EmptySignal)
{
    DemodulatorFM demod;

    std::vector<Complex> signal;

    auto result = demod.Demodulate(signal);

    EXPECT_TRUE(result.empty());
}

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

    auto result = demod.Demodulate(signal);

    EXPECT_EQ(result.size(), signal.size() - 1);
}