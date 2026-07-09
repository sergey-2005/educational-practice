#include "FileManager.h"
using namespace std;

vector<Complex> FileManager::LoadSignal(const string& fileName)
{
    vector<Complex> signal;
    ifstream file(fileName, ios::binary);//открыть для чтения файл, как бинарный
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл " << fileName << endl;
        return signal;
    }
    int32_t rawI;
    int32_t rawQ;
    while ((file.read(reinterpret_cast<char*>(&rawI), sizeof(int32_t))) && file.read(reinterpret_cast<char*>(&rawQ), sizeof(int32_t)))
    {
        Complex sample;
        sample.i = static_cast<float>(rawI) / 2147483648.0f;
        sample.q = static_cast<float>(rawQ) / 2147483648.0f;
        signal.push_back(sample);
    }
    file.close();
    return signal;
}

void FileManager::SaveSignal(const vector<float>& signal, const string& fileName)
{
    ofstream file(fileName, ios::binary);
    if (!file.is_open())
    {
        cout << "Не удалось создать файл " << fileName << endl;
        return;
    }
    // reinterpret_cast - считывание памяти этой переменной, как набор байтов для записи в файл, т.к write записывает только их, а надо signal.size() * sizeof(float)
    file.write(reinterpret_cast<const char*>(signal.data()), signal.size() * sizeof(float));
    file.close();
}

