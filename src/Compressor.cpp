#include "Compressor.h"


Compressor::Compressor()
{
}

cv::Mat Compressor::computeDFT(const cv::Mat& img) const
{   
    // TODO: add padding for optimal size for effcent DFT
    cv::Mat floatImage = convertTOFloatMat(img);
    
    cv::Mat complexImage = prepareComplex2channelMat(floatImage);

    // Compute DFT
    cv::dft(complexImage, complexImage);

    return complexImage;
}

cv::Mat Compressor::prepareComplex2channelMat(const cv::Mat& floatImage) const
{   

    cv::Mat planes[] = { floatImage, cv::Mat::zeros(floatImage.size(), CV_32F) };
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);

    return complexImage;
}

cv::Mat Compressor::convertTOFloatMat(const Image& img) const
{
    cv::Mat floatImage;
    img.getImage().convertTo(floatImage, CV_32F);
    return floatImage;
}


cv::Mat Compressor::computeInverseDFT(const cv::Mat& complexImage) const
{
    cv::Mat inverseTransform;
    cv::dft(complexImage, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);

    // Normalize the result to the 0-255 range
    cv::normalize(inverseTransform, inverseTransform, 0, 255, cv::NORM_MINMAX);

    inverseTransform.convertTo(inverseTransform, CV_8U);  // Convert back to 8-bit

    return inverseTransform;
}

cv::Mat Compressor::Magnitude(const cv::Mat& complexImage) const
{
    cv::Mat planes[] = { complexImage, cv::Mat::zeros(complexImage.size(), CV_32F) };
    cv::split(complexImage, planes);                   
    cv::magnitude(planes[0], planes[1], planes[0]);

    return planes[0];
}

float const Compressor::IntensityThresholdValue(const cv::Mat& magnitude, float percentile) const {

    const float PERCENTILE_SCALE = 100.0f;

    cv::Mat flattened = magnitude.reshape(1, 1).clone();  

    cv::Mat sorted;

    cv::sort(flattened, sorted, cv::SORT_DESCENDING);

    float threshold = sorted.at<float>(static_cast<int>(sorted.cols * (percentile / PERCENTILE_SCALE)));

    return threshold;
}

cv::Mat Compressor::MakeSubSamplingMask(const cv::Mat& magnitude, float threshold) const
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

cv::Mat Compressor::applyMask(const cv::Mat& complexImage, const cv::Mat& mask) const
{
    cv::Mat planes[2];
    cv::split(complexImage, planes);

    cv::Mat maskFloat;
    mask.convertTo(maskFloat, CV_32F);  // Convert to float

    // cv::Mat maskFloat = convertTOFloatMat(mask);

    cv::Mat maskedPlanes[] = { planes[0].mul(maskFloat), planes[1].mul(maskFloat) };

    cv::Mat maskedComplexImage;
    cv::merge(maskedPlanes, 2, maskedComplexImage);  // Merge back to complex format
 
    return maskedComplexImage;
}

SparseRepresentation Compressor::compress(const Image& image, float percentile) const {
    cv::Mat DFTImage = computeDFT(image.getImage());
    cv::Mat magnitude = Magnitude(DFTImage);
    float threshold = IntensityThresholdValue(magnitude, percentile);
    cv::Mat mask = MakeSubSamplingMask(magnitude, threshold);
    cv::Mat maskedDFTImage = applyMask(DFTImage, mask);

    SparseRepresentation sparseRepr = SparseRepresentation(maskedDFTImage);

    return sparseRepr;
}

Image Compressor::decompress(const SparseRepresentation & sparseRepr) const
{
    cv::Mat decodedSparceCompresDFTimage = sparseRepr.convertToDenseComplexMatrix();

    cv::Mat decodedSparceCompresImage = computeInverseDFT(decodedSparceCompresDFTimage);

    return Image(decodedSparceCompresImage);
}
    


