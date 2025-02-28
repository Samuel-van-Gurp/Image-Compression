#include "StoringData.h"
#include "SparseRepresentation.h"
#include "CompressedDFTImageHolder.h"

StoringData::StoringData()
{
}

const std::string StoringData::FILE_EXTENTION = ".samuel";

void StoringData::SaveFile(const std::string &fileName, const std::string &filePath, const SparseRepresentation &sparceRep) const
{
    // std::ofstream outFile(filePath + fileName, std::ios::binary);

    hasSamuelExtensionErr(fileName);

    std::ofstream outFile;

    if (!openFileForWriting(fileName, filePath, outFile) || !outFile)
    {
        handleFileError();
        return;
    }

    writeOriginalImageSize(outFile, sparceRep.getOriginalSizeImage());

    writeSparceRep(outFile, sparceRep);

    outFile.close();
}

SparseRepresentation StoringData::LoadFile(const std::string &fileName, const std::string &filePath) const
{
    std::ifstream inFile(filePath + fileName, std::ios::binary);

    hasSamuelExtensionErr(fileName);

    if (!inFile)
    {
        std::cerr << "Error opening file for reading\n";
        cv::Mat temp;
        return SparseRepresentation(temp);
    }

    std::pair<int, int> sizeOriginalImage = readOriginalImageSize(inFile);

    size_t numElements;
    std::vector<CompressedDFTImageHolder> SparceVec;

    // Read number of rows
    inFile.read(reinterpret_cast<char *>(&numElements), sizeof(numElements));

    SparceVec.resize(numElements);

    // Read each row
    for (size_t i = 0; i < numElements; ++i)
    {
        int row, col;
        float real, imag;

        inFile.read(reinterpret_cast<char *>(&row), sizeof(row));
        inFile.read(reinterpret_cast<char *>(&col), sizeof(col));
        inFile.read(reinterpret_cast<char *>(&real), sizeof(real));
        inFile.read(reinterpret_cast<char *>(&imag), sizeof(imag));

        // Create and store the ComplexRowColumnValue object
        SparceVec[i] = CompressedDFTImageHolder(row, col, real, imag);
    }

    return SparseRepresentation(SparceVec, sizeOriginalImage);
}

std::pair<int, int> StoringData::readOriginalImageSize(std::ifstream &inFile) const
{
    int rows, cols;
    inFile.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    inFile.read(reinterpret_cast<char *>(&cols), sizeof(cols));

    return std::make_pair(rows, cols);
}

void StoringData::writeSparceRep(std::ofstream &outFile, const SparseRepresentation &sparceRep) const
{

    std::vector<CompressedDFTImageHolder> SparceVec = sparceRep.getSparseElements();

    writeSparseVectorLength(outFile, SparceVec);

    for (const CompressedDFTImageHolder &element : SparceVec)
    {
        int rowIdx = element.m_row;
        int colIdx = element.m_col;
        float real = element.m_real;
        float imag = element.m_imag;

        outFile.write(reinterpret_cast<const char *>(&rowIdx), sizeof(rowIdx)); // Row index
        outFile.write(reinterpret_cast<const char *>(&colIdx), sizeof(colIdx)); // Column index
        outFile.write(reinterpret_cast<const char *>(&real), sizeof(real));     // Real part
        outFile.write(reinterpret_cast<const char *>(&imag), sizeof(imag));     // Image part
    }
}

void StoringData::writeSparseVectorLength(std::ofstream &outFile, const std::vector<CompressedDFTImageHolder> &SparceVec) const
{
    size_t numRows = SparceVec.size();
    outFile.write(reinterpret_cast<char *>(&numRows), sizeof(numRows));
}

void StoringData::writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const
{
    outFile.write(reinterpret_cast<const char *>(&imageSize.first), sizeof(imageSize.first));
    outFile.write(reinterpret_cast<const char *>(&imageSize.second), sizeof(imageSize.second));
}

bool StoringData::openFileForWriting(const std::string &fileName, const std::string &filePath, std::ofstream &outFile) const
{
    outFile.open(filePath + fileName, std::ios::binary);
    return outFile.is_open(); // Return true if the file was successfully opened
}

void StoringData::handleFileError() const
{
    std::cerr << "Error opening file\n";
}

void StoringData::hasSamuelExtensionErr(const std::string &fileName) const
{
    if (fileName.size() < FILE_EXTENTION.size() ||
        fileName.substr(fileName.size() - FILE_EXTENTION.size()) != FILE_EXTENTION)
    {
        std::cerr << "Error: File must have the " << FILE_EXTENTION << " extension!\n";
        throw std::runtime_error("Invalid file extension");
    }
}
