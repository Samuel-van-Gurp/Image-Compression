#ifndef DCT_H
#define DCT_H

#include <vector>
#include <cmath>
#include <iostream>


class DCT
{
public:

    explicit DCT(const int signalLenght);

    std::vector<float> computeDCT(const std::vector<float> &signal) const;

    std::vector<float> computeInverseDCT(const std::vector<float> &coeff) const;

private:
    static constexpr double PI = 3.14159265358979323846;
    std::vector<std::vector<float>> m_DCTMatrix;
    std::vector<std::vector<float>> m_inverseDCTMatrix;

    std::vector<std::vector<float>> computeDCTMatrix(int signalLength) const;
    double computeDCTMatrixElement(const int row_index, const int column_index, const int signalLength) const;
    std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>> &DCTMatrix) const;
    std::vector<float> multiplyMatrixVector(const std::vector<std::vector<float>> &matrix, const std::vector<float> &signal) const;
};

#endif // DCT_H