#include "DCTCompression.h"

std::unique_ptr<BaseCompressedImageHolder> DCTCompression::compress(const Image &image, CompressionLevel compressionLevel) const
{
    const int CHUNK_SIZE = 8;
    DCTTransformationHandler dctTransformationHandler(CHUNK_SIZE);
    RunLengthEnoding runLengthEncoding;
    ZigzagDCTcoefficientsOrder zigzagOrder;
    DCTEncoding dctEncoding(runLengthEncoding, zigzagOrder);

    auto imageVector = image.getImageAsVector();

    if (imageVector.empty())
    {
        throw std::invalid_argument("Image is empty");
    }

    auto tranformedImage = dctTransformationHandler.DCTTransformImage(imageVector, compressionLevel);

    std::vector<std::vector<std::pair<float, int>>> encodedImage = dctEncoding.encodeImageBlocks(tranformedImage);

    // fill the compressed image holder
    auto compressedImageHolder = std::make_unique<CompressedDCTImageHolder>();
    compressedImageHolder->quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);
    compressedImageHolder->compressedImage = encodedImage;
    compressedImageHolder->OriginalImageDimensions = std::make_pair(static_cast<int>(imageVector.size()), static_cast<int>(imageVector[0].size()));
    compressedImageHolder->BLOCK_SIZE = 8;

    return compressedImageHolder;
}

Image DCTCompression::decompress(BaseCompressedImageHolder &compressedData) const
{
    // cast to derived type
    const auto &compressedImageHolder = dynamic_cast<const CompressedDCTImageHolder &>(compressedData);

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
