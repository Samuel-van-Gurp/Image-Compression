#include "DCTTransformationHandler.h"
#include <vector>

DCTTransformationHandler::DCTTransformationHandler(const int ImageBlocksize) 
    : m_TwoDimDCT(ImageBlocksize){
}


std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::DCTTransformImage(const std::vector<std::vector<float>> &image, const CompressionLevel &compressionLevel, int CHUNK_SIZE) const
{
    ImageChopper imageChopper;
    
    auto quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);

    auto imageChunks = imageChopper.chopImage(image, CHUNK_SIZE);

    // throw chunks are not 8x8
    if (imageChunks[0].size() != CHUNK_SIZE || imageChunks[0][0].size() != CHUNK_SIZE)
    {
        throw std::invalid_argument("Chunks are not 8x8");
    }
    auto DCTImageChunks = ApplyDCTToImagechunks(imageChunks);

    if (DCTImageChunks[0].size() != CHUNK_SIZE || DCTImageChunks[0][0].size() != CHUNK_SIZE)
    {
        throw std::invalid_argument("Chunks are not 8x8");
    }

    auto QuantisedDCTImageChunks = QuantizeImageChunks(DCTImageChunks,quantizationTable , divide);
    
    return QuantisedDCTImageChunks;
}

std::vector<std::vector<float>> DCTTransformationHandler::inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                   const std::vector<std::vector<int>> &QuantizationTable,
                                                                                   const int originalHeight,
                                                                                   const int originalWidth) const
{
    ImageChopper imageChopper;

    auto dequantisedChunks = QuantizeImageChunks(DCTImageChunks, QuantizationTable, multiply);

    auto imageChunks = ApplyInverseDCTToImageChunks(dequantisedChunks);

    auto result = imageChopper.reconstructImage(imageChunks, originalHeight, originalWidth);
    return result;
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::QuantizeImageChunks(std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                         const std::vector<std::vector<int>> &quantizationTable,
                                                                                         std::function<float(float, int)> devideOrMultiply) const
{
    std::vector<std::vector<std::vector<float>>> quantizedImageChunks;

    for (auto &chunk : DCTImageChunks)
    {
        std::vector<std::vector<float>> quantizedChunk(chunk.size(), std::vector<float>(chunk[0].size(), 0));
        
        // trow if chuncksize is not 8x8
        if (chunk.size() != 8 || chunk[0].size() != 8)
        {
            throw std::invalid_argument("Chunks are not 8x8");
        }

        for (size_t i = 0; i < chunk.size(); ++i)
        {
            // init the quantised chunk same size as the chunk
            for (size_t j = 0; j < chunk[i].size(); ++j)
            {
                quantizedChunk[i][j] = std::round(devideOrMultiply(chunk[i][j], quantizationTable[i][j]));
            }
        }
        quantizedImageChunks.push_back(quantizedChunk);
    }
    return quantizedImageChunks;
}

std::function<float(float, int)> DCTTransformationHandler::divide = [](float a, int b) -> float
{
    return (b != 0) ? (a / b) : 0.0f; // Avoid division by zero
};

std::function<float(float, int)> DCTTransformationHandler::multiply = [](float a, int b) -> float
{
    return a * b;
};

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyInverseDCTToImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChunks) const
{
    // TwoDimDCT twoDimDCT = TwoDimDCT(DCTImageChunks[0]);
    
    std::vector<std::vector<std::vector<float>>> imageChunks;

    for (const auto &chunk : DCTImageChunks)
    {
        imageChunks.push_back(m_TwoDimDCT.computeTwoDimInverseDCT(chunk));
    }

    return imageChunks;
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyDCTToImagechunks(const std::vector<std::vector<std::vector<float>>> &imageChunks) const
{
    // TwoDimDCT twoDimDct = TwoDimDCT(imageChunks[0]);
    std::vector<std::vector<std::vector<float>>> DCTImageChunks;

    for (auto const &chunk : imageChunks)
    {
        auto DCTImageChunk = m_TwoDimDCT.computeTwoDimDCT(chunk);

        // print size of the image chunks
        DCTImageChunks.push_back(DCTImageChunk);

    }

    return DCTImageChunks;
}
