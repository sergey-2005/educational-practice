#include <gtest/gtest.h>
#include "Normalize.h"

TEST(Normalize, MaximumEqualsOne)
{
    std::vector<float> signal =
    {
        2,
        -4,
        1
    };

    auto result = Normalize(signal);

    EXPECT_FLOAT_EQ(result[1], -1.0f);
}

TEST(Normalize, EmptySignal)
{
    std::vector<float> signal;

    auto result = Normalize(signal);

    EXPECT_TRUE(result.empty());
}