#include <iostream>
#include <vector>
#include <string>
#include "Complex.h"
#include "FileManager.h"
#include "DemodulatorAM.h"
#include "DemodulatorFM.h"
#include "Filter.h"
#include "Normalize.h"
#include "Downsample.h"
#include "WavWriter.h"
using namespace std;

int main()
{
    FilterType type;
    while (true)
    {
        string choice;
        cout << "select a filter (r - recursive, n - non-recursive): ";
        // получаю сразувсю строку с учётов пробелов и прочих символов, которые cin не принимает
        getline(cin, choice);
        if (choice == "r")
        {
            type = FilterType::Recursive;
            break;
        }
        if (choice == "n")
        {
            type = FilterType::NonRecursive;
            break;
        }
        cout << "incorrect input\n";
    }
    // файл .bin
    FileManager fm;
    vector<Complex> fmsignal = fm.LoadSignal("file1EuropaPlus.bin");
    DemodulatorFM fmdemod;
    vector<float> fmAudio = fmdemod.Demodulate(fmsignal);
    Filter fmFilter(10, type);
    fmAudio = fmFilter.Process(fmAudio);
    fmAudio = Normalize(fmAudio);
    fmAudio = Downsample(fmAudio, 10);
    // для дальнейшей проверки через матлаб (на слух)
    fm.SaveSignal(fmAudio, "fm_audio.bin");
    // сохраняю .wav
    WavWriter writer;
    writer.Save(fmAudio, "fm_audio.wav", 50000);
    // файл .dat
    vector<Complex> amsignal = fm.LoadSignal("am_sound.dat");
    DemodulatorAM amDemod;
    vector<float> amAudio = amDemod.Demodulate(amsignal);
    Filter amFilter(5, type);
    amAudio = amFilter.Process(amAudio);
    amAudio = Normalize(amAudio);
    // для дальнейшей проверки через матлаб (на слух)
    fm.SaveSignal(amAudio, "am_audio.bin");
    // сохраняю .wav
    writer.Save(amAudio, "am_audio.wav", 32000);
    cout << "am_audio.wav and fm_audio.wav files have been created";
}