#include "DFT.h"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>

TEST(DFTTest, DFTZeroInZeroOut)
{
    // Arrange
    cv::Mat zeroImage = cv::Mat::zeros(5, 5, CV_8UC1);

    DFT dft = DFT();

    // Act
    cv::Mat transformedImg = dft.computeDFT(zeroImage);

    // Split the matrix into 2 channels
    std::vector<cv::Mat> channels(2);
    cv::split(transformedImg, channels);

    // Assert
    EXPECT_TRUE(cv::countNonZero(channels[0]) == 0 &&
                cv::countNonZero(channels[1]) == 0);
}

TEST(DFTTest, MagnitudeTest)
{
    // Arrange
    int IMAGE_SIZE = 3;
    cv::Mat Real = cv::Mat::ones(IMAGE_SIZE, IMAGE_SIZE, CV_32F) * 5.0;
    cv::Mat Imaginary = cv::Mat::ones(IMAGE_SIZE, IMAGE_SIZE, CV_32F) * 3.0;

    // combine a 2 channel mat
    cv::Mat planes[] = {Real, Imaginary};
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);

    DFT dft = DFT();

    cv::Mat magnitudeImage = dft.Magnitude(complexImage);

    // Calculate the magnitude of element and multiply by number of pixels
    double expectedValue = sqrt(5 * 5 + 3 * 3) * (IMAGE_SIZE * IMAGE_SIZE);

    // Sum all elements in the magnitudeImage (it will be a cv::Scalar)
    double actualValue = cv::sum(magnitudeImage)[0];

    EXPECT_NEAR(actualValue, expectedValue, 1e-5);
}

TEST(DFTTest, InverseDFTZeroInZeroOut)
{
    // Arrange
    cv::Mat zeroReal = cv::Mat::zeros(5, 5, CV_32F);
    cv::Mat zeroImag = cv::Mat::zeros(5, 5, CV_32F);
    std::vector<cv::Mat> zeroChannels = {zeroReal, zeroImag};
    cv::Mat zeroComplex;
    cv::merge(zeroChannels, zeroComplex); // Create a 2-channel zero matrix

    DFT dft = DFT();

    // Act
    cv::Mat inverseTransformedImg = dft.computeInverseDFT(zeroComplex);

    // Assert
    EXPECT_TRUE(cv::countNonZero(inverseTransformedImg) == 0);
}

TEST(DFTTest, DFTRoundTrip)
{
    // Arrange
    cv::Mat RandomImage(5, 5, CV_8UC1);
    cv::randu(RandomImage, 0.0, 255.0);

    DFT dft = DFT();

    // Act
    cv::Mat transformedImg = dft.computeDFT(RandomImage);
    cv::Mat inverseTransformedImg = dft.computeInverseDFT(transformedImg);

    // Assert
    double error = cv::norm(RandomImage, inverseTransformedImg, cv::NORM_L2);
    EXPECT_NEAR(error, 0.0, 1e-5);
}
