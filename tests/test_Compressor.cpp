#include "DFT/DFTCompressor.h"
#include "CompressionLevel.h"
#include "Image.h"
#include <gtest/gtest.h>

TEST(CompressorTest, CompressionRountTripNOCompression)
{
    // Arrange
    float COMPRESSION_PERCENTILE = 1.0;

    cv::Mat RandomMatrix(256, 256, CV_8UC1);
    cv::randu(RandomMatrix, 0.0, 255.0);

    Image randomImage = Image(RandomMatrix);
    DFTCompressor compressor;

    auto SparceRep = compressor.compress(randomImage,CompressionLevel::VERY_HIGH);
    Image decompressedImage = compressor.decompress(SparceRep);

    // Assert

    // cal avg per pixel err
    double totalError = cv::norm(RandomMatrix, decompressedImage.getImageMatrix(), cv::NORM_L2);
    double avgError = totalError / static_cast<double>(RandomMatrix.total());

    EXPECT_NEAR(avgError, 0.0, 1); // acount for floating point err
}
