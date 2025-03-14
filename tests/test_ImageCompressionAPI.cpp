#include "gtest/gtest.h"
#include "API/ImageCompressionAPI.h"
#include <opencv2/opencv.hpp>
#include <random>

cv::Mat makeRandomImage(int width, int height)
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

TEST(ImageCompressionAPITest, CompressDecompress)
{
    int IMAGE_BLOCK_SIZE = 8;

    // Create a random image
    // cv::Mat inputImage = makeRandomImage(1036, 1554);
    cv::Mat inputImage = makeRandomImage(103, 155);

    ASSERT_FALSE(inputImage.empty());

    Image img = Image(inputImage);

    ImageCompressionAPI api = ImageCompressionAPI::create(Method::DCT);

    auto compressedImage = api.compress(img, CompressionLevel::ULTRA_HIGH);

    // decompress the image
    auto decompressedImage = api.decompress(*compressedImage);

    EXPECT_EQ(img.getImageAsVector().size(), decompressedImage.getImageAsVector().size());
}