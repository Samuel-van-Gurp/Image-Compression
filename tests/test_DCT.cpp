#include "DCT/DCT.h"
#include <gtest/gtest.h>

TEST(ImageDCT, 1D_sample)
{
    // Arrange
    std::vector<float> signal = {6, 10, 17};
    std::vector<float> expectedCoefficients = {19.0526f, -7.7782f, 1.2247f};

    DCT dct;

    // Act

    auto outputCoefficients = dct.computeDCT(signal);

    // Assert
    float floarErr = 1e-4f;

    // Assert using EXPECT_NEAR instead of EXPECT_FLOAT_EQ
    EXPECT_NEAR(expectedCoefficients[0], outputCoefficients[0], floarErr);
    EXPECT_NEAR(expectedCoefficients[1], outputCoefficients[1], floarErr);
    EXPECT_NEAR(expectedCoefficients[2], outputCoefficients[2], floarErr);
}

TEST(ImageDCT, 1D_sample_inverse)
{
    // Arrange
    std::vector<float> expectedSignal = {6, 10, 17};
    std::vector<float> Coefficients = {19.0526f, -7.7782f, 1.2247f};

    DCT dct;

    // Act

    auto output = dct.computeInverseDCT(Coefficients);

    auto outputSignal = output;

    // Assert
    float floarErr = 1e-4f;

    // Assert using EXPECT_NEAR instead of EXPECT_FLOAT_EQ
    EXPECT_NEAR(expectedSignal[0], outputSignal[0], floarErr);
    EXPECT_NEAR(expectedSignal[1], outputSignal[1], floarErr);
    EXPECT_NEAR(expectedSignal[2], outputSignal[2], floarErr);
}