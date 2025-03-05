#include "DFTCompressor.h"

std::unique_ptr<BaseCompressedImageHolder> DFTCompressor::compress(const Image &image, CompressionLevel compressionLevel) const
{

    float percentile = getCompressionPersentile(compressionLevel);

    validatePercentileRange(percentile);

    DFT dft;

    cv::Mat DFTImage = dft.computeDFT(image.getImageMatrix());
    cv::Mat magnitude = dft.Magnitude(DFTImage);
    float threshold = ComputeIntensityThreshold(magnitude, percentile);
    cv::Mat mask = MakeSubSamplingMask(magnitude, threshold);
    cv::Mat maskedDFTImage = applyMask(DFTImage, mask);

    CompressedDFTImageHolder sparseRepr = CompressedDFTImageHolder(maskedDFTImage);

    auto sparseRepr_ptr = std::make_unique<CompressedDFTImageHolder>(sparseRepr);

    return sparseRepr_ptr; // impisit conversion from unique_ptr<CompressedDFTImageHolder> to unique_ptr<unique_ptrBaseCompressedImageHolder>
}

Image DFTCompressor::decompress(BaseCompressedImageHolder &sparseRepr) const
{
    DFT dft;

    // cast to derived type
    const auto &sparseRepr_derivedtype = dynamic_cast<const CompressedDFTImageHolder &>(sparseRepr);

    cv::Mat decodedSparceCompresDFTimage = sparseRepr_derivedtype.convertToDenseComplexMatrix();

    cv::Mat decodedSparceCompresImage = dft.computeInverseDFT(decodedSparceCompresDFTimage);

    return Image(decodedSparceCompresImage);
}

float DFTCompressor::getCompressionPersentile(CompressionLevel compressionLevel) const
{
    switch (compressionLevel)
    {
    case CompressionLevel::NONE:
        return 100.0f;
    case CompressionLevel::LOW:
        return 50.0f;
    case CompressionLevel::MEDIUM:
        return 10.0f;
    case CompressionLevel::HIGH:
        return 1.0f;
    case CompressionLevel::VERY_HIGH:
        return 0.1f;
    case CompressionLevel::ULTRA_HIGH:
        return 0.01f;
    default:
        return 100.0f;
    }
}

float const DFTCompressor::ComputeIntensityThreshold(const cv::Mat &magnitude, float percentile) const
{

    const float PERCENTILE_SCALE = 100.0f;

    cv::Mat flattened = magnitude.reshape(1, 1);
    cv::Mat sorted;
    cv::sort(flattened, sorted, cv::SORT_DESCENDING);

    int index = static_cast<int>(sorted.cols * (percentile / PERCENTILE_SCALE));

    index = std::min(index, sorted.cols - 1); // clamp to range

    float threshold = sorted.at<float>(index);

    return threshold;
}

void DFTCompressor::validatePercentileRange(const float percentile) const
{
    if (percentile < 0.0f || percentile > 100.0f)
    {
        throw std::invalid_argument("Percentile must be between 0 and 100.");
    }
}

cv::Mat DFTCompressor::MakeSubSamplingMask(const cv::Mat &magnitude, float threshold) const
{
    cv::Mat mask = cv::Mat::zeros(magnitude.size(), CV_32F);

    for (int i = 0; i < magnitude.rows; i++)
    {
        for (int j = 0; j < magnitude.cols; j++)
        {
            if (magnitude.at<float>(i, j) > threshold)
            {
                mask.at<float>(i, j) = 1;
            }
        }
    }
    return mask;
}

cv::Mat DFTCompressor::applyMask(const cv::Mat &complexImage, const cv::Mat &mask) const
{
    cv::Mat planes[2];
    cv::split(complexImage, planes);

    cv::Mat maskFloat;
    mask.convertTo(maskFloat, CV_32F); // Convert to float

    cv::Mat maskedPlanes[] = {planes[0].mul(maskFloat), planes[1].mul(maskFloat)};

    cv::Mat maskedComplexImage;
    cv::merge(maskedPlanes, 2, maskedComplexImage); // Merge back to complex format

    return maskedComplexImage;
}
