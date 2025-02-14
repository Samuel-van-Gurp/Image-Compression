#include "TwoDimDCT.h"

std::vector<std::vector<float>> TwoDimDCT::computeTwoDimDCT(const std::vector<std::vector<float>> &Image) const
{
    auto rowWiseTransImage = computeDCTRowWise(Image);
    auto DCTDomainImage = computeDCTColumnWise(rowWiseTransImage);

    return DCTDomainImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeTwoDimInverseDCT(const std::vector<std::vector<float>> &Image) const
{
    auto rowWiseTransImage = computeInverseDCTRowWise(Image);
    auto DCTDomainImage = computeInverseDCTColumnWise(rowWiseTransImage);

    return DCTDomainImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeDCTRowWise(const std::vector<std::vector<float>> &Image) const
{
    int rows = static_cast<int>(Image.size());
    int cols = static_cast<int>(Image[0].size());

    std::vector<std::vector<float>> rowWiseTransImage(rows, std::vector<float>(cols, 0.0f));

    DCT dct;

    for (int i = 0; i < rows; ++i)
    {
        // Compute 1D DCT for the current row
        auto dctRow = dct.computeDCT(Image[i]);

        rowWiseTransImage[i] = dctRow;
    }

    return rowWiseTransImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const
{
    int rows = static_cast<int>(rowWiseTransImage.size());
    int cols = static_cast<int>(rowWiseTransImage[0].size());

    std::vector<std::vector<float>> twoDimDCTResult(rows, std::vector<float>(cols, 0.0f));

    DCT dct;

    for (int j = 0; j < cols; ++j)
    {
        std::vector<float> column(rows);
        for (int i = 0; i < rows; ++i)
        {
            column[i] = rowWiseTransImage[i][j];
        }

        auto dctCol = dct.computeDCT(column);

        for (int i = 0; i < rows; ++i)
        {
            twoDimDCTResult[i][j] = dctCol[i];
        }
    }

    return twoDimDCTResult;
}

std::vector<std::vector<float>> TwoDimDCT::computeInverseDCTRowWise(const std::vector<std::vector<float>> &Image) const
{
    int rows = static_cast<int>(Image.size());
    int cols = static_cast<int>(Image[0].size());

    std::vector<std::vector<float>> rowWiseTransImage(rows, std::vector<float>(cols, 0.0f));

    DCT dct;

    for (int i = 0; i < rows; ++i)
    {
        // Compute 1D DCT for the current row
        auto dctRow = dct.computeInverseDCT(Image[i]);

        rowWiseTransImage[i] = dctRow;
    }

    return rowWiseTransImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeInverseDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const
{
    int rows = static_cast<int>(rowWiseTransImage.size());
    int cols = static_cast<int>(rowWiseTransImage[0].size());

    std::vector<std::vector<float>> twoDimDCTResult(rows, std::vector<float>(cols, 0.0f));

    DCT dct;

    for (int j = 0; j < cols; ++j)
    {
        std::vector<float> column(rows);
        for (int i = 0; i < rows; ++i)
        {
            column[i] = rowWiseTransImage[i][j];
        }

        auto dctCol = dct.computeInverseDCT(column);

        for (int i = 0; i < rows; ++i)
        {
            twoDimDCTResult[i][j] = dctCol[i];
        }
    }

    return twoDimDCTResult;
}