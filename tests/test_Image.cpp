#include "Image.h"
#include <gtest/gtest.h>

TEST(ImageTest, HandelsInvalidFilesPath)
{
    // Arrange
    std::string invalidPath = "non_existent_image.png";

    // Act & Assert
    EXPECT_THROW(Image("invalidPath"), std::runtime_error);
}

TEST(ImageTests, ConstructorWithMat)
{
    // Arrange
    cv::Mat mat(10, 10, CV_8UC1, cv::Scalar(255));

    // Act
    Image img(mat);

    // Assert
    EXPECT_EQ(img.getImageMatrix().size(), mat.size());
    EXPECT_EQ(img.getImageMatrix().type(), mat.type());
}