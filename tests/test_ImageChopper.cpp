#include "DCT/ImageChopper.h"
#include <gtest/gtest.h>

TEST(ImageChopperTest, chopTest)
{
    const int WIDTH = 553;
    const int HEIGHT = 1111;
    const int chopSize = 8;

    std::vector<std::vector<float>> testImage(WIDTH, std::vector<float>(HEIGHT, 1));

    ImageChopper imageChopper;

    auto chopedImage = imageChopper.chopImage(testImage, chopSize);

    int expectedChops = (WIDTH / chopSize) * (HEIGHT / chopSize) + 208; // 208 to account for padding
    EXPECT_EQ(chopedImage.size(), expectedChops);
}

TEST(ImageChopperTest, ReconstructImage)
{

    //
    ImageChopper chopper;

    std::vector<std::vector<float>> originalImage = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    std::vector<std::vector<std::vector<float>>> choppedImage = {
        {{1, 2},
         {5, 6}},
        {{3, 4},
         {7, 8}},
        {{9, 10},
         {13, 14}},
        {{11, 12},
         {15, 16}}};

    std::vector<std::vector<float>> expectedImage = originalImage;

    std::vector<std::vector<float>> reconstructedImage = chopper.reconstructImage(choppedImage, 4, 4);

    EXPECT_EQ(reconstructedImage, expectedImage);
}
