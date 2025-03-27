#include "DCT.h"

DCT::DCT(const int signalLenght) 
{
    m_DCTMatrix = computeDCTMatrix(signalLenght);

    m_inverseDCTMatrix = transpose(m_DCTMatrix);
}

std::vector<float> DCT::computeDCT(const std::vector<float> &signal) const
{


    std::vector<float> out = multiplyMatrixVector(m_DCTMatrix, signal);

    return out;
}

std::vector<float> DCT::computeInverseDCT(const std::vector<float> &coeff) const
{

    std::vector<float> out = multiplyMatrixVector(m_inverseDCTMatrix, coeff);

    return out;
}

std::vector<std::vector<float>> DCT::transpose(const std::vector<std::vector<float>> &DCTMatrix) const
{
    size_t N = DCTMatrix.size();
    std::vector<std::vector<float>> transposed(N, std::vector<float>(N));

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            transposed[j][i] = DCTMatrix[i][j];
        }
    }

    return transposed;
}

std::vector<float> DCT::multiplyMatrixVector(
    const std::vector<std::vector<float>> &matrix,
    const std::vector<float> &signal) const
{
    size_t numRows = matrix.size();
    std::vector<float> result(numRows);

    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < signal.size(); ++j)
        {
            result[i] += matrix[i][j] * signal[j];
        }
    }
    return result;
}

std::vector<std::vector<float>> DCT::computeDCTMatrix(int signalLength) const
{
    std::vector<std::vector<float>> DCTMatrix(signalLength, std::vector<float>(signalLength, 0.0f));

    for (int rowIndex = 0; rowIndex < signalLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < signalLength; columnIndex++)
        {
            DCTMatrix[rowIndex][columnIndex] = static_cast<float>(computeDCTMatrixElement(rowIndex, columnIndex, signalLength));
        }
    }

    return DCTMatrix;
}

double DCT::computeDCTMatrixElement(const int row_index, const int column_index, const int signalLength) const
{
    signalLength;

    if (row_index == 0)
    {
        return sqrt(1.0 / signalLength);
    }
    else
    {
        return sqrt(2.0 / signalLength) * std::cos((PI * (2 * column_index + 1) * row_index) / (2 * signalLength));
    }
}