#include <gtest/gtest.h>
#include "DemodulatorAM.h"

TEST(DemodulatorAM, EmptySignal)
{
    DemodulatorAM demod;

    std::vector<Complex> signal;

    auto result = demod.Demodulate(signal);

    EXPECT_TRUE(result.empty());
}

TEST(DemodulatorAM, SizeCheck)
{
    DemodulatorAM demod;

    std::vector<Complex> signal =
    {
        {1,0},
        {0,1},
        {1,1}
    };

    auto result = demod.Demodulate(signal);

    EXPECT_EQ(result.size(), signal.size());
}