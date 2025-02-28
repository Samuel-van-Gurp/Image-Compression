#ifndef COMPRESSED_DCT_IMAGE_HOLDER_H
#define COMPRESSED_DCT_IMAGE_HOLDER_H

#include "QuantizationTable.h"
#include "BaseCompressedImageHolder.h"
#include <vector>

struct CompressedDCTImageHolder : public BaseCompressedImageHolder
{
public:
    // All the info needed to decompress the image later on
    std::vector<std::vector<std::pair<float, int>>> compressedImage;
    std::pair<int, int> OriginalImageDimensions;
    int BLOCK_SIZE;

    std::vector<std::vector<int>> quantizationTable;
};

#endif // COMPRESSED_DCT_IMAGE_HOLDER_H
