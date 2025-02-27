#include "StoreDCTData.h"

const std::string StoreDCTData::FILE_EXTENSION = ".samuelDCT";

void StoreDCTData::writeToBinary(const std::string &fileName, const std::string &filePath, const CompressedImageHolder &compressedImageHolder)
{
    validateFileExtension(fileName);

    std::ofstream outFile;
    outFile.open(filePath + fileName, std::ios::binary);

    outFile.write(reinterpret_cast<const char *>(&compressedImageHolder.BLOCK_SIZE), sizeof(compressedImageHolder.BLOCK_SIZE));

    writeOriginalImageSize(outFile, compressedImageHolder.OriginalImageDimensions);
    
    writeQuantizationTable(outFile, compressedImageHolder.quantizationTable);

    writeCompressedImage(outFile, compressedImageHolder.compressedImage);

    outFile.close();
}

CompressedImageHolder StoreDCTData::readFromBinary(const std::string &fileName, const std::string &filePath)
{
    validateFileExtension(fileName);

    std::ifstream inFile;
    inFile.open(filePath + fileName, std::ios::binary);

    CompressedImageHolder compressedImageHolder;

    inFile.read(reinterpret_cast<char *>(&compressedImageHolder.BLOCK_SIZE), sizeof(compressedImageHolder.BLOCK_SIZE));

    compressedImageHolder.OriginalImageDimensions = readOriginalImageSize(inFile);

    compressedImageHolder.quantizationTable = readQuantizationTable(inFile);

    compressedImageHolder.compressedImage = readCompressedImage(inFile);

    inFile.close();

    return compressedImageHolder;
}

std::vector<std::vector<std::pair<float, int>>> StoreDCTData::readCompressedImage(std::ifstream &inFile)
{
    size_t numRows, numCols;
    inFile.read(reinterpret_cast<char *>(&numRows), sizeof(numRows));
    inFile.read(reinterpret_cast<char *>(&numCols), sizeof(numCols));

    std::vector<std::vector<std::pair<float, int>>> compressedImage(numRows, std::vector<std::pair<float, int>>(numCols));

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            inFile.read(reinterpret_cast<char *>(&compressedImage[i][j].first), sizeof(compressedImage[i][j].first));
            inFile.read(reinterpret_cast<char *>(&compressedImage[i][j].second), sizeof(compressedImage[i][j].second));
        }
    }

    return compressedImage;
}

std::vector<std::vector<int>> StoreDCTData::readQuantizationTable(std::ifstream &inFile)
{
    size_t numRows, numCols;
    inFile.read(reinterpret_cast<char *>(&numRows), sizeof(numRows));
    inFile.read(reinterpret_cast<char *>(&numCols), sizeof(numCols));

    std::vector<std::vector<int>> quantizationTable(numRows, std::vector<int>(numCols));

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            inFile.read(reinterpret_cast<char *>(&quantizationTable[i][j]), sizeof(quantizationTable[i][j]));
        }
    }

    return quantizationTable;
}

std::pair<int, int> StoreDCTData::readOriginalImageSize(std::ifstream &inFile) 
{
    int rows, cols;
    inFile.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    inFile.read(reinterpret_cast<char *>(&cols), sizeof(cols));

    return std::make_pair(rows, cols);
}

void StoreDCTData::writeCompressedImage(std::ofstream &outFile, const std::vector<std::vector<std::pair<float, int>>> &compressedImage)
{
    size_t numRows = compressedImage.size();
    size_t numCols = compressedImage[0].size();

    outFile.write(reinterpret_cast<const char *>(&numRows), sizeof(numRows));
    outFile.write(reinterpret_cast<const char *>(&numCols), sizeof(numCols));

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            float value = compressedImage[i][j].first;
            int runLength = compressedImage[i][j].second;

            outFile.write(reinterpret_cast<const char *>(&value), sizeof(value));
            outFile.write(reinterpret_cast<const char *>(&runLength), sizeof(runLength));
        }
    }
}

void StoreDCTData::writeQuantizationTable(std::ofstream &outFile, const std::vector<std::vector<int>> &quantizationTable)
{
    size_t numRows = quantizationTable.size();
    size_t numCols = quantizationTable[0].size();

    outFile.write(reinterpret_cast<const char *>(&numRows), sizeof(numRows));
    outFile.write(reinterpret_cast<const char *>(&numCols), sizeof(numCols));

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < numCols; ++j)
        {
            int value = quantizationTable[i][j];
            outFile.write(reinterpret_cast<const char *>(&value), sizeof(value));
        }
    }
}



void StoreDCTData::writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const
{
    outFile.write(reinterpret_cast<const char *>(&imageSize.first), sizeof(imageSize.first));
    outFile.write(reinterpret_cast<const char *>(&imageSize.second), sizeof(imageSize.second));
}

void StoreDCTData::validateFileExtension(const std::string &fileName) const
{
    if (fileName.size() < FILE_EXTENSION.size() ||
        fileName.substr(fileName.size() - FILE_EXTENSION.size()) != FILE_EXTENSION)
    {
        std::cerr << "Error: File must have the " << FILE_EXTENSION << " extension!\n";
        throw std::runtime_error("Invalid file extension");
    }
}