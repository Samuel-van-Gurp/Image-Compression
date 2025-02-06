#ifndef SPARSE_REPRESENTATIONS_H
#define SPARSE_REPRESENTATIONS_H

#include <opencv2/core/core.hpp>
#include <vector>

class SparseRepresentations
{
public:
    SparseRepresentations(const cv::Mat& maskedDFT);
    cv::Mat convertToDenseComplexMatrix() const;
private:
    cv::Mat mergeRealAndImaginary(const cv::Mat & real, const cv::Mat & imaginary) const;
    const std::pair<int, int> m_size;
    std::vector<std::vector<float>> sparseElements;

    std::pair<cv::Mat,cv::Mat> splitComplexImage(const cv::Mat & complexImage) const;
    void fillRowColumnComplexValue(const cv::Mat & real, const cv::Mat & imagery);
    void setRowColumnValueElement(const cv::Mat & real, const cv::Mat & imagery, int rowIndex, int columnIndex);
    bool isElementZero(const cv::Mat & real, const cv::Mat & imagery, int rowIndex, int columnIndex);
};

#endif // SPARSE_REPRESENTATIONS_H
