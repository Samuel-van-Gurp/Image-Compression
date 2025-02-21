#ifndef ZIGZAG_DCT_COEFFICIENTS_ORDER_H
#define ZIGZAG_DCT_COEFFICIENTS_ORDER_H


#include "RunLengthEnoding.h"
#include <vector>
#include <cmath>

class ZigzagDCTcoefficientsOrder
{
public:
    std::vector<std::vector<int>> ZigZagOrderImageBlocks(std::vector<std::vector<std::vector<int>>> &imageChuncks) const;

    std::vector<std::vector<std::vector<int>>> deZigZagOrderImageBlocks(std::vector<std::vector<int>> &imageChuncks) const;

private:
    RunLengthEnoding m_runlengthEnoding;

    void fillZigzagDiagonal(std::vector<std::vector<int>> &imageBlock, const std::vector<int> &zigzagOrder, int sum, int dctBlockSize, int &index) const;
    std::vector<int> Zigzagtraversal(const std::vector<std::vector<int>> &imageBlock);
    std::vector<int> ZigzagOrder(const std::vector<std::vector<int>> &imageBlock) const;
    std::vector<int> extractZigzagDiagonal(const std::vector<std::vector<int>> &imageBlock, int sum) const;

    std::vector<std::vector<int>> ReverseZigzagtraversal(const std::vector<int> &zigzagOrder) const;
};

#endif // ZIGZAG_DCT_COEFFICIENTS_ORDER_H