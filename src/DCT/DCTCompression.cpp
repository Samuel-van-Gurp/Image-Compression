#include "DCTCompression.h"
#include "TwoDimDCT.h"
#include <vector>

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::DCTTransformImage(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &QuantizationTable, int CHUNCK_SIZE) const
{
    ImageChopper imageChopper;

    auto imageChuncks = imageChopper.chopImage(image, CHUNCK_SIZE);

    auto DCTImageChuncks = ApplyDCTToImagechuncks(imageChuncks);

    QuantizeImageChunks(DCTImageChuncks, QuantizationTable, divide);
    return DCTImageChuncks;
}

std::vector<std::vector<float>> DCTTransformationHandler::inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                                                   const std::vector<std::vector<int>> &QuantizationTable,
                                                                                   const int originalHeight,
                                                                                   const int originalWidth) const
{
    ImageChopper imageChopper;

    QuantizeImageChunks(DCTImageChuncks, QuantizationTable, multiply);

    auto imageChuncks = ApplyInverseDCTToImageChuncks(DCTImageChuncks);

    return imageChopper.reconstructImage(imageChuncks, originalHeight, originalWidth);
}

void DCTTransformationHandler::QuantizeImageChunks(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                   const std::vector<std::vector<int>> &quantizationTable,
                                                   std::function<float(float, int)> devideOrMultiply) const
{

    for (auto &chunck : DCTImageChuncks)
    {
        for (size_t i = 0; i < chunck.size(); ++i)
        {
            for (size_t j = 0; j < chunck[i].size(); ++j)
            {
                chunck[i][j] = (std::round(devideOrMultiply(chunck[i][j], quantizationTable[i][j])));
            }
        }
    }
}

std::function<float(float, int)> DCTTransformationHandler::divide = [](float a, int b) -> float
{
    return (b != 0) ? (a / b) : 0.0f; // Avoid division by zero
};

std::function<float(float, int)> DCTTransformationHandler::multiply = [](float a, int b) -> float
{
    return a * b;
};

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyInverseDCTToImageChuncks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const
{
    TwoDimDCT twoDimDCT;
    std::vector<std::vector<std::vector<float>>> imageChuncks;

    for (const auto &chunck : DCTImageChuncks)
    {
        imageChuncks.push_back(twoDimDCT.computeTwoDimInverseDCT(chunck));
    }

    return imageChuncks;
}

std::vector<std::vector<std::vector<float>>> DCTTransformationHandler::ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const
{
    TwoDimDCT twoDimDct;
    std::vector<std::vector<std::vector<float>>> DCTImageChuncks;

    for (auto const &chunck : imageChuncks)
    {
        DCTImageChuncks.push_back(twoDimDct.computeTwoDimDCT(chunck));
    }

    return DCTImageChuncks;
}
