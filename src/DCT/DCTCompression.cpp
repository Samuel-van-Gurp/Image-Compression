#include "DCTCompression.h"

CompressedDCTImageHolder DCTCompression::DCTCompress(const std::vector<std::vector<float>> &image, CompressionLevel compressionLevel) const
{
    const int CHUNK_SIZE = 8;
    DCTTransformationHandler dctTransformationHandler(CHUNK_SIZE);
    RunLengthEnoding runLengthEncoding;
    ZigzagDCTcoefficientsOrder zigzagOrder;
    DCTEncoding dctEncoding(runLengthEncoding, zigzagOrder);

    if (image.empty())
    {
        throw std::invalid_argument("Image is empty");
    }

    auto quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);

    auto tranformedImage = dctTransformationHandler.DCTTransformImage(image, quantizationTable);

    std::vector<std::vector<std::pair<float, int>>> encodedImage = dctEncoding.encodeImageBlocks(tranformedImage);

    // fill the compressed image holder
    CompressedDCTImageHolder compressedImageHolder;
    compressedImageHolder.quantizationTable = quantizationTable;
    compressedImageHolder.compressedImage = encodedImage;
    compressedImageHolder.OriginalImageDimensions = std::make_pair(static_cast<int>(image.size()), static_cast<int>(image[0].size()));
    compressedImageHolder.BLOCK_SIZE = 8;

    return compressedImageHolder;
}

Image DCTCompression::DCTDecompress(CompressedDCTImageHolder &compressedImageHolder) const
{
    DCTTransformationHandler dctTransformationHandler(compressedImageHolder.BLOCK_SIZE);

    RunLengthEnoding runLengthEncoding;
    ZigzagDCTcoefficientsOrder zigzagOrder;
    DCTEncoding dctEncoding(runLengthEncoding, zigzagOrder);

    auto decoded = dctEncoding.decodeImageBlocks(compressedImageHolder.compressedImage);

    auto ReconstructedImage = dctTransformationHandler.inverseDCTTransformImage(decoded, compressedImageHolder.quantizationTable,
                                                                                compressedImageHolder.OriginalImageDimensions.first,
                                                                                compressedImageHolder.OriginalImageDimensions.second);

    return Image(ReconstructedImage);
}
