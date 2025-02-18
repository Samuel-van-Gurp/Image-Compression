#ifndef JPEGQUANTIZATIONTABLE_H
#define JPEGQUANTIZATIONTABLE_H

#include <vector>

struct QuantizationTable
{
    // Static member variables for different compression levels
    static const std::vector<std::vector<int>> lowCompressionTable;
    static const std::vector<std::vector<int>> mediumCompressionTable;
    static const std::vector<std::vector<int>> highCompressionTable;
    static const std::vector<std::vector<int>> veryHighCompressionTable;
    static const std::vector<std::vector<int>> ultraHighCompressionTable;
};

#endif // JPEGQUANTIZATIONTABLE_H