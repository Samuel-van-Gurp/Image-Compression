#include "CompressionLevel.h"
#include "QuantizationTable.h"
#include "ImageChopper.h"
#include "DCT"
#include <vector>

class DCTCompression
{
public:
    std::vector<std::vector<std::vector<float>>> DCTCompress(const std::vector<std::vector<float>> &image, const CompressionLevel compressionLevel) const;

private:
    QuantizationTable getquantizationTable(CompressionLevel compressionLevel) const;

    std::vector<std::vector<std::vector<float>>> ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const;
};
