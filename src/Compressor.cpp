#include "Compressor.h"

Compressor::Compressor()
{
}

float const Compressor::IntensityThresholdValue(const cv::Mat &magnitude, float percentile) const
{

    const float PERCENTILE_SCALE = 100.0f;

    cv::Mat flattened = magnitude.reshape(1, 1).clone();
    cv::Mat sorted;
    cv::sort(flattened, sorted, cv::SORT_DESCENDING);

    int index = static_cast<int>(sorted.cols * (percentile / PERCENTILE_SCALE));
    index = std::min(index, sorted.cols - 1); // clap to range

    float threshold = sorted.at<float>(index);

    return threshold;
}

cv::Mat Compressor::MakeSubSamplingMask(const cv::Mat &magnitude, float threshold) const
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

cv::Mat Compressor::applyMask(const cv::Mat &complexImage, const cv::Mat &mask) const
{
    cv::Mat planes[2];
    cv::split(complexImage, planes);

    cv::Mat maskFloat;
    mask.convertTo(maskFloat, CV_32F); // Convert to float

    // cv::Mat maskFloat = convertTOFloatMat(mask);

    cv::Mat maskedPlanes[] = {planes[0].mul(maskFloat), planes[1].mul(maskFloat)};

    cv::Mat maskedComplexImage;
    cv::merge(maskedPlanes, 2, maskedComplexImage); // Merge back to complex format

    return maskedComplexImage;
}

SparseRepresentation Compressor::compress(const Image &image, float percentile) const
{
    DFT dft;

    cv::Mat DFTImage = dft.computeDFT(image.getImageMatrix());
    cv::Mat magnitude = dft.Magnitude(DFTImage);
    float threshold = IntensityThresholdValue(magnitude, percentile);
    cv::Mat mask = MakeSubSamplingMask(magnitude, threshold);
    cv::Mat maskedDFTImage = applyMask(DFTImage, mask);

    SparseRepresentation sparseRepr = SparseRepresentation(maskedDFTImage);

    return sparseRepr;
}

Image Compressor::decompress(const SparseRepresentation &sparseRepr) const
{
    DFT dft;

    cv::Mat decodedSparceCompresDFTimage = sparseRepr.convertToDenseComplexMatrix();

    cv::Mat decodedSparceCompresImage = dft.computeInverseDFT(decodedSparceCompresDFTimage);

    return Image(decodedSparceCompresImage);
}
