#include "DCTCompression.h"
#include "TwoDimDCT.h"
#include <vector>

std::vector<std::vector<std::vector<float>>> DCTCompression::DCTCompress(const std::vector<std::vector<float>> &image, const CompressionLevel compressionLevel) const
{
    ImageChopper imageChopper;
    int CHUNCK_SIZE = 8;

    auto imageChuncks = imageChopper.chopImage(image, CHUNCK_SIZE);

    auto DCTImageChuncks = ApplyDCTToImagechuncks(imageChuncks);

    auto quantizedImageChuncks = QuantizeImageChuncks(DCTImageChuncks, getQuantizationTable(compressionLevel));

    return quantizedImageChuncks;
}

std::vector<std::vector<float>> DCTCompression::DCTDecompress(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                              const CompressionLevel compressionLevel,
                                                              const int originalHeight,
                                                              const int originalWidth) const
{
    ImageChopper imageChopper;

    auto DeQuantisizedDCTImageChuncks = DeQuantisizeImageChuncks(DCTImageChuncks, getQuantizationTable(compressionLevel));

    auto imageChuncks = ApplyInverseDCTToImageChuncks(DeQuantisizedDCTImageChuncks);

    return imageChopper.reconstructImage(imageChuncks, originalHeight, originalWidth);
}

std::vector<std::vector<std::vector<float>>> DCTCompression::DeQuantisizeImageChuncks(std::vector<std::vector<std::vector<float>>> imageChuncks,
                                                                                      const std::vector<std::vector<int>> &quantizationTable) const
{
    for (auto &chunck : imageChuncks)
    {
        for (size_t i = 0; i < chunck.size(); ++i)
        {
            for (size_t j = 0; j < chunck[i].size(); ++j)
            {
                chunck[i][j] = chunck[i][j] * quantizationTable[i][j];
            }
        }
    }

    return imageChuncks;
}

std::vector<std::vector<std::vector<float>>> DCTCompression::ApplyInverseDCTToImageChuncks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const
{
    TwoDimDCT twoDimDCT;
    std::vector<std::vector<std::vector<float>>> imageChuncks;

    for (const auto &chunck : DCTImageChuncks)
    {
        imageChuncks.push_back(twoDimDCT.computeTwoDimInverseDCT(chunck));
    }

    return imageChuncks;
}

std::vector<std::vector<int>> DCTCompression::getQuantizationTable(CompressionLevel compressionLevel) const
{
    switch (compressionLevel)
    {
    case CompressionLevel::LOW:
        return QuantizationTable::lowCompressionTable;
    case CompressionLevel::MEDIUM:
        return QuantizationTable::mediumCompressionTable;
    case CompressionLevel::HIGH:
        return QuantizationTable::highCompressionTable;
    case CompressionLevel::VERY_HIGH:
        return QuantizationTable::veryHighCompressionTable;
    case CompressionLevel::ULTRA_HIGH:
        return QuantizationTable::ultraHighCompressionTable;
    default:
        return QuantizationTable::lowCompressionTable;
    }
}

std::vector<std::vector<std::vector<float>>> DCTCompression::ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const
{
    TwoDimDCT twoDimDct;
    std::vector<std::vector<std::vector<float>>> DCTImageChuncks;

    for (auto const &chunck : imageChuncks)
    {
        DCTImageChuncks.push_back(twoDimDct.computeTwoDimDCT(chunck));
    }

    return DCTImageChuncks;
}

std::vector<std::vector<std::vector<float>>> DCTCompression::QuantizeImageChuncks(std::vector<std::vector<std::vector<float>>> DCTImageChuncks,
                                                                                  const std::vector<std::vector<int>> &quantizationTable) const
{

    for (auto &chunck : DCTImageChuncks)
    {
        for (size_t i = 0; i < chunck.size(); ++i)
        {
            for (size_t j = 0; j < chunck[i].size(); ++j)
            {
                chunck[i][j] = std::round(chunck[i][j] / quantizationTable[i][j]);
                // std::cout << "chunck[i][j]:" << chunck[i][j] << std::endl;
                // round to nearest integer
            }
        }
    }

    return DCTImageChuncks;
}
