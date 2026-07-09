#include <gtest/gtest.h>
#include "Filter.h"
using namespace std;

//Проверяет обработку пустого сигнала
TEST(Filter, EmptySignal)
{
    Filter filter(5, FilterType::Recursive);

    vector<float> signal;

    vector<float> result = filter.Process(signal);

    EXPECT_TRUE(result.empty());
}

//Проверяет обработку простого сигнала
TEST(Filter, SimpleSignal)
{
    Filter filter(3, FilterType::NonRecursive);

    vector<float> signal =
    {
        1,
        2,
        3,
        4,
        5
    };

    vector<float>  result = filter.Process(signal);

    EXPECT_EQ(result.size(), 3);
}

 //Рекурсивный фильтр использует предыдущие выходные значения, поэтому результат должен иметь ту же длину, что и входной сигнал
TEST(Filter, RecursiveFilterOutputSize)
{
    Filter filter(3, FilterType::Recursive);

    vector<float> signal = {1, 2, 3, 4, 5};

    vector<float> result = filter.Process(signal);

    EXPECT_EQ(result.size(), signal.size());
}

// Для нерекурсивного фильтра размер выходного сигнала должен быть: N - order + 1, где N - длина входного сигнала
TEST(Filter, NonRecursiveFilterOutputSize)
{
    Filter filter(3, FilterType::NonRecursive);

    vector<float> signal = {1, 2, 3, 4, 5, 6, 7};

    vector<float> result = filter.Process(signal);

    // Для order=3: 7 - 3 + 1 = 5
    EXPECT_EQ(result.size(), 5);
}

// Проверяет обработку сигнала длиной равной порядку фильтра При равенстве длин результат должен содержать один отсчет */
TEST(Filter, SignalEqualToOrder)
{
    Filter filter(3, FilterType::NonRecursive);

    vector<float> signal = {1, 2, 3};

    vector<float> result = filter.Process(signal);

    EXPECT_EQ(result.size(), 1);
}

 // Проверяет сохранение амплитуды при единичном коэффициенте усиления Если сумма коэффициентов фильтра = 1, амплитуда сигнала должна сохраняться
TEST(Filter, UnityGain)
{
    // Создаю фильтр с коэффициентами, дающими единичное усиление
    // Например, для фильтра 2-го порядка: [0.333, 0.333, 0.333]
    Filter filter(2, FilterType::NonRecursive);
    
    vector<float> signal = {3, 3, 3, 3, 3};

    vector<float> result = filter.Process(signal);

    // Для сигнала из троек результат должен быть ≈ 3
    for (float val : result)
    {
        EXPECT_NEAR(val, 3.0f, 0.001f);
    }
}
