#include "Image.h"
#include "CompressedDFTImageHolder.h"
#include <opencv2/opencv.hpp>

class DFT
{
public:
    cv::Mat computeDFT(const cv::Mat &img) const;
    cv::Mat computeInverseDFT(const cv::Mat &complexImage) const;
    cv::Mat Magnitude(const cv::Mat &complexImage) const;

private:
    cv::Mat prepareComplex2channelMat(const cv::Mat &floatImage) const;
    cv::Mat convertTOFloatMat(const cv::Mat &img) const;
};
