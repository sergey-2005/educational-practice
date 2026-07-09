#include <gtest/gtest.h>
#include "Downsample.h"
using namespace std;

//Для сигнала из 6 элементов и коэффициента 2 ожидается результат из 3 элементов
TEST(Downsample, SizeReduction)
{
    vector<float> signal =
    {
        1,2,3,4,5,6
    };

    vector<float> result = Downsample(signal, 2);

    EXPECT_EQ(result.size(), 3);
}

//Проверяет обработку некорректного коэффициента децимации (0) При коэффициенте 0 функция должна возвращать пустой вектор
TEST(Downsample, WrongFactor)
{
    vector<float> signal =
    {
        1,2,3
    };

    vector<float> result = Downsample(signal, 0);

    EXPECT_TRUE(result.empty());
}

// При передаче пустого вектора функция должна возвращать пустой вектор
TEST(Downsample, EmptySignal)
{
    vector<float> signal;

    vector<float> result = Downsample(signal, 2);

    EXPECT_TRUE(result.empty());
}

//Если функция берет каждый второй отсче
TEST(Downsample, CorrectValues)
{
    vector<float> signal =
    {
        1, 2, 3, 4, 5, 6
    };

    vector<float> result = Downsample(signal, 2);

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 5);
}

//Коэффициент 1
TEST(Downsample, FactorOne)
{
    vector<float> signal =
    {
        1, 2, 3
    };

    vector<float> result = Downsample(signal, 1);

    EXPECT_EQ(result, signal);
}

//Коэффициент больше длины сигнала
TEST(Downsample, LargeFactor)
{
    vector<float> signal =
    {
        1, 2, 3
    };

    vector<float> result = Downsample(signal, 10);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 1);
}
