#ifndef ICOMPRESSIONSTRATEGY_H
#define ICOMPRESSIONSTRATEGY_H

#include "BaseCompressedImageHolder.h"
#include "Image.h"
#include <vector>


class ICompressionStrategy
{
public:
    virtual ~ICompressionStrategy() = default;

    virtual BaseCompressedImageHolder compress(const Image &image, const std::vector<std::vector<int>> &quantizationTable) const = 0;

    virtual Image decompress(const CompressionLevel &compressedData) const = 0;

};

#endif // ICOMPRESSIONSTRATEGY_H
