#include "Image.h"
#include "SparseRepresentation.h"
#include <opencv2/opencv.hpp>
class Compressor
{

public:
    Compressor();
    
    SparseRepresentations compress(const Image & image, float percentile) const;
    Image decompress(const SparseRepresentations & sparseRepr) const;

private:
    cv::Mat computeDFT(const cv::Mat& img) const;
    cv::Mat prepareComplex2channelMat(const cv::Mat & img) const;
    cv::Mat convertTOFloatMat(const Image & img) const;
    cv::Mat computeInverseDFT(const cv::Mat & complexImage) const;
    cv::Mat Magnitude(const cv::Mat & complexImage) const;
 
    float const IntensityThresholdValue(const cv::Mat & img, float percentile) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat & img, float threshold) const;
    cv::Mat applyMask(const cv::Mat & complexImage, const cv::Mat & mask) const;
};
    
