#include "DCTTransformationHandler.h"
#include <vector>

DCTTransformationHandler::DCTTransformationHandler(const int ImageBlocksize)
    : m_TwoDimDCT(ImageBlocksize)
{
}

std::vector<std::vector<float>> DCTTransformationHandler::Forwardblock(const std::vector<std::vector<float>>& imageBlock, const std::vector<std::vector<int>>& quantizationTable) const
{
    auto dctBlock = m_TwoDimDCT.computeTwoDimDCT(imageBlock);
        
    return QuantizeChunk(dctBlock, quantizationTable, divide);       
}

std::vector<std::vector<float>> DCTTransformationHandler::InverseBlock(const std::vector<std::vector<float>>& dctBlock, const std::vector<std::vector<int>>& quantizationTable) const
{
    auto dequantizedBlock = QuantizeChunk(dctBlock, quantizationTable, multiply);
        
    return m_TwoDimDCT.computeTwoDimInverseDCT(dequantizedBlock);       
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::DCTTransformImage(const std::vector<std::vector<float>> &image, const CompressionLevel &compressionLevel, int CHUNK_SIZE) const
{
    ImageChopper imageChopper;
    auto quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);

    auto imageChunks = imageChopper.chopImage(image, CHUNK_SIZE);

    std::vector<std::vector<std::vector<float>>> result(imageChunks.size());
        
    for (size_t i = 0; i < imageChunks.size(); ++i) {

        auto dctBlock = m_TwoDimDCT.computeTwoDimDCT(imageChunks[i]);
        
        result.emplace_back(QuantizeChunk(dctBlock, quantizationTable, divide));
    }
    
    return result;
}

std::vector<std::vector<float>> DCTTransformationHandler::inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                   const std::vector<std::vector<int>> &QuantizationTable,
                                                                                   const int originalHeight,
                                                                                   const int originalWidth) const
{
    ImageChopper imageChopper;

    std::vector<std::vector<std::vector<float>>> ImageChunks;

    // loop over image chunks
    for (const auto &chunk : DCTImageChunks)
    {
        ImageChunks.push_back(m_TwoDimDCT.computeTwoDimInverseDCT(QuantizeChunk(chunk, QuantizationTable, multiply)));
    }
    auto result = imageChopper.reconstructImage(ImageChunks, originalHeight, originalWidth);

    return result;
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::QuantizeImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                           const std::vector<std::vector<int>> &quantizationTable,
                                                                                           std::function<float(float, int)> devideOrMultiply) const
{
    std::vector<std::vector<std::vector<float>>> quantizedImageChunks;

    for (auto &chunk : DCTImageChunks)
    {
        // trow if chuncksize is not 8x8
        if (chunk.size() != 8 || chunk[0].size() != 8)
        {
            throw std::invalid_argument("Chunks are not 8x8");
        }

        quantizedImageChunks.push_back(QuantizeChunk(chunk, quantizationTable, devideOrMultiply));
    }
    return quantizedImageChunks;
}

std::vector<std::vector<float>> DCTTransformationHandler::QuantizeChunk(const std::vector<std::vector<float>> &chunk,
                                                                        const std::vector<std::vector<int>> &quantizationTable,
                                                                        std::function<float(float, int)> devideOrMultiply) const
{
    std::vector<std::vector<float>> quantizedChunk(chunk.size(), std::vector<float>(chunk[0].size(), 0));

    for (size_t i = 0; i < chunk.size(); ++i)
    {
        for (size_t j = 0; j < chunk[i].size(); ++j)
        {
            quantizedChunk[i][j] = std::round(devideOrMultiply(chunk[i][j], quantizationTable[i][j]));
        }
    }

    return quantizedChunk;
}

std::function<float(float, int)> DCTTransformationHandler::divide = [](float a, int b) -> float
{
    return (b != 0) ? (a / b) : 0.0f; // Avoid division by zero
};

std::function<float(float, int)> DCTTransformationHandler::multiply = [](float a, int b) -> float
{
    return a * b;
};

// std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyInverseDCTToImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChunks) const
// {

//     std::vector<std::vector<std::vector<float>>> imageChunks;

//     for (const auto &chunk : DCTImageChunks)
//     {
//         imageChunks.push_back(m_TwoDimDCT.computeTwoDimInverseDCT(chunk));
//     }

//     return imageChunks;
// }
// std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyDCTToImagechunks(const std::vector<std::vector<std::vector<float>>> &imageChunks) const
// {
//     std::vector<std::vector<std::vector<float>>> DCTImageChunks;

//     for (auto const &chunk : imageChunks)
//     {
//         auto DCTImageChunk = m_TwoDimDCT.computeTwoDimDCT(chunk);

//         DCTImageChunks.push_back(DCTImageChunk);

//     }

//     return DCTImageChunks;
// }
