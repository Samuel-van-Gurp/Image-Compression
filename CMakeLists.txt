cmake_minimum_required(VERSION 3.10)
project(MyCMakeProject VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenCV_DIR "C:/Users/svangurp/opencv/build")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)
# Specify the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add the executable target using the source file(s)
add_executable(MyCMakeProject src/main.cpp
                              src/Image.cpp
                              src/Compressor.cpp)

target_link_libraries(MyCMakeProject ${OpenCV_LIBS})
