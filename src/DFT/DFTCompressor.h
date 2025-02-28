#include "CompressionLevel.h"
#include "Image.h"
#include "DFT/DFT.h"
#include "SparseRepresentation.h"
#include "ICompressionStrategy.h" 

#include <opencv2/opencv.hpp>

class DFTCompressor //: public ICompressionStrategy TODO
{

public:
    SparseRepresentation compress(const Image &image, CompressionLevel compressionLevel) const;
    Image decompress(const SparseRepresentation &sparseRepr) const;
    
    private:

    float getCompressionPersentile(CompressionLevel) const;
    float const ComputeIntensityThreshold(const cv::Mat &img, float percentile) const;
    void validatePercentileRange(const float percentile) const;
    cv::Mat MakeSubSamplingMask(const cv::Mat &img, float threshold) const;
    cv::Mat applyMask(const cv::Mat &complexImage, const cv::Mat &mask) const;
};
