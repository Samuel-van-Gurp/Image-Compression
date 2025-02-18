#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>

class Image
{
public:
    explicit Image(const cv::Mat &img);

    explicit Image(const std::vector<std::vector<float>> &img);

    explicit Image(const std::string &filepath);

    void displayImage(const std::string &title = "Image") const;

    cv::Mat getImageMatrix() const;

    void setImage(cv::Mat img);

    std::vector<std::vector<float>> getImageAsVector() const;

    void DisplayDiffImage(Image otherImage) const;

    void ImageReport() const;

private:
    cv::Mat m_image;

    void convertTCV_8UC1();

    void readToGrayScale(const std::string &filenpath);
};

#endif // IMAGE_H