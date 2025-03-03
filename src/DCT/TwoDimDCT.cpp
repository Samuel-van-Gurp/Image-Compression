#include "TwoDimDCT.h"

// constructor
TwoDimDCT::TwoDimDCT(const int ImageBlocksize) : m_DCT(ImageBlocksize)
{
    
}



std::vector<std::vector<float>> TwoDimDCT::computeTwoDimDCT(const std::vector<std::vector<float>> &Image) const
{
    if (Image.size() != Image[0].size())
    {
        throw std::invalid_argument("Image block is not square");
    }

    auto rowWiseTransImage = computeDCTRowWise(Image);
    auto DCTDomainImage = computeDCTColumnWise(rowWiseTransImage);

    if (DCTDomainImage.size() != DCTDomainImage[0].size())
    {
        throw std::invalid_argument("DCT Image block is not square");
    }

    return DCTDomainImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeTwoDimInverseDCT(const std::vector<std::vector<float>> &Image) const
{

    if (Image.size() != Image[0].size())
    {
        throw std::invalid_argument("Image block is not square");
    }

    auto rowWiseTransImage = computeInverseDCTRowWise(Image);
    auto DCTDomainImage = computeInverseDCTColumnWise(rowWiseTransImage);

    return DCTDomainImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeDCTRowWise(const std::vector<std::vector<float>> &Image) const
{
    
    int rows = static_cast<int>(Image.size());
    int cols = static_cast<int>(Image[0].size());

    std::vector<std::vector<float>> rowWiseTransImage(rows, std::vector<float>(cols, 0.0f));


    for (int i = 0; i < rows; ++i)
    {
        // Compute 1D DCT for the current row
        auto dctRow = m_DCT.computeDCT(Image[i]);

        rowWiseTransImage[i] = dctRow;
    }

    return rowWiseTransImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const
{
    int rows = static_cast<int>(rowWiseTransImage.size());
    int cols = static_cast<int>(rowWiseTransImage[0].size());

    std::vector<std::vector<float>> twoDimDCTResult(rows, std::vector<float>(cols, 0.0f));


    for (int j = 0; j < cols; ++j)
    {
        std::vector<float> column(rows);
        for (int i = 0; i < rows; ++i)
        {
            column[i] = rowWiseTransImage[i][j];
        }

        auto dctCol = m_DCT.computeDCT(column);

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

    for (int i = 0; i < rows; ++i)
    {
        // Compute 1D DCT for the current row
        auto dctRow = m_DCT.computeInverseDCT(Image[i]);

        rowWiseTransImage[i] = dctRow;
    }

    return rowWiseTransImage;
}

std::vector<std::vector<float>> TwoDimDCT::computeInverseDCTColumnWise(const std::vector<std::vector<float>> &rowWiseTransImage) const
{
    int rows = static_cast<int>(rowWiseTransImage.size());
    int cols = static_cast<int>(rowWiseTransImage[0].size());

    std::vector<std::vector<float>> twoDimDCTResult(rows, std::vector<float>(cols, 0.0f));


    for (int j = 0; j < cols; ++j)
    {
        std::vector<float> column(rows);
        for (int i = 0; i < rows; ++i)
        {
            column[i] = rowWiseTransImage[i][j];
        }

        auto dctCol = m_DCT.computeInverseDCT(column);

        for (int i = 0; i < rows; ++i)
        {
            twoDimDCTResult[i][j] = dctCol[i];
        }
    }

    return twoDimDCTResult;
}