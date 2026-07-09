#include <gtest/gtest.h>
#include "Downsample.h"

TEST(Downsample, SizeReduction)
{
    std::vector<float> signal =
    {
        1,2,3,4,5,6
    };

    auto result = Downsample(signal, 2);

    EXPECT_EQ(result.size(), 3);
}

TEST(Downsample, WrongFactor)
{
    std::vector<float> signal =
    {
        1,2,3
    };

    auto result = Downsample(signal, 0);

    EXPECT_TRUE(result.empty());
}