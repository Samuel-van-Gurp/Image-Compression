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

    int expectedChops = (WIDTH / chopSize) * (HEIGHT / chopSize) + 208; // 178 to account for padding
    EXPECT_EQ(chopedImage.size(), expectedChops);
}
