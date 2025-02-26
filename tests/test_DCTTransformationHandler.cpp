#include "gtest/gtest.h"
#include "DCT/DCTTransformationHandler.h"
#include <opencv2/opencv.hpp>
#include <random>

cv::Mat createRandomImage(int width, int height)
{
    cv::Mat image(height, width, CV_8UC1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image.at<uint8_t>(i, j) = dis(gen);
        }
    }
    return image;
}

std::vector<std::vector<float>> convertToVector(const cv::Mat &image)
{
    std::vector<std::vector<float>> vec(image.rows, std::vector<float>(image.cols));
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            vec[i][j] = static_cast<float>(image.at<uint8_t>(i, j));
        }
    }
    return vec;
}

cv::Mat convertToMat(const std::vector<std::vector<float>> &data, int rows, int cols)
{
    cv::Mat image(rows, cols, CV_32F);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            image.at<float>(i, j) = data[i][j];
        }
    }
    return image;
}

TEST(DCTCompressionTest, CompressDecompress)
{
    // Create a random image
    cv::Mat inputImage = createRandomImage(256, 256);
    ASSERT_FALSE(inputImage.empty());

    // Convert cv::Mat to std::vector<std::vector<float>>
    std::vector<std::vector<float>> inputVector = convertToVector(inputImage);

    // Create an instance of DCTCompression
    DCTTransformationHandler compressor;

    // Compress the image
    std::vector<std::vector<std::vector<float>>> compressedData = compressor.DCTTransformImage(inputVector, QuantizationTable::mediumCompressionTable);
    ASSERT_FALSE(compressedData.empty());

    // Decompress the image
    std::vector<std::vector<float>> decompressedData = compressor.inverseDCTTransformImage(compressedData, QuantizationTable::mediumCompressionTable, inputImage.rows, inputImage.cols);

    cv::Mat outputImage = convertToMat(decompressedData, inputImage.rows, inputImage.cols);
    ASSERT_FALSE(outputImage.empty());

    // Check if the decompressed image has the same size as the original
    cv::Size inputSize = inputImage.size();
    cv::Size outputSize = outputImage.size();

    EXPECT_EQ(inputSize, outputSize);
}

// TEST(DCTCompressionTest, InvalidCompressionLevel)
// {
//     // Create a random image
//     cv::Mat inputImage = createRandomImage(256, 256);
//     ASSERT_FALSE(inputImage.empty());

//     // Create an instance of DCTCompression
//     DCTCompression compressor;

//     // Try compressing with an invalid compression level
//     EXPECT_THROW(compressor.DCTCompress(inputImage, static_cast<CompressionLevel>(-1)), std::invalid_argument);
// }
