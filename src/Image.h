#ifndef IMAGE_H
#define IMAGE_H


#include <opencv2/opencv.hpp>

class Image
{
public:
    Image(const cv::Mat& img);

    Image(const std::string& filepath);


    void displayImage() const;

    cv::Mat getImage() const;

    void setImage(cv::Mat img);

private:
    cv::Mat image;

    void readToGrayScale(const std::string& filenpath);

};


#endif  // IMAGE_H