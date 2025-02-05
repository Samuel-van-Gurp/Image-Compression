#include "Image.h"
#include <opencv2/opencv.hpp>
class Compressor
{

public:
    Compressor();
    Image compress(const Image & image, float percentile) const;
private:
    cv::Mat DFT(const cv::Mat& img) const;
    cv::Mat IDFT(const cv::Mat & complexImage) const;
    cv::Mat Magnitude(const cv::Mat & complexImage) const;
 
    float const IntensityThresholdValue(const cv::Mat & img, float percentile) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat & img, float threshold) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat & img, int threshold) const;
    cv::Mat applyMask(const cv::Mat & complexImage, const cv::Mat & mask) const;
};
    
