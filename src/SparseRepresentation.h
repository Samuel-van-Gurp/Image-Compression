#ifndef SPARSE_REPRESENTATIONS_H
#define SPARSE_REPRESENTATIONS_H

#include <opencv2/core/core.hpp>
#include <vector>

class SparseRepresentation
{
public:
    static constexpr int CHANNELS_COMPLEX_VALUE_ROW_COLUMN = 4;

    explicit SparseRepresentation(const cv::Mat &maskedDFT);
    SparseRepresentation(const std::vector<std::vector<float>> &sparseElements, const std::pair<int, int> &size);

    cv::Mat convertToDenseComplexMatrix() const;
    std::vector<std::vector<float>> getSparseElements() const;
    std::pair<int, int> getOriginalSizeImage() const;

private:
    const std::pair<int, int> m_OriginalSizeImage;
    std::vector<std::vector<float>> m_sparseElements;

    std::pair<cv::Mat, cv::Mat> splitComplexImage(const cv::Mat &complexImage) const;
    cv::Mat mergeRealAndImaginary(const cv::Mat &real, const cv::Mat &imaginary) const;
    void fillRowColumnComplexValue(const cv::Mat &real, const cv::Mat &imagery);
    void setRowColumnValueElement(const cv::Mat &real, const cv::Mat &imagery, int rowIndex, int columnIndex);
    bool isElementZero(const cv::Mat &real, const cv::Mat &imagery, int rowIndex, int columnIndex);
};

#endif // SPARSE_REPRESENTATIONS_H
