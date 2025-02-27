#ifndef DCT_COMPRESSION_H
#define DCT_COMPRESSION_H

#include "compressedImageHolder.h"
#include "DCTTransformationHandler.h"
#include "QuantizationTable.h"
#include "DCTEncoding.h"

#include <algorithm>
#include <vector>
class DCTCompression
{
public:
    CompressedImageHolder DCTCompress(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &quantizationTable) const;
    std::vector<std::vector<float>> DCTDecompress(CompressedImageHolder &compressedImageHolder) const;

private:
};

#endif // DCT_COMPRESSION_H