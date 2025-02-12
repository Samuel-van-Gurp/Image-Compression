#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>

class Image
{
public:
    explicit Image(const cv::Mat &img);

    explicit Image(const std::string &filepath);

    void displayImage(const std::string &title = "Image") const;

    cv::Mat getImageMatrix() const;

    void setImage(cv::Mat img);

private:
    cv::Mat image;

    void readToGrayScale(const std::string &filenpath);
};

#endif // IMAGE_H