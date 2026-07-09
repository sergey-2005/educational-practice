#include <gtest/gtest.h>
#include "Normalize.h"
using namespace std;

//Проверяет, что максимальное по модулю значение становится равным 1
TEST(Normalize, MaximumEqualsOne)
{
    vector<float> signal =
    {
        2,
        -4,
        1
    };

     vector<float> result = Normalize(signal);

    EXPECT_FLOAT_EQ(result[1], -1.0f);
}

 //При передаче пустого вектора функция нормализации должна возвращать пустой вектор, а не выбрасывать исключение
TEST(Normalize, EmptySignal)
{
    vector<float> signal;

     vector<float> result = Normalize(signal);

    EXPECT_TRUE(result.empty());
}

 // Если все значения сигнала равны нулю, максимальное абсолютное значение равно 0. В этом случае функция должна вернуть вектор из нулей,
 // чтобы избежать деления на ноль
TEST(Normalize, AllZeros)
{
    vector<float> signal =
    {
        0.0f,
        0.0f,
        0.0f
    };

    vector<float> result = Normalize(signal);

    // Все значения должны остаться нулевыми
    EXPECT_EQ(result.size(), signal.size());
    for (float value : result)
    {
        EXPECT_FLOAT_EQ(value, 0.0f);
    }
}
