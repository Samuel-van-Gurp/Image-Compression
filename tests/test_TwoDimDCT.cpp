#include "DCT/TwoDimDCT.h"

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

std::vector<std::vector<float>> matToVector(const cv::Mat &mat)
{
    int rows = mat.rows;
    int cols = mat.cols;

    std::vector<std::vector<float>> vec(rows, std::vector<float>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            vec[i][j] = static_cast<float>(mat.at<float>(i, j)); // Assuming grayscale (8-bit)
        }
    }

    return vec;
}

cv::Mat vectorToMat(const std::vector<std::vector<float>> &vec)
{
    int rows = static_cast<int>(vec.size());
    int cols = static_cast<int>(vec[0].size());

    cv::Mat mat(rows, cols, CV_32F); // Create a floating-point matrix (CV_32F)

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            mat.at<float>(i, j) = vec[i][j];
        }
    }

    return mat;
}

TEST(DCTTest, DCTRoundTrip)
{
    // Arrange
    cv::Mat RandomImage(5, 5, CV_32FC1);
    cv::randu(RandomImage, 0.0, 255.0);

    TwoDimDCT twoDimDCT = TwoDimDCT();

    // Act
    auto transformedImg = twoDimDCT.computeTwoDimDCT(matToVector(RandomImage));
    auto inverseTransformedImg = twoDimDCT.computeTwoDimInverseDCT(transformedImg);

    // Assert
    double error = cv::norm(RandomImage, vectorToMat(inverseTransformedImg), cv::NORM_L2);
    EXPECT_NEAR(error, 0.0, 1e-4);
}