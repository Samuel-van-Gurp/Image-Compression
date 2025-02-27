cmake_minimum_required(VERSION 3.11)
project(MyCMakeProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32) # check that we are on windows
  set(OpenCV_DIR "C:/Users/svangurp/opencv/build")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)
# Specify the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Make a library of the main code
add_library(CompressionCalc STATIC 
                              src/Image.cpp
                              src/RunLengthEnoding.h

                              src/DFT/DFTCompressor.cpp
                              src/DFT/SparseRepresentation.cpp
                              src/DFT/StoringData.cpp
                              src/DFT/DFT.cpp
                              src/DFT/ComplexRowColumnValue.cpp

                              src/DCT/DCT.cpp
                              src/DCT/TwoDimDCT.cpp
                              src/DCT/ImageChopper.cpp
                              src/DCT/DCTCompression.cpp
                              src/DCT/DCTTransformationHandler.cpp
                              src/DCT/QuantizationTable.cpp
                              src/DCT/ZigzagDCTcoefficientsOrder.cpp
                              src/DCT/DCTEncoding.cpp
                              src/DCT/StoreDCTData.cpp
                              )

# make main executable and link it with the CompressionCalc and OpenCV
add_executable(MyCMakeProject src/main.cpp)
target_link_libraries(MyCMakeProject CompressionCalc ${OpenCV_LIBS})

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
    tests/test_DCTTransformationHandler.cpp
    tests/test_RunLengthEnoding.cpp
)

# Link GoogleTest and OpenCV to the test executable
target_link_libraries(MyTests PRIVATE gtest_main ${OpenCV_LIBS} CompressionCalc)

# Discover and register tests with CTest
include(GoogleTest)
gtest_discover_tests(MyTests)