#include "Image.h"
#include <opencv2/opencv.hpp>
class Compressor
{

public:
    Compressor();
    cv::Mat DFT(cv::Mat img);
    cv::Mat IDFT(const cv::Mat & complexImage);
private:
};
    
