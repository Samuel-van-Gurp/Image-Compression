#include "SparseRepresentation.h"

SparseRepresentations::SparseRepresentations(const cv::Mat& maskedDFT)
    : m_size(maskedDFT.size().width, maskedDFT.size().height)
    , sparseElements()
{
    auto realImaginaryPair = splitComplexImage(maskedDFT);
    cv::Mat real = realImaginaryPair.first;
    cv::Mat imagery = realImaginaryPair.second;

    fillRowColumnComplexValue(real, imagery);
}

void SparseRepresentations::fillRowColumnComplexValue(const cv::Mat& real, const cv::Mat& imagery){
    
    for (int rowIndex = 0; rowIndex < real.rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < real.cols; columnIndex++)
        {
            if (!isElementZero(real, imagery, rowIndex, columnIndex))
            {
                setRowColumnValueElement(real, imagery, rowIndex, columnIndex);
            }
        }
    }
}

void SparseRepresentations::setRowColumnValueElement(const cv::Mat& real, const cv::Mat& imagery, int rowIndex, int columnIndex){
    
    sparseElements.push_back({(float)rowIndex, (float)columnIndex, real.at<float>(rowIndex, columnIndex), imagery.at<float>(rowIndex, columnIndex)});
}

bool SparseRepresentations::isElementZero(const cv::Mat& real, const cv::Mat& imagery, int rowIndex, int columnIndex){
    
    return real.at<float>(rowIndex, columnIndex) == 0 || imagery.at<float>(rowIndex, columnIndex) == 0;
}

std::pair<cv::Mat, cv::Mat> SparseRepresentations::splitComplexImage(const cv::Mat& complexImage) const
{
    cv::Mat planes[2];
    cv::split(complexImage, planes); 

    return std::make_pair(planes[0], planes[1]);;
}

cv::Mat SparseRepresentations::convertToDenseComplexMatrix() const
{ 
    cv::Mat reconstructedRealImage = cv::Mat::zeros(m_size.first, m_size.second, CV_32FC1);
    cv::Mat reconstructedImageryImage = cv::Mat::zeros(m_size.first, m_size.second, CV_32FC1);

    for (int i = 0; i < sparseElements.size(); i++){

        int rowIndex = static_cast<int>(sparseElements[i][0]);
        int columnIndex = static_cast<int>(sparseElements[i][1]);
        float realValue = sparseElements[i][2];
        float imageryValue = sparseElements[i][3];

        reconstructedRealImage.at<float>(rowIndex, columnIndex) = realValue;
        reconstructedImageryImage.at<float>(rowIndex, columnIndex) = imageryValue;
    }

    // Merge real and imaginary parts into a 2-channel matrix
    cv::Mat complexImage = mergeRealAndImaginary(reconstructedRealImage, reconstructedImageryImage);
    return complexImage;
}

cv::Mat SparseRepresentations::mergeRealAndImaginary(const cv::Mat& real, const cv::Mat& imaginary) const
    {
        std::vector<cv::Mat> channels = {real, imaginary};
        cv::Mat complexImage;
        cv::merge(channels, complexImage);
        return complexImage;
    }