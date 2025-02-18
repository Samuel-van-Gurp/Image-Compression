#include "Image.h"

Image::Image(const cv::Mat &img)
    : m_image(img)
{
    if (m_image.type() == CV_32FC1)
    {
        convertTCV_8UC1();
    }
}

Image::Image(const std::string &filepath)
{
    readToGrayScale(filepath);
    if (m_image.type() == CV_32FC1)
    {
        convertTCV_8UC1();
    }
}

Image::Image(const std::vector<std::vector<float>> &img)
{
    m_image = cv::Mat(static_cast<int>(img.size()), static_cast<int>(img[0].size()), CV_32F);

    for (int i = 0; i < img.size(); ++i)
    {
        for (int j = 0; j < img[0].size(); ++j)
        {
            m_image.at<float>(i, j) = static_cast<float>(img[i][j]);
        }
    }
    if (m_image.type() == CV_32FC1)
    {
        convertTCV_8UC1();
    }
}

void Image::convertTCV_8UC1()
{
    m_image.convertTo(m_image, CV_8UC1);
}
void Image::readToGrayScale(const std::string &filenpath)
{
    m_image = cv::imread(filenpath, cv::IMREAD_GRAYSCALE);
    if (m_image.empty())
    {
        throw std::runtime_error("Could not open or find the image");
    }
}

void Image::displayImage(const std::string &title) const
{
    cv::imshow(title, m_image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

cv::Mat Image::getImageMatrix() const
{
    return m_image;
}

std::vector<std::vector<float>> Image::getImageAsVector() const
{
    std::vector<std::vector<float>> imageMatrix(m_image.rows, std::vector<float>(m_image.cols, 0));

    for (int i = 0; i < m_image.rows; ++i)
    {
        for (int j = 0; j < m_image.cols; ++j)
        {
            imageMatrix[i][j] = static_cast<float>(m_image.at<uchar>(i, j));
        }
    }

    return imageMatrix;
}

void Image::DisplayDiffImage(Image otherImage) const
{
    // calculate the difference between the two images
    cv::Mat diffImage;
    cv::absdiff(m_image, otherImage.getImageMatrix(), diffImage);
    // display the difference image
    cv::imshow("Difference Image", diffImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void Image::ImageReport() const
{
    std::cout << "________________________________________________ " << std::endl;

    std::cout << "Image size: " << m_image.rows << "x" << m_image.cols << std::endl;
    std::cout << "Image channels: " << m_image.channels() << std::endl;
    std::cout << "Image depth: " << m_image.depth() << std::endl;
    std::cout << "Image type: " << m_image.type() << std::endl;

    // facts about the intensety distribution of the image to terminal
    double minVal, maxVal;
    cv::Scalar mean, stddev;
    cv::minMaxLoc(m_image, &minVal, &maxVal);
    cv::meanStdDev(m_image, mean, stddev);

    std::cout << "Image intensity distribution: " << std::endl;
    std::cout << "Min intensity: " << minVal << std::endl;
    std::cout << "Mean intensity: " << mean[0] << std::endl;
    std::cout << "Standard deviation: " << stddev[0] << std::endl;
    std::cout << "Standard deviation: " << stddev << std::endl;

    std::cout << "________________________________________________ " << std::endl;
}
