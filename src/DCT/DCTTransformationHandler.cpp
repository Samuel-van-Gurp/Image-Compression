#include "DCTTransformationHandler.h"
#include "TwoDimDCT.h"
#include <vector>

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::DCTTransformImage(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &QuantizationTable, int CHUNK_SIZE) const
{
    ImageChopper imageChopper;

    auto imageChunks = imageChopper.chopImage(image, CHUNK_SIZE);

    auto DCTImageChunks = ApplyDCTToImagechunks(imageChunks);

    auto QuantisedDCTImageChunks = QuantizeImageChunks(DCTImageChunks, QuantizationTable, divide);
    
    return QuantisedDCTImageChunks;
}

std::vector<std::vector<float>> DCTTransformationHandler::inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                   const std::vector<std::vector<int>> &QuantizationTable,
                                                                                   const int originalHeight,
                                                                                   const int originalWidth) const
{
    ImageChopper imageChopper;

    QuantizeImageChunks(DCTImageChunks, QuantizationTable, multiply);

    auto imageChunks = ApplyInverseDCTToImageChunks(DCTImageChunks);

    return imageChopper.reconstructImage(imageChunks, originalHeight, originalWidth);
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::QuantizeImageChunks(std::vector<std::vector<std::vector<float>>> &DCTImageChunks,
                                                                                         const std::vector<std::vector<int>> &quantizationTable,
                                                                                         std::function<float(float, int)> devideOrMultiply) const
{
    std::vector<std::vector<std::vector<float>>> quantizedImageChunks;

    for (auto &chunk : DCTImageChunks)
    {
        std::vector<std::vector<float>> quantizedChunk(chunk.size(), std::vector<float>(chunk[0].size(), 0));

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
    TwoDimDCT twoDimDCT;
    std::vector<std::vector<std::vector<float>>> imageChunks;

    for (const auto &chunk : DCTImageChunks)
    {
        imageChunks.push_back(twoDimDCT.computeTwoDimInverseDCT(chunk));
    }

    return imageChunks;
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyDCTToImagechunks(const std::vector<std::vector<std::vector<float>>> &imageChunks) const
{
    TwoDimDCT twoDimDct;
    std::vector<std::vector<std::vector<float>>> DCTImageChunks;

    for (auto const &chunk : imageChunks)
    {
        DCTImageChunks.push_back(twoDimDct.computeTwoDimDCT(chunk));
    }

    return DCTImageChunks;
}
