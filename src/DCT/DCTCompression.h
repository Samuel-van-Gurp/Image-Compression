#include "QuantizationTable.h"
#include "ImageChopper.h"
#include "DCT.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <functional>

class DCTCompression
{
public:
    std::vector<std::vector<std::vector<float>>> DCTCompress(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &QuantizationTable, int CHUNCK_SIZE = 8) const;

    std::vector<std::vector<float>> DCTDecompress(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                  const std::vector<std::vector<int>> &QuantizationTable,
                                                  const int originalHeight,
                                                  const int originalWidth) const;

private:
    std::vector<std::vector<std::vector<float>>> ApplyDCTToImagechuncks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const;
    std::vector<std::vector<std::vector<float>>> ApplyInverseDCTToImageChuncks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const;

    void QuantizeImageChunks(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                             const std::vector<std::vector<int>> &quantizationTable,
                             std::function<float(float, int)> devideOrMultiply) const;

    static std::function<float(float, int)> divide;
    static std::function<float(float, int)> multiply;
};
