#ifndef DCT_COMPRESSION_H
#define DCT_COMPRESSION_H

#include "CompressedDCTImageHolder.h"
#include "DCTTransformationHandler.h"
#include "QuantizationTable.h"
#include "DCTEncoding.h"
#include "ICompressionStrategy.h"

#include "Image.h"

#include <algorithm>
#include <vector>

class DCTCompression : public ICompressionStrategy 
{
public:
    std::unique_ptr<BaseCompressedImageHolder> compress(const Image &image, CompressionLevel compressionLevel) const;
    Image decompress(BaseCompressedImageHolder &compressedImageHolder) const;

private:
};

#endif // DCT_COMPRESSION_H