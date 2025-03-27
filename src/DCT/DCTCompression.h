#ifndef DCT_COMPRESSION_H
#define DCT_COMPRESSION_H

#include "CompressedDCTImageHolder.h"
#include "DCTTransformationHandler.h"
#include "QuantizationTable.h"
#include "DCTEncoding.h"
#include "ICompressionStrategy.h"

#include "Image.h"
#include <future> 
#include <algorithm>
#include <vector>

class DCTCompression : public ICompressionStrategy 
{
public:
    std::unique_ptr<BaseCompressedImageHolder> compress(const Image &image, const CompressionLevel compressionLevel) const override;
    Image decompress(BaseCompressedImageHolder &compressedImageHolder) const;
    
    private:
    std::unique_ptr<BaseCompressedImageHolder> createCompressedImageHolder(const std::vector<std::vector<std::pair<float, int>>> &encodedImage, const std::vector<std::vector<int>> &quantizationTable, const std::vector<std::vector<float>> &imageVector, int chunkSize) const;
};

#endif // DCT_COMPRESSION_H