#include "CompressionLevel.h"
#include "QuantizationTable.h"
#include "ImageChopper.h"
#include "DCT.h"
#include <opencv2/opencv.hpp>
#include <vector>

class DCTCompression
{
public:
    std::vector<std::vector<std::vector<float>>> DCTCompress(const std::vector<std::vector<float>> &image,
                                                             const CompressionLevel compressionLevel) const;

    std::vector<std::vector<float>> DCTDecompress(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                  const CompressionLevel compressionLevel,
                                                  const int originalHeight,
                                                  const int originalWidth) const;

private:
    std::vector<std::vector<int>> getQuantizationTable(CompressionLevel compressionLevel) const;

    std::vector<std::vector<std::vector<float>>> ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const;

    std::vector<std::vector<std::vector<float>>> DeQuantisizeImageChuncks(std::vector<std::vector<std::vector<float>>> imageChuncks, const std::vector<std::vector<int>> &quantizationTable) const;
    std::vector<std::vector<std::vector<float>>> QuantizeImageChuncks(std::vector<std::vector<std::vector<float>>> DCTImageChuncks, const std::vector<std::vector<int>> &quantizationTable) const;

    std::vector<std::vector<std::vector<float>>> ApplyInverseDCTToImageChuncks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const;
};
