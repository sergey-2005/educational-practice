#include <gtest/gtest.h>
#include "FileManager.h"
using namespace std;

//Проверяет обработку попытки загрузить несуществующий файл
TEST(FileManager, WrongFile)
{
    FileManager fm;

    vector<float> signal = fm.LoadSignal("unknown_file.bin");

    EXPECT_TRUE(signal.empty());
}

//Проверяет, что операция записи выполняется без ошибок
TEST(FileManager, SaveFile)
{
    FileManager fm;

    vector<float> signal =
    {
        1,
        2,
        3
    };

    EXPECT_NO_THROW(
        fm.SaveSignal(signal, "test.bin");
    );
}

//Проверяет сохранение пустого сигнала
TEST(FileManager, SaveEmptySignal)
{
    FileManager fm;
    
    vector<float> empty_signal;
    
    EXPECT_NO_THROW(fm.SaveSignal(empty_signal, "empty_signal.bin"));
    
    // Проверяем, что файл создан (но имеет размер 0)
    ifstream file("empty_signal.bin", ios::binary);
    EXPECT_TRUE(file.good());
    file.seekg(0, ios::end);
    EXPECT_EQ(file.tellg(), 0);
    file.close();
    
    // Удаляю тестовый файл
    remove("empty_signal.bin");
}
// Проверяет загрузку файла с некорректным размером
TEST(FileManager, CorruptedFile)
{
    FileManager fm;
    
    // Создаем файл с некорректным размером (7 байт)
    ofstream file("corrupted.bin", ios::binary);
    char data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    file.write(data, 7);
    file.close();
    
    // Функция должна либо вернуть частичные данные, либо пустой вектор
    vector<float>  signal = fm.LoadSignal("corrupted.bin");
    
    // Проверяем, что функция не падает
    EXPECT_TRUE(signal.empty() || signal.size() == 1);
    
    // Удаляем тестовый файл
    remove("corrupted.bin");
}

 //Функция должна корректно сохранять бинарные данные любого типа, включая отрицательные числа с плавающей точкой
TEST(FileManager, SaveNegativeValues)
{
    FileManager fm;
    
    vector<float> signal = {-5.0f, -3.2f, 0.0f, 1.5f, -2.7f};
    string filename = "negative.bin";
    
    EXPECT_NO_THROW(fm.SaveSignal(signal, filename));
    
    vector<float>  loaded = fm.LoadSignal(filename);
    
    EXPECT_EQ(loaded.size(), signal.size());
    for (size_t i = 0; i < loaded.size(); i++)
    {
        EXPECT_FLOAT_EQ(loaded[i], signal[i]);
    }
    
    remove(filename.c_str());
}

// * Проверяет, что функции сохранения и загрузки корректно работают с большими объемами данных и не вызывают переполнения памяти
TEST(FileManager, LargeSignal)
{
    FileManager fm;
    
    vector<float> signal;
    signal.reserve(100000);
    for (int i = 0; i < 100000; i++)
    {
        signal.push_back(static_cast<float>(i) / 1000.0f);
    }
    
    string filename = "large.bin";
    
    EXPECT_NO_THROW(fm.SaveSignal(signal, filename));
    
    vector<float>  loaded = fm.LoadSignal(filename);
    
    EXPECT_EQ(loaded.size(), signal.size());
    EXPECT_FLOAT_EQ(loaded[0], signal[0]);
    EXPECT_FLOAT_EQ(loaded[loaded.size() - 1], signal[signal.size() - 1]);
    
    remove(filename.c_str());
}
