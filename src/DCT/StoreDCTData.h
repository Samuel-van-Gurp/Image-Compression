#ifndef STORE_DCT_DATA_H
#define STORE_DCT_DATA_H

#include "CompressedDCTImageHolder.h"
#include "BaseCompressedImageHolder.h" 
#include "BaseStoreData.h"
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

class StoreDCTData : public BaseStoreData
{

public:
    void writeToBinary(const std::string &fileName, const std::string &filePath, const BaseCompressedImageHolder &compressedImageHolder) override;

    std::unique_ptr<BaseCompressedImageHolder> readFromBinary(const std::string &fileName, const std::string &filePath) override;

private:
    static const std::string FILE_EXTENSION;

    // write functions
    void writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const;
    void writeQuantizationTable(std::ofstream &outFile, const std::vector<std::vector<int>> &quantizationTable);
    void writeCompressedImage(std::ofstream &outFile, const std::vector<std::vector<std::pair<float, int>>> &compressedImage);

    // read functions
    std::pair<int, int> readOriginalImageSize(std::ifstream &inFile);
    std::vector<std::vector<int>> readQuantizationTable(std::ifstream &inFile);
    std::vector<std::vector<std::pair<float, int>>> readCompressedImage(std::ifstream &inFile);

    void validateFileExtension(const std::string &fileName) const;
};

#endif