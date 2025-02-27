#ifndef DCT_TRANSFORMATION_HANDLER_H
#define DCT_TRANSFORMATION_HANDLER_H

#include "QuantizationTable.h"
#include "ImageChopper.h"
#include "DCT.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <functional>

class DCTTransformationHandler
{
public:
    std::vector<std::vector<std::vector<float>>> DCTTransformImage(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &QuantizationTable, int CHUNCK_SIZE = 8) const;

    std::vector<std::vector<float>> inverseDCTTransformImage(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                             const std::vector<std::vector<int>> &QuantizationTable,
                                                             const int originalHeight,
                                                             const int originalWidth) const;

private:
    std::vector<std::vector<std::vector<float>>> ApplyDCTToImagechunks(const std::vector<std::vector<std::vector<float>>> &imageChuncks) const;
    std::vector<std::vector<std::vector<float>>> ApplyInverseDCTToImageChunks(const std::vector<std::vector<std::vector<float>>> &DCTImageChuncks) const;
    
    std::vector<std::vector<std::vector<float>>> QuantizeImageChunks(std::vector<std::vector<std::vector<float>>> &DCTImageChuncks,
                                                                    const std::vector<std::vector<int>> &quantizationTable,
                                                                    std::function<float(float, int)> devideOrMultiply) const;

    static std::function<float(float, int)> divide;
    static std::function<float(float, int)> multiply;
};

#endif // DCT_TRANSFORMATION_HANDLER_H
