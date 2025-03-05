#ifndef JPEGQUANTIZATIONTABLE_H
#define JPEGQUANTIZATIONTABLE_H

#include "CompressionLevel.h"
#include <vector>
#include <string>

struct QuantizationTable
{
    // Static member variables for different compression levels
    static const std::vector<std::vector<int>> identityCompressionTable;
    static const std::vector<std::vector<int>> lowCompressionTable;
    static const std::vector<std::vector<int>> mediumCompressionTable;
    static const std::vector<std::vector<int>> highCompressionTable;
    static const std::vector<std::vector<int>> veryHighCompressionTable;
    static const std::vector<std::vector<int>> ultraHighCompressionTable;

    // translate the compression level to the corresponding quantization table
    static const std::vector<std::vector<int>> &getQuantizationTable(const CompressionLevel &compressionLevel);
    const CompressionLevel getCompressionLevel(const std::string &compressionLevel);
};

#endif // JPEGQUANTIZATIONTABLE_H