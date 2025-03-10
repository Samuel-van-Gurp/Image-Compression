#include "StoreDCTData.h"

const std::string StoreDCTData::FILE_EXTENSION = ".samuel";

void StoreDCTData::writeToBinary(const std::string &fileName, const std::string &filePath, const BaseCompressedImageHolder  &compressedData)
{
    validateFileExtension(fileName);

    std::ofstream outFile;
    outFile.open(filePath + fileName, std::ios::binary);

    // cast to derived type
    const auto &compressedImageHolder = dynamic_cast<const CompressedDCTImageHolder&>(compressedData);

    outFile.write(reinterpret_cast<const char *>(&compressedImageHolder.BLOCK_SIZE), sizeof(compressedImageHolder.BLOCK_SIZE));

    writeOriginalImageSize(outFile, compressedImageHolder.OriginalImageDimensions);

    writeQuantizationTable(outFile, compressedImageHolder.quantizationTable);

    writeCompressedImage(outFile, compressedImageHolder.compressedImage);

    outFile.close();
}

std::unique_ptr<BaseCompressedImageHolder > StoreDCTData::readFromBinary(const std::string &fileName, const std::string &filePath)
{
    validateFileExtension(fileName);

    std::ifstream inFile;
    inFile.open(filePath + fileName, std::ios::binary);

    auto compressedImageHolder = std::make_unique<CompressedDCTImageHolder>();

    inFile.read(reinterpret_cast<char *>(&compressedImageHolder->BLOCK_SIZE), sizeof(compressedImageHolder->BLOCK_SIZE));

    compressedImageHolder->OriginalImageDimensions = readOriginalImageSize(inFile);

    compressedImageHolder->quantizationTable = readQuantizationTable(inFile);

    compressedImageHolder->compressedImage = readCompressedImage(inFile);

    inFile.close();
    // Implicit conversion from unique_ptr<CompressedDCTImageHolder> to unique_ptr<BaseCompressedImageHolder>
    return compressedImageHolder;
}

std::vector<std::vector<std::pair<float, int>>> StoreDCTData::readCompressedImage(std::ifstream &inFile)
{
    // Read number of blocks
    int numBlocks;
    inFile.read(reinterpret_cast<char *>(&numBlocks), sizeof(numBlocks));

    std::vector<std::vector<std::pair<float, int>>> compressedImage(numBlocks);

    // For each block
    for (int i = 0; i < numBlocks; ++i)
    {
        // Read number of pairs in this block
        int numPairs;
        inFile.read(reinterpret_cast<char *>(&numPairs), sizeof(numPairs));

        // Read each value-runlength pair
        compressedImage[i].resize(numPairs);
        for (int j = 0; j < numPairs; ++j)
        {
            inFile.read(reinterpret_cast<char *>(&compressedImage[i][j].first), sizeof(float));
            inFile.read(reinterpret_cast<char *>(&compressedImage[i][j].second), sizeof(int));
        }
    }

    return compressedImage;
}

std::vector<std::vector<int>> StoreDCTData::readQuantizationTable(std::ifstream &inFile)
{
    int numRows, numCols;
    inFile.read(reinterpret_cast<char *>(&numRows), sizeof(numRows));
    inFile.read(reinterpret_cast<char *>(&numCols), sizeof(numCols));

    std::vector<std::vector<int>> quantizationTable(numRows, std::vector<int>(numCols));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
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
    if (compressedImage.empty())
    {
        throw std::runtime_error("Compressed image data is empty");
    }

    // Write number of blocks
    int numBlocks = static_cast<int>(compressedImage.size());
    outFile.write(reinterpret_cast<const char *>(&numBlocks), sizeof(numBlocks));

    // For each block
    for (const auto &block : compressedImage)
    {
        // Write number of pairs in this block
        int numPairs = static_cast<int>(block.size());
        outFile.write(reinterpret_cast<const char *>(&numPairs), sizeof(numPairs));

        // Write each value-runlength pair
        for (const auto &[value, runLength] : block)
        {
            outFile.write(reinterpret_cast<const char *>(&value), sizeof(value));
            outFile.write(reinterpret_cast<const char *>(&runLength), sizeof(runLength));
        }
    }
}

void StoreDCTData::writeQuantizationTable(std::ofstream &outFile, const std::vector<std::vector<int>> &quantizationTable)
{
    int numRows = static_cast<int>(quantizationTable.size());
    int numCols = static_cast<int>(quantizationTable[0].size());

    outFile.write(reinterpret_cast<const char *>(&numRows), sizeof(numRows));
    outFile.write(reinterpret_cast<const char *>(&numCols), sizeof(numCols));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
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