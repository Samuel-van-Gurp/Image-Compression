#include "DCT.h"

class TwoDimDCT
{
public:
    std::vector<std::vector<float>> computeTwoDimDCT(const std::vector<std::vector<float>> &Image) const;
    std::vector<std::vector<float>> computeTwoDimInverseDCT(const std::vector<std::vector<float>> &Image) const;

private:
    std::vector<std::vector<float>> computeDCTRowWise(const std::vector<std::vector<float>> &Image) const;
    std::vector<std::vector<float>> computeDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const;
    std::vector<std::vector<float>> computeInverseDCTRowWise(const std::vector<std::vector<float>> &Image) const;
    std::vector<std::vector<float>> computeInverseDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const;
};
