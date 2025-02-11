#include "Image.h"
#include "DFT.h"
#include "SparseRepresentation.h"
#include <opencv2/opencv.hpp>

class Compressor
{

public:
    Compressor();

    SparseRepresentation compress(const Image &image, float percentile) const;
    Image decompress(const SparseRepresentation &sparseRepr) const;

private:
    // cv::Mat computeDFT(const cv::Mat &img) const;
    // cv::Mat prepareComplex2channelMat(const cv::Mat &img) const;
    // cv::Mat convertTOFloatMat(const cv::Mat &img) const;
    // cv::Mat computeInverseDFT(const cv::Mat &complexImage) const;
    // cv::Mat Magnitude(const cv::Mat &complexImage) const;

    float const IntensityThresholdValue(const cv::Mat &img, float percentile) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat &img, float threshold) const;
    cv::Mat applyMask(const cv::Mat &complexImage, const cv::Mat &mask) const;
};
