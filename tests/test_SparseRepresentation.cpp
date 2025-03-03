#include "DFT/CompressedDFTImageHolder.h"
#include "Image.h"
#include "DFT/ComplexRowColumnValue.h"
#include <gtest/gtest.h>

TEST(SparseRepresentationTest, SparseReprRountTrip)
{
    // Create a 4x4 complex image (CV_32FC2) with all zeros.
    cv::Mat complexMatrix = cv::Mat::zeros(4, 4, CV_32FC2);

    std::vector<cv::Mat> channels(2);
    cv::split(complexMatrix, channels);
    channels[0].at<float>(1, 2) = 3.14f; // real
    channels[1].at<float>(1, 2) = 2.71f; // imaginary part
    cv::merge(channels, complexMatrix);

    CompressedDFTImageHolder sparseRep(complexMatrix);

    auto sparseElements = sparseRep.getSparseElements();

    ASSERT_EQ(sparseElements.size(), 1);

    // Check the stored values.
    EXPECT_EQ(sparseElements[0].m_row, 1);            // row
    EXPECT_EQ(sparseElements[0].m_col, 2);            // column
    EXPECT_FLOAT_EQ(sparseElements[0].m_real, 3.14f); // real
    EXPECT_FLOAT_EQ(sparseElements[0].m_imag, 2.71f); // imaginary

    cv::Mat reconstructedComplex = sparseRep.convertToDenseComplexMatrix();

    cv::split(reconstructedComplex, channels);

    cv::Mat reconstructedReal = channels[0];
    cv::Mat reconstructedImag = channels[1];

    // Check the non-zero
    float real = reconstructedReal.at<float>(2, 2);
    float imag = reconstructedImag.at<float>(1, 2);
    EXPECT_FLOAT_EQ(reconstructedReal.at<float>(1, 2), 3.14f);
    EXPECT_FLOAT_EQ(reconstructedImag.at<float>(1, 2), 2.71f);

    // Check that other elements are zero.
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {

            if (i == 1 && j == 2)
                continue;
            EXPECT_FLOAT_EQ(reconstructedReal.at<float>(i, j), 0.0f);
            EXPECT_FLOAT_EQ(reconstructedImag.at<float>(i, j), 0.0f);
        }
    }
}
