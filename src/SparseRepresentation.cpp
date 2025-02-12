#include "SparseRepresentation.h"

SparseRepresentation::SparseRepresentation(const cv::Mat &FourierDomianImage)
    : m_OriginalSizeImage(FourierDomianImage.size().height, FourierDomianImage.size().width), m_sparseElements()
{
    auto realImaginaryPair = splitComplexImage(FourierDomianImage);
    cv::Mat real = realImaginaryPair.first;
    cv::Mat imagery = realImaginaryPair.second;

    fillRowColumnComplexValue(real, imagery);
}

SparseRepresentation::SparseRepresentation(const std::vector<std::vector<float>> &sparseElements, const std::pair<int, int> &size)
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
                setRowColumnValueElement(real, imagery, rowIndex, columnIndex);
            }
        }
    }
}

void SparseRepresentation::setRowColumnValueElement(const cv::Mat &real, const cv::Mat &imagery, int rowIndex, int columnIndex)
{

    m_sparseElements.push_back({(float)rowIndex, (float)columnIndex, real.at<float>(rowIndex, columnIndex), imagery.at<float>(rowIndex, columnIndex)});
}

bool SparseRepresentation::isElementZero(const cv::Mat &real, const cv::Mat &imagery, int rowIndex, int columnIndex)
{

    return real.at<float>(rowIndex, columnIndex) == 0 || imagery.at<float>(rowIndex, columnIndex) == 0;
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

    for (int i = 0; i < m_sparseElements.size(); i++)
    {

        int rowIndex = static_cast<int>(m_sparseElements[i][0]);
        int columnIndex = static_cast<int>(m_sparseElements[i][1]);
        float realValue = m_sparseElements[i][2];
        float imageryValue = m_sparseElements[i][3];

        reconstructedRealImage.at<float>(rowIndex, columnIndex) = realValue;
        reconstructedImageryImage.at<float>(rowIndex, columnIndex) = imageryValue;
    }

    // Merge real and imaginary parts into a 2-channel matrix
    cv::Mat complexImage = mergeRealAndImaginary(reconstructedRealImage, reconstructedImageryImage);
    return complexImage;
}

std::vector<std::vector<float>> SparseRepresentation::getSparseElements() const
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