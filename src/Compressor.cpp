#include "Compressor.h"

Compressor::Compressor()
{
}

cv::Mat Compressor::DFT(cv::Mat img)
{   
    // convert to float
    cv::Mat floatImage;
    img.convertTo(floatImage, CV_32F);


    // Create a complex image with two channels: real and imaginary
    cv::Mat planes[] = { floatImage, cv::Mat::zeros(img.size(), CV_32F) };
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);

    // Compute DFT
    cv::dft(complexImage, complexImage);

    return complexImage;
}

cv::Mat Compressor::IDFT(const cv::Mat& complexImage)
{
    cv::Mat inverseTransform;
    cv::dft(complexImage, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);

    inverseTransform.convertTo(inverseTransform, CV_8U);  // Convert back to 8-bit

    return inverseTransform;
}



