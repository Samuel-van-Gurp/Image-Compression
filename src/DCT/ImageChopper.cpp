#include "ImageChopper.h"

#include "ImageChopper.h"
#include <algorithm>

std::vector<std::vector<std::vector<float>>> ImageChopper::chopImage(const std::vector<std::vector<float>> &image, int chopSize) const
{
    std::vector<std::vector<float>> paddedImage = padImage(image, chopSize);
    int paddedImageHeight = static_cast<int>(paddedImage.size());
    int paddedImageWidth = static_cast<int>(paddedImage[0].size());

    std::vector<std::vector<std::vector<float>>> chops;

    for (int row = 0; row < paddedImageHeight; row += chopSize)
    {
        for (int col = 0; col < paddedImageWidth; col += chopSize)
        {
            chops.push_back(extractImageBlock(paddedImage, row, col, chopSize));
        }
    }

    return chops;
}

std::vector<std::vector<float>> ImageChopper::reconstructImage(const std::vector<std::vector<std::vector<float>>> &choppedImage, int originalHeight, int originalWidth) const
{
    int chopSize = static_cast<int>(choppedImage[0].size());
    std::vector<std::vector<float>> reconstructedImage(originalHeight, std::vector<float>(originalWidth, 0));

    int index = 0;
    for (int row = 0; row < originalHeight; row += chopSize)
    {
        for (int col = 0; col < originalWidth; col += chopSize)
        {
            insertImageBlock(reconstructedImage, choppedImage[index++], row, col);
        }
    }

    return reconstructedImage;
}

std::vector<std::vector<float>> ImageChopper::padImage(const std::vector<std::vector<float>> &image, int chopSize) const
{
    int height = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    int paddedHeight = ((height + chopSize - 1) / chopSize) * chopSize;
    int paddedWidth = ((width + chopSize - 1) / chopSize) * chopSize;

    std::vector<std::vector<float>> paddedImage(paddedHeight, std::vector<float>(paddedWidth, 0));

    for (int i = 0; i < height; ++i)
    {
        std::copy(image[i].begin(), image[i].end(), paddedImage[i].begin());
    }

    return paddedImage;
}

std::vector<std::vector<float>> ImageChopper::extractImageBlock(const std::vector<std::vector<float>> &image, int row, int col, int chopSize) const
{
    std::vector<std::vector<float>> block(chopSize, std::vector<float>(chopSize, 0));

    for (int i = 0; i < chopSize; ++i)
    {
        for (int j = 0; j < chopSize; ++j)
        {
            block[i][j] = image[row + i][col + j];
        }
    }

    return block;
}

void ImageChopper::insertImageBlock(std::vector<std::vector<float>> &image, const std::vector<std::vector<float>> &block, int row, int col) const
{
    int chopSize = static_cast<int>(block.size());

    for (int i = 0; i < chopSize; ++i)
    {
        for (int j = 0; j < chopSize; ++j)
        {
            image[row + i][col + j] = block[i][j];
        }
    }
}
