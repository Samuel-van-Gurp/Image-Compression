#ifndef ZIGZAG_DCT_COEFFICIENTS_ORDER_H
#define ZIGZAG_DCT_COEFFICIENTS_ORDER_H

#include "RunLengthEnoding.h"
#include <vector>
#include <cmath>

class ZigzagDCTcoefficientsOrder
{
public:
    std::vector<std::vector<float>> ZigZagOrderImageBlocks(std::vector<std::vector<std::vector<float>>> &imageChuncks) const;

    std::vector<std::vector<std::vector<float>>> deZigZagOrderImageBlocks(std::vector<std::vector<float>> &imageChuncks) const;

private:
    RunLengthEnoding m_runlengthEnoding;

    void fillZigzagDiagonal(std::vector<std::vector<float>> &imageBlock, const std::vector<float> &zigzagOrder, int sum, int dctBlockSize, int &index) const;
    std::vector<float> Zigzagtraversal(const std::vector<std::vector<float>> &imageBlock);
    std::vector<float> ZigzagOrder(const std::vector<std::vector<float>> &imageBlock) const;
    std::vector<float> extractZigzagDiagonal(const std::vector<std::vector<float>> &imageBlock, int sum) const;

    std::vector<std::vector<float>> ReverseZigzagtraversal(const std::vector<float> &zigzagOrder) const;
};

#endif // ZIGZAG_DCT_COEFFICIENTS_ORDER_H