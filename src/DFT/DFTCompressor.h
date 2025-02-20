#include "Image.h"
#include "DFT/DFT.h"
#include "SparseRepresentation.h"
#include <opencv2/opencv.hpp>

class DFTCompressor
{

public:
    DFTCompressor();

    SparseRepresentation compress(const Image &image, float percentile) const;
    Image decompress(const SparseRepresentation &sparseRepr) const;

private:
    float const ComputeIntensityThreshold(const cv::Mat &img, float percentile) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat &img, float threshold) const;
    cv::Mat applyMask(const cv::Mat &complexImage, const cv::Mat &mask) const;
};
