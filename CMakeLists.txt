cmake_minimum_required(VERSION 3.11)
project(MyCMakeProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32) # check that we are on windows
  set(OpenCV_DIR "C:/Users/svangurp/opencv/build")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)
# Specify the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add the executable target using the source file(s)
add_executable(MyCMakeProject src/main.cpp
                              src/Image.cpp
                              src/Compressor.cpp
                              src/SparseRepresentation.cpp
                              src/StoringData.cpp
                              src/DFT.cpp
                              src/ComplexRowColumnValue.cpp
                              src/DCT/DCT.cpp
                              src/DCT/TwoDimDCT.cpp
                              src/DCT/ImageChopper.cpp
                              src/DCT/DCTCompression.cpp
                              src/DCT/QuantizationTable.cpp)

target_link_libraries(MyCMakeProject ${OpenCV_LIBS})


# -------------------------------------------
# Google Test 
# -------------------------------------------

enable_testing()

# Fetch google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Force shared runtime (optional, but recommended on Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create a test executable
add_executable(MyTests
    tests/test_main.cpp
    tests/test_Image.cpp
    tests/test_Compressor.cpp
    tests/test_DFT.cpp
    tests/test_DCT.cpp
    tests/test_SparseRepresentation.cpp
    tests/test_TwoDimDCT.cpp
    tests/test_ImageChopper.cpp
    

    src/DCT/DCT.cpp
    src/DCT/ImageChopper.cpp
    src/Image.cpp         
    src/Compressor.cpp
    src/SparseRepresentation.cpp
    src/StoringData.cpp
    src/DFT.cpp
    src/DCT/TwoDimDCT.cpp
    src/ComplexRowColumnValue.cpp
    src/DCT/CompressionLevel.h
)

# Link GoogleTest and OpenCV to the test executable
target_link_libraries(MyTests PRIVATE gtest_main ${OpenCV_LIBS})

# Discover and register tests with CTest
include(GoogleTest)
gtest_discover_tests(MyTests)