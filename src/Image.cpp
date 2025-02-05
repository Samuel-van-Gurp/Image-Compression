#include "Image.h"


Image::Image(const cv::Mat & img)
    : image(img)
{
}

Image::Image(const std::string & filepath)
{
    readToGrayScale(filepath);
}


void Image::readToGrayScale(const std::string & filenpath)
{
    image = cv::imread(filenpath, cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        throw std::runtime_error("Could not open or find the image");
    }
}


void Image::displayImage() const
{
    cv::imshow("Image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

cv::Mat Image::getImage() const
{
    return image;
}
