#include "ImageChopper.h"
#include <algorithm>

std::vector<std::vector<std::vector<float>>> ImageChopper::chopImage(const std::vector<std::vector<float>> &image, int chopSize) const
{   
    std::vector<std::vector<float>> processedImage = image;
    
    if (!areSidesMultipleOfBlockSize(static_cast<int>(image.size()), static_cast<int>(image[0].size()), chopSize))
    {

        processedImage = padImage(image, chopSize); // create padded image

    }

    int ImageHeight = static_cast<int>(processedImage.size());
    int ImageWidth = static_cast<int>(processedImage[0].size());

    std::vector<std::vector<std::vector<float>>> chops;

    for (int row = 0; row < ImageHeight; row += chopSize)
    {
        for (int col = 0; col < ImageWidth; col += chopSize)
        {
            chops.push_back(extractImageBlock(processedImage, row, col, chopSize));
        }
    }
    return chops;
}

bool ImageChopper::areSidesMultipleOfBlockSize(const int height, const int width,const int chopSize) const 
{
    return height % chopSize == 0 && width % chopSize == 0;
    
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
            if (index < choppedImage.size()) {
                insertImageBlock(reconstructedImage, choppedImage[index], row, col);
            }
            index++;
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

// void ImageChopper::insertImageBlock(std::vector<std::vector<float>> &image, const std::vector<std::vector<float>> &block, int row, int col) const
// {
//     int chopSize = static_cast<int>(block.size());

//     for (int i = 0; i < chopSize; ++i)
//     {
//         for (int j = 0; j < chopSize; ++j)
//         {
//             image[row + i][col + j] = block[i][j];
//         }
//     }
// }
void ImageChopper::insertImageBlock(std::vector<std::vector<float>> &image, const std::vector<std::vector<float>> &block, int row, int col) const
{
    int chopSize = static_cast<int>(block.size());
    int maxRow = static_cast<int>(image.size());
    int maxCol = maxRow > 0 ? static_cast<int>(image[0].size()) : 0;

    for (int i = 0; i < chopSize; ++i)
    {
        if (row + i >= maxRow) break; // Stop if we reach the end of the image
        
        for (int j = 0; j < chopSize; ++j)
        {
            if (col + j >= maxCol) break; // Stop if we reach the end of the row
            image[row + i][col + j] = block[i][j];
        }
    }
}