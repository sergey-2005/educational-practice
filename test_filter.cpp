#include <gtest/gtest.h>
#include "Filter.h"

TEST(Filter, EmptySignal)
{
    Filter filter(5, FilterType::Recursive);

    std::vector<float> signal;

    auto result = filter.Process(signal);

    EXPECT_TRUE(result.empty());
}

TEST(Filter, SimpleSignal)
{
    Filter filter(3, FilterType::NonRecursive);

    std::vector<float> signal =
    {
        1,
        2,
        3,
        4,
        5
    };

    auto result = filter.Process(signal);

    EXPECT_EQ(result.size(), 3);
}