#include "CompressedDCTImageHolder.h"

float CompressedDCTImageHolder::getCompressionRatio() const
{

    // structured binding to read pair
    auto [originalWidth, originalHeight] = OriginalImageDimensions;
    int originalSize = originalWidth * originalHeight;

    int totalpairs = 0;
    for (const auto &block : compressedImage)
    {
        block;
        totalpairs += static_cast<int>(block.size());

    }
    const int numberOfVelues = totalpairs;

    

    return static_cast<float>(originalSize) / (numberOfVelues);
}
