#ifndef ICOMPRESSIONSTRATEGY_H
#define ICOMPRESSIONSTRATEGY_H

#include "BaseCompressedImageHolder.h"
#include "CompressionLevel.h"
#include "Image.h"
#include <vector>


class ICompressionStrategy
{
public:
    virtual ~ICompressionStrategy() = default;

    virtual BaseCompressedImageHolder compress(const Image &image, const CompressionLevel compressionlevel) const = 0;

    virtual Image decompress(const CompressionLevel &compressedData) const = 0;

};

#endif // ICOMPRESSIONSTRATEGY_H
