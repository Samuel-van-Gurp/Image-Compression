#include "StoreDFTData.h"
#include "CompressedDFTImageHolder.h"
#include "ComplexRowColumnValue.h"

StoreDFTData::StoreDFTData()
{
}

const std::string StoreDFTData::FILE_EXTENTION = ".samuel"; // move to base

void StoreDFTData::writeToBinary(const std::string &fileName, const std::string &filePath, const BaseCompressedImageHolder &sparceRep)
{

    hasSamuelExtensionErr(fileName);

    std::ofstream outFile;

    if (!openFileForWriting(fileName, filePath, outFile) || !outFile)
    {
        handleFileError();
        return;
    }

    // cast to derived type
    const auto &compressedImageHolder = dynamic_cast<const CompressedDFTImageHolder &>(sparceRep);

    writeOriginalImageSize(outFile, compressedImageHolder.getOriginalSizeImage());

    writeSparceRep(outFile, compressedImageHolder);

    outFile.close();
}

std::unique_ptr<BaseCompressedImageHolder> StoreDFTData::readFromBinary(const std::string &fileName, const std::string &filePath)
{
    std::ifstream inFile(filePath + fileName, std::ios::binary);

    hasSamuelExtensionErr(fileName);

    if (!inFile)
    {
        std::cerr << "Error opening file for reading\n";
        cv::Mat temp;
        return std::make_unique<CompressedDFTImageHolder>(CompressedDFTImageHolder(temp));
    }

    std::pair<int, int> sizeOriginalImage = readOriginalImageSize(inFile);

    size_t numElements;
    std::vector<ComplexRowColumnValue> SparceVec;

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

        SparceVec[i] = ComplexRowColumnValue(row, col, real, imag);
    }
    // Implicit conversion from unique_ptr<CompressedDFTImageHolder> to unique_ptr<BaseCompressedImageHolder>
    return std::make_unique<CompressedDFTImageHolder>(CompressedDFTImageHolder(SparceVec, sizeOriginalImage));
}

std::pair<int, int> StoreDFTData::readOriginalImageSize(std::ifstream &inFile) const
{
    int rows, cols;
    inFile.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    inFile.read(reinterpret_cast<char *>(&cols), sizeof(cols));

    return std::make_pair(rows, cols);
}

void StoreDFTData::writeSparceRep(std::ofstream &outFile, const CompressedDFTImageHolder &sparceRep) const
{

    std::vector<ComplexRowColumnValue> SparceVec = sparceRep.getSparseElements();

    writeSparseVectorLength(outFile, SparceVec);

    for (const ComplexRowColumnValue &element : SparceVec)
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

void StoreDFTData::writeSparseVectorLength(std::ofstream &outFile, const std::vector<ComplexRowColumnValue> &SparceVec) const
{
    size_t numRows = SparceVec.size();
    outFile.write(reinterpret_cast<char *>(&numRows), sizeof(numRows));
}

void StoreDFTData::writeOriginalImageSize(std::ofstream &outFile, const std::pair<int, int> &imageSize) const
{
    outFile.write(reinterpret_cast<const char *>(&imageSize.first), sizeof(imageSize.first));
    outFile.write(reinterpret_cast<const char *>(&imageSize.second), sizeof(imageSize.second));
}

bool StoreDFTData::openFileForWriting(const std::string &fileName, const std::string &filePath, std::ofstream &outFile) const
{
    outFile.open(filePath + fileName, std::ios::binary);
    return outFile.is_open(); // Return true if the file was successfully opened
}

void StoreDFTData::handleFileError() const
{
    std::cerr << "Error opening file\n";
}

void StoreDFTData::hasSamuelExtensionErr(const std::string &fileName) const
{
    if (fileName.size() < FILE_EXTENTION.size() ||
        fileName.substr(fileName.size() - FILE_EXTENTION.size()) != FILE_EXTENTION)
    {
        std::cerr << "Error: File must have the " << FILE_EXTENTION << " extension!\n";
        throw std::runtime_error("Invalid file extension");
    }
}
