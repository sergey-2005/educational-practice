#include "WavWriter.h"
using namespace std;

void WavWriter::Save(const vector<float>& signal, const string& fileName, int sampleRate)
{
    ofstream file(fileName, ios::binary);
    if (!file.is_open())
    {
        cout << "Не удалось создать " << fileName << endl;
        return;
    }
    int16_t bitsPerSample = 16; // один звуковой отсчёт будет занимать 16 бит
    int16_t numchannels = 1;// моно
    int32_t byteRate = sampleRate * numchannels * bitsPerSample / 8;//кол-во байт в секунду
    int16_t blockAlign = numchannels * bitsPerSample / 8; //кол-во байт для одного сэмпла
    int32_t dataSize = static_cast<int32_t>(signal.size() * sizeof(int16_t));// объём данных
    int32_t chunkSize = 36 + dataSize;// объём файла. 36 = 44 байта - 8 первых байт, которые не ситаются
    //заполненение структуры файла, значала заголовок, потом данные
    file.write("RIFF", 4); // посимвольная запись в файл слова RIFF
    file.write(reinterpret_cast<char*>(&chunkSize), 4); // записываю размер файла
    file.write("WAVE", 4); // посимвольная запись в файл слова WAVE
    file.write("fmt ", 4); // посимвольная запись в файл слова fmt
    int32_t subchunk1Size = 16;
    int16_t audioFormat = 1;
    file.write(reinterpret_cast<char*>(&subchunk1Size), 4); // оставшийся размер подцепочки, начиная с этой позиции
    file.write(reinterpret_cast<char*>(&audioFormat), 2); // 1 означает линейное квантование
    file.write(reinterpret_cast<char*>(&numchannels), 2); // моно
    file.write(reinterpret_cast<char*>(&sampleRate), 4); // частота дискретизации
    file.write(reinterpret_cast<char*>(&byteRate), 4); // кол-во байт переданных за секунду воспроизведения
    file.write(reinterpret_cast<char*>(&blockAlign), 2); // кол-во байт для одного сэмпла
    file.write(reinterpret_cast<char*>(&bitsPerSample), 2); // кол-во бит в сэмпле
    // data
    file.write("data", 4); // посимвольная запись в файл слова data
    file.write(reinterpret_cast<char*>(&dataSize), 4); //количество байт в области данных
    for (float sample : signal)
    {
        //преобразование типов
        int16_t pcm = static_cast<int16_t>(sample * 32767);
        // pcm не объявлена, как const
        file.write(reinterpret_cast<char*>(&pcm), sizeof(int16_t));
    }
    file.close();
}