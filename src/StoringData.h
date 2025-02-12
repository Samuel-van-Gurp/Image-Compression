#include "Image.h"
#include "SparseRepresentation.h"
#include <iostream>
#include <fstream>
#include <vector>

class StoringData
{
public:
    StoringData();
    void SaveFile(const std::string &fileName, const std::string &filePath, const SparseRepresentation &sparceRep) const;
    SparseRepresentation LoadFile(const std::string &fileName, const std::string &filePath) const;

private:
    static const std::string FILE_EXTENTION;

    std::pair<int, int> readOriginalImageSize(std::ifstream &inFile) const;
    void writeSparceRep(std::ofstream &outFile, const SparseRepresentation &sparceRep) const;
    void writeSparseVectorLength(std::ofstream &outFile, const std::vector<ComplexRowColumnValue> &SparceVec) const;
    void hasSamuelExtensionErr(const std::string &fileName) const;
    bool openFileForWriting(const std::string &fileName, const std::string &filePath, std::ofstream &outFile) const;
    void writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const;
    void handleFileError() const;
    bool openFileForReading(const std::string &filePath, const std::string &fileName, std::ifstream &file) const;
    bool openFileCheckForErr(const std::string &filePath, const std::string &fileName, std::ifstream &file) const;
};
