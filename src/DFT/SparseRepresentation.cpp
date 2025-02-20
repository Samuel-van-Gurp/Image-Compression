#include "SparseRepresentation.h"

SparseRepresentation::SparseRepresentation(const cv::Mat &FourierDomianImage)
    : m_OriginalSizeImage(FourierDomianImage.size().height, FourierDomianImage.size().width), m_sparseElements()
{
    auto realImaginaryPair = splitComplexImage(FourierDomianImage);
    cv::Mat real = realImaginaryPair.first;
    cv::Mat imagery = realImaginaryPair.second;

    fillRowColumnComplexValue(real, imagery);
}

SparseRepresentation::SparseRepresentation(const std::vector<ComplexRowColumnValue> &sparseElements, const std::pair<int, int> &size)
    : m_OriginalSizeImage(size), m_sparseElements(sparseElements)
{
}

void SparseRepresentation::fillRowColumnComplexValue(const cv::Mat &real, const cv::Mat &imagery)
{

    for (int rowIndex = 0; rowIndex < real.rows; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < real.cols; columnIndex++)
        {
            if (!isElementZero(real, imagery, rowIndex, columnIndex))
            {
                // setRowColumnValueElement(real, imagery, rowIndex, columnIndex);
                m_sparseElements.push_back(ComplexRowColumnValue(rowIndex, columnIndex, real.at<float>(rowIndex, columnIndex), imagery.at<float>(rowIndex, columnIndex)));
            }
        }
    }
}

bool SparseRepresentation::isElementZero(const cv::Mat &real, const cv::Mat &imagery, int rowIndex, int columnIndex)
{
    return real.at<float>(rowIndex, columnIndex) == 0 && imagery.at<float>(rowIndex, columnIndex) == 0;
}

std::pair<cv::Mat, cv::Mat> SparseRepresentation::splitComplexImage(const cv::Mat &complexImage) const
{
    cv::Mat planes[2];
    cv::split(complexImage, planes);

    return std::make_pair(planes[0], planes[1]);
    ;
}

cv::Mat SparseRepresentation::convertToDenseComplexMatrix() const
{
    cv::Mat reconstructedRealImage = cv::Mat::zeros(m_OriginalSizeImage.first, m_OriginalSizeImage.second, CV_32FC1);
    cv::Mat reconstructedImageryImage = cv::Mat::zeros(m_OriginalSizeImage.first, m_OriginalSizeImage.second, CV_32FC1);

    for (const auto &element : m_sparseElements)
    {
        int rowIndex = element.m_row;
        int columnIndex = element.m_col;
        float realValue = element.m_real;
        float imageryValue = element.m_imag;

        reconstructedRealImage.at<float>(rowIndex, columnIndex) = realValue;
        reconstructedImageryImage.at<float>(rowIndex, columnIndex) = imageryValue;
    }

    cv::Mat complexImage = mergeRealAndImaginary(reconstructedRealImage, reconstructedImageryImage);
    return complexImage;
}

std::vector<ComplexRowColumnValue> SparseRepresentation::getSparseElements() const
{
    return m_sparseElements;
}

std::pair<int, int> SparseRepresentation::getOriginalSizeImage() const
{
    return m_OriginalSizeImage;
}

cv::Mat SparseRepresentation::mergeRealAndImaginary(const cv::Mat &real, const cv::Mat &imaginary) const
{
    std::vector<cv::Mat> channels = {real, imaginary};
    cv::Mat complexImage;
    cv::merge(channels, complexImage);
    return complexImage;
}