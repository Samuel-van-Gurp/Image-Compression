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
#include <iostream>
#include <chrono>

class DCTCompression : public ICompressionStrategy
{
public:
    DCTCompression();

    std::unique_ptr<BaseCompressedImageHolder> compress(const Image &image, const CompressionLevel compressionLevel) const override;
    Image decompress(BaseCompressedImageHolder &compressedImageHolder) const override;

private:
    const int CHUNK_SIZE;

    ImageChopper m_imageChopper;
    DCTTransformationHandler m_dctTransformationHandler;
    RunLengthEnoding m_runlengthEnoding;
    ZigzagDCTcoefficientsOrder m_zigzagDCTcoefficientsOrder;

    std::unique_ptr<BaseCompressedImageHolder> createCompressedImageHolder(const std::vector<std::vector<std::pair<float, int>>> &encodedImage, const std::vector<std::vector<int>> &quantizationTable, const std::vector<std::vector<float>> &imageVector, int chunkSize) const;
    std::vector<std::vector<std::pair<float, int>>> processImageBlocks(const std::vector<std::vector<std::vector<float>>> &imageChunks, const std::vector<std::vector<int>> &quantizationTable) const;
    std::vector<std::pair<float, int>> processImageBlock(const std::vector<std::vector<float>> &imageBlock, const std::vector<std::vector<int>> &quantizationTable) const;
};

#endif // DCT_COMPRESSION_H