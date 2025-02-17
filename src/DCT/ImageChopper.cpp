#include "ImageChopper.h"

std::vector<std::vector<std::vector<float>>> ImageChopper::chopImage(const std::vector<std::vector<float>> &Image, const int chopSize) const
{

    std::vector<std::vector<float>> paddedImage;

    if (Image.size() % chopSize != 0 || Image[0].size() % chopSize != 0)
    {
        paddedImage = padImage(Image, chopSize);
    }
    else
    {
        paddedImage = Image;
    }

    int paddedImageHeight = static_cast<int>(paddedImage[0].size());
    int paddedImageWidth = static_cast<int>(paddedImage.size());
    int numberOfChops = (paddedImageWidth / chopSize) * (paddedImageHeight / chopSize);

    std::vector<std::vector<std::vector<float>>> chops = getImageBlocks(paddedImage, chopSize, numberOfChops);
    return chops;
}

std::vector<std::vector<std::vector<float>>> ImageChopper::getImageBlocks(const std::vector<std::vector<float>> &paddedImage, const int chopSize, const int numberOfChops) const
{
    std::vector<std::vector<std::vector<float>>> chops;
    chops.reserve(numberOfChops);

    int paddedImageWidth = static_cast<int>(paddedImage.size());
    int paddedImageHeight = static_cast<int>(paddedImage[0].size());

    for (int row = 0; row < paddedImageWidth; row += chopSize)
    {
        for (int col = 0; col < paddedImageHeight; col += chopSize)
        {
            extractImageBlock(paddedImage, row, col, chopSize, chops);
        }
    }

    return chops;
}

void ImageChopper::extractImageBlock(const std::vector<std::vector<float>> &paddedImage, int row, int col, int chopSize, std::vector<std::vector<std::vector<float>>> &chops) const
{
    std::vector<std::vector<float>> block;
    block.reserve(chopSize);
    for (int i = 0; i < chopSize; ++i)
    {
        block.push_back(std::vector<float>(
            paddedImage[row + i].begin() + col,
            paddedImage[row + i].begin() + col + chopSize));
    }
    chops.push_back(block);
}

std::vector<std::vector<float>> ImageChopper::padImage(const std::vector<std::vector<float>> &Image, const int chopSize) const
{
    int imagewidth = static_cast<int>(Image.size());
    int imageheight = static_cast<int>(Image[0].size());

    int extraWidth = (chopSize - (imagewidth % chopSize)) % chopSize;
    int extraHeight = (chopSize - (imageheight % chopSize)) % chopSize;
    int newWidth = imagewidth + extraWidth;
    int newHeight = imageheight + extraHeight;

    std::vector<std::vector<float>> paddedImage(newWidth, std::vector<float>(newHeight, 0));

    for (int i = 0; i < imagewidth; i++)
    {
        for (int j = 0; j < imageheight; j++)
        {
            paddedImage[i][j] = Image[i][j];
        }
    }
    return paddedImage;
}
