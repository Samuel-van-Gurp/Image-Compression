#include "DCTCompression.h"

#include <vector>

std::vector<std::vector<std::vector<float>>> DCTCompression::DCTCompress(const std::vector<std::vector<float>> &image, const CompressionLevel compressionLevel) const
{
    ImageChopper imageChopper;
    int CHUNCK_SIZE = 8;

    auto imageChuncks = imageChopper.chopImage(image, CHUNCK_SIZE);

    auto DCTImageChuncks = ApplyDCTToImagechuncks(imageChuncks);

    auto quantizedImageChuncks = QuantizeImageChuncks(DCTImageChuncks, getquantizationTable(compressionLevel));

    return std::vector<std::vector<std::vector<float>>>();
}

QuantizationTable DCTCompression::getqQuantizationTable(CompressionLevel compressionLevel) const
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
    default:
        return QuantizationTable::lowCompressionTable;
    }
}

std::vector<std::vector<std::vector<float>>> DCTCompression::ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const
{
    DCT dct;
    std::vector<std::vector<std::vector<float>>> DCTImageChuncks;

    for (auto &chunck : image)
    {
        std::vector<std::vector<float>> DCTChunck;
        for (auto &row : chunck)
        {
            DCTChunck.push_back(dct.computeDCT(row));
        }
        DCTImageChuncks.push_back(DCTChunck);
    }

    return DCTImageChuncks;
}
std::vector<std::vector<std::vector<float>>> DCTCompression::QuantizeImageChuncks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks, const QuantizationTable &quantizationTable) const
{

    for (auto &chunck : DCTImageChuncks)
    {
        for (size_t i = 0; i < chunck.size(); ++i)
        {
            for (size_t j = 0; j < chunck[i].size(); ++j)
            {
                chunck[i][j] = chunck[i][j] / QuantizationTable::quantizationTable[i][j];
            }
        }
    }
}
