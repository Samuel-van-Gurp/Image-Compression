#include "QuantizationTable.h"

const std::vector<std::vector<int>> QuantizationTable::identityCompressionTable = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

const std::vector<std::vector<int>> QuantizationTable::lowCompressionTable = {
    {2, 1, 1, 2, 3, 5, 6, 7},
    {1, 1, 2, 3, 4, 7, 8, 7},
    {2, 2, 3, 4, 6, 8, 10, 8},
    {2, 3, 4, 6, 8, 14, 12, 9},
    {3, 4, 6, 8, 10, 17, 16, 12},
    {4, 6, 8, 10, 13, 17, 19, 15},
    {8, 10, 12, 14, 17, 20, 19, 16},
    {12, 15, 16, 17, 20, 18, 19, 17}};

const std::vector<std::vector<int>> QuantizationTable::mediumCompressionTable = {
    {4, 3, 3, 4, 6, 10, 13, 15},
    {3, 3, 4, 5, 7, 15, 16, 14},
    {4, 4, 5, 7, 10, 14, 17, 14},
    {4, 5, 6, 8, 13, 22, 20, 16},
    {5, 6, 10, 14, 16, 27, 25, 19},
    {6, 9, 14, 16, 20, 26, 29, 23},
    {12, 16, 19, 22, 26, 30, 29, 25},
    {18, 23, 24, 25, 28, 25, 26, 24}};

const std::vector<std::vector<int>> QuantizationTable::highCompressionTable = {
    {8, 6, 6, 8, 12, 20, 25, 30},
    {6, 6, 7, 10, 13, 29, 30, 28},
    {7, 7, 8, 12, 20, 28, 34, 28},
    {7, 9, 12, 16, 26, 44, 40, 31},
    {9, 12, 20, 28, 33, 55, 52, 39},
    {12, 18, 28, 32, 41, 52, 57, 46},
    {24, 32, 39, 44, 52, 61, 60, 50},
    {36, 46, 48, 50, 56, 50, 52, 49}};

const std::vector<std::vector<int>> QuantizationTable::veryHighCompressionTable = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99}};

const std::vector<std::vector<int>> QuantizationTable::ultraHighCompressionTable = {
    {64, 48, 40, 64, 96, 160, 204, 244},
    {48, 48, 56, 76, 104, 232, 240, 220},
    {56, 52, 64, 96, 160, 228, 276, 224},
    {56, 68, 88, 116, 204, 348, 320, 248},
    {72, 88, 148, 224, 272, 436, 412, 308},
    {96, 140, 220, 256, 324, 416, 452, 368},
    {196, 256, 312, 348, 412, 484, 480, 404},
    {288, 368, 380, 392, 448, 400, 412, 396}};

const std::vector<std::vector<int>> &QuantizationTable::getQuantizationTable(const CompressionLevel &compressionLevel)
{
    switch (compressionLevel)
    {
    case CompressionLevel::NONE:
        return identityCompressionTable;
    case CompressionLevel::LOW:
        return lowCompressionTable;
    case CompressionLevel::MEDIUM:
        return mediumCompressionTable;
    case CompressionLevel::HIGH:
        return highCompressionTable;
    case CompressionLevel::VERY_HIGH:
        return veryHighCompressionTable;
    case CompressionLevel::ULTRA_HIGH:
        return ultraHighCompressionTable;
    default:
        return identityCompressionTable;
    }
}

const CompressionLevel QuantizationTable::getCompressionLevel(const std::string &compressionLevel)
{
    if (compressionLevel == "NONE")
    {
        return CompressionLevel::NONE;
    }
    else if (compressionLevel == "LOW")
    {
        return CompressionLevel::LOW;
    }
    else if (compressionLevel == "MEDIUM")
    {
        return CompressionLevel::MEDIUM;
    }
    else if (compressionLevel == "HIGH")
    {
        return CompressionLevel::HIGH;
    }
    else if (compressionLevel == "VERY_HIGH")
    {
        return CompressionLevel::VERY_HIGH;
    }
    else if (compressionLevel == "ULTRA_HIGH")
    {
        return CompressionLevel::ULTRA_HIGH;
    }
    else
    {
        return CompressionLevel::NONE;
    }
}