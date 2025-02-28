#ifndef DCT_COMPRESSION_H
#define DCT_COMPRESSION_H

#include "CompressedDCTImageHolder.h"
#include "compressedImageHolder.h"
#include "DCTTransformationHandler.h"
#include "QuantizationTable.h"
#include "DCTEncoding.h"
#include "ICompressionStrategy.h" 

#include <algorithm>
#include <vector>
class DCTCompression // : public ICompressionStrategy TODO
{
public:
    CompressedDCTImageHolder DCTCompress(const std::vector<std::vector<float>> &image, CompressionLevel compressionLevel) const;
    std::vector<std::vector<float>> DCTDecompress(CompressedDCTImageHolder &compressedImageHolder) const;

private:
};

#endif // DCT_COMPRESSION_H