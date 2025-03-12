#ifndef STORING_DATA_H
#define STORING_DATA_H

#include "Image.h"
#include "CompressedDFTImageHolder.h"
#include "BaseCompressedImageHolder.h"
#include "BaseStoreData.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

class StoreDFTData : public BaseStoreData
{
public:
    StoreDFTData();
    void writeToBinary(const std::string &fileName, const std::string &filePath, const BaseCompressedImageHolder &sparceRep) override;
    std::unique_ptr<BaseCompressedImageHolder> readFromBinary(const std::string &fileName, const std::string &filePath) override;

private:
    static const std::string FILE_EXTENTION;

    std::pair<int, int> readOriginalImageSize(std::ifstream &inFile) const;
    void writeSparceRep(std::ofstream &outFile, const CompressedDFTImageHolder &sparceRep) const;
    void writeSparseVectorLength(std::ofstream &outFile, const std::vector<ComplexRowColumnValue> &SparceVec) const;
    void hasSamuelExtensionErr(const std::string &fileName) const;
    bool openFileForWriting(const std::string &fileName, const std::string &filePath, std::ofstream &outFile) const;
    void writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const;
    void handleFileError() const;
    bool openFileForReading(const std::string &filePath, const std::string &fileName, std::ifstream &file) const;
    bool openFileCheckForErr(const std::string &filePath, const std::string &fileName, std::ifstream &file) const;
};
#endif // STORING_DATA_H