#ifndef DCT_H
#define DCT_H

#include <vector>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DCT
{
public:
    std::vector<float> computeDCT(const std::vector<float> &signal) const;

    std::vector<float> computeInverseDCT(const std::vector<float> &coeff) const;

private:
    void inplaceTranspose(std::vector<std::vector<float>> &DCTMatrix) const;
    std::vector<std::vector<float>> computeDCTMatrix(const std::vector<float> &signal) const;
    double computeDCTMatrixElement(const int row_index, const int column_index, const int signalLength) const;
    std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>> &DCTMatrix) const;
    std::vector<float> multiplyMatrixVector(const std::vector<std::vector<float>> &matrix, const std::vector<float> &signal) const;
};

#endif // DCT_H