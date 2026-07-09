#include <gtest/gtest.h>
#include "FileManager.h"

TEST(FileManager, WrongFile)
{
    FileManager fm;

    auto signal = fm.LoadSignal("unknown_file.bin");

    EXPECT_TRUE(signal.empty());
}

TEST(FileManager, SaveFile)
{
    FileManager fm;

    std::vector<float> signal =
    {
        1,
        2,
        3
    };

    EXPECT_NO_THROW(
        fm.SaveSignal(signal, "test.bin");
    );
}