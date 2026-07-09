add_executable(UnitTests

    main.cpp
    Tests.cpp

    test_filter.cpp
    test_normalize.cpp
    test_downsample.cpp
    test_filemanager.cpp
    test_demodulatorAM.cpp
    test_demodulatorFM.cpp

    ../ConsoleApplication1/Filter.cpp
    ../ConsoleApplication1/Normalize.cpp
    ../ConsoleApplication1/Downsample.cpp
    ../ConsoleApplication1/FileManager.cpp
    ../ConsoleApplication1/DemodulatorAM.cpp
    ../ConsoleApplication1/DemodulatorFM.cpp
    ../ConsoleApplication1/WavWriter.cpp
)

target_include_directories(UnitTests PRIVATE
    ../ConsoleApplication1
)

target_link_libraries(UnitTests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTests)