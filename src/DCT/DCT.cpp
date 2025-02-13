#include "DCT.h"

std::vector<float> DCT::computeDCT(const std::vector<float> &signal) const
{

    auto DCTMatrix = computeDCTMatrix(signal);

    std::vector<float> out = multiplyMatrixVector(DCTMatrix, signal);
    return out;
}

std::vector<float> DCT::multiplyMatrixVector(
    const std::vector<std::vector<float>> &matrix,
    const std::vector<float> &signal) const
{
    size_t numRows = matrix.size();
    std::vector<float> result(numRows, 0.0f);

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < signal.size(); ++j)
        {
            result[i] += matrix[i][j] * signal[j];
        }
    }
    return result;
}

std::vector<std::vector<float>> DCT::computeDCTMatrix(const std::vector<float> &signal) const
{
    int matrixSize = static_cast<int>(signal.size());

    std::vector<std::vector<float>> DCTMatrix(matrixSize, std::vector<float>(matrixSize, 0.0f));

    for (int rowIndex = 0; rowIndex < matrixSize; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrixSize; columnIndex++)
        {
            DCTMatrix[rowIndex][columnIndex] = static_cast<float>(computeDCTMatrixElement(rowIndex, columnIndex, matrixSize));
            std::cout << computeDCTMatrixElement(rowIndex, columnIndex, matrixSize) << std::endl;
        }
    }

    return DCTMatrix;
}

double DCT::computeDCTMatrixElement(const int row_index, const int column_index, const int signalLength) const
{
    static_cast<int>(signalLength);

    if (row_index == 0)
    {
        return sqrt(1.0 / signalLength);
    }
    else
    {
        return sqrt(2.0 / signalLength) * std::cos((M_PI * (2 * column_index + 1) * row_index) / (2 * signalLength));
    }
}