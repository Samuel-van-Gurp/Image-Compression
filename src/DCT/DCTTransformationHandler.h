#ifndef DCT_TRANSFORMATION_HANDLER_H
#define DCT_TRANSFORMATION_HANDLER_H

#include "QuantizationTable.h"
#include "CompressionLevel.h"
#include "ImageChopper.h"
#include "DCT.h"
#include "TwoDimDCT.h"
#include <future>
#include <thread>
#include <vector>
#include <functional>
#include <iostream>

class DCTTransformationHandler
{
public:
    explicit DCTTransformationHandler(const int ImageBlocksize);

    std::vector<std::vector<std::vector<float>>> DCTTransformImage(const std::vector<std::vector<float>> &image,
                                                                   const CompressionLevel &compressionLevel,
                                                                   int CHUNCK_SIZE = 8) const;

    std::vector<std::vector<float>> inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChunks, const std::vector<std::vector<int>> &QuantizationTable, const int originalHeight, const int originalWidth) const;

    std::vector<std::vector<float>> inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                             const CompressionLevel &compressionLevel,
                                                             const int originalHeight,
                                                             const int originalWidth) const;
    std::vector<std::vector<float>> Forwardblock(const std::vector<std::vector<float>> &imageBlock, const std::vector<std::vector<int>>& quantizationTable) const;

    std::vector<std::vector<float>> InverseBlock(const std::vector<std::vector<float>> &dctBlock, const std::vector<std::vector<int>>& quantizationTable) const;

private:
    TwoDimDCT m_TwoDimDCT;

    std::vector<std::vector<std::vector<float>>> ApplyDCTToImagechunks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const;
    std::vector<std::vector<std::vector<float>>> ApplyInverseDCTToImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const;

    std::vector<std::vector<std::vector<float>>> QuantizeImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                                     const std::vector<std::vector<int>> &quantizationTable,
                                                                     std::function<float(float, int)> devideOrMultiply) const;

    std::vector<std::vector<float>> QuantizeChunk(const std::vector<std::vector<float>> &chunk, const std::vector<std::vector<int>> &quantizationTable, std::function<float(float, int)> devideOrMultiply) const;

    static std::function<float(float, int)> divide;
    static std::function<float(float, int)> multiply;
};

#endif // DCT_TRANSFORMATION_HANDLER_H
