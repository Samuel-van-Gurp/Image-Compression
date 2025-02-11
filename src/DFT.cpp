#include "DFT.h"

cv::Mat DFT::computeDFT(const cv::Mat &img) const
{
    // TODO: add padding for optimal size for effcent DFT
    cv::Mat floatImage = convertTOFloatMat(img);

    cv::Mat complexImage = prepareComplex2channelMat(floatImage);

    // Compute DFT
    cv::dft(complexImage, complexImage);

    return complexImage;
}

cv::Mat DFT::prepareComplex2channelMat(const cv::Mat &floatImage) const
{
    cv::Mat planes[] = {floatImage, cv::Mat::zeros(floatImage.size(), CV_32F)};
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);

    return complexImage;
}

cv::Mat DFT::convertTOFloatMat(const cv::Mat &img) const
{
    cv::Mat floatImage;
    img.convertTo(floatImage, CV_32F);
    return floatImage;
}

cv::Mat DFT::computeInverseDFT(const cv::Mat &complexImage) const
{
    cv::Mat inverseTransform;
    cv::dft(complexImage, inverseTransform, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);

    inverseTransform.convertTo(inverseTransform, CV_8U); // Convert back to 8-bit

    return inverseTransform;
}

cv::Mat DFT::Magnitude(const cv::Mat &complexImage) const
{
    cv::Mat planes[] = {complexImage, cv::Mat::zeros(complexImage.size(), CV_32F)};
    cv::split(complexImage, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);

    return planes[0];
}
