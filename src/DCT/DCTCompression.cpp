#include "DCTCompression.h"

CompressedImageHolder DCTCompression::DCTCompress(const std::vector<std::vector<float>> &image, const std::vector<std::vector<int>> &quantizationTable) const
{
    DCTTransformationHandler dctTransformationHandler;
    RunLengthEnoding runLengthEncoding;
    ZigzagDCTcoefficientsOrder zigzagOrder;
    DCTEncoding dctEncoding(runLengthEncoding, zigzagOrder);

    // check that the imag is not empty
    if (image.empty())
    {
        throw std::invalid_argument("Image is empty");
    }

    auto tranformedImage = dctTransformationHandler.DCTTransformImage(image, quantizationTable);

    std::vector<std::vector<std::pair<float, int>>> encodedImage = dctEncoding.encodeImageBlocks(tranformedImage);

    // fill the compressed image holder
    CompressedImageHolder compressedImageHolder;
    compressedImageHolder.quantizationTable = quantizationTable;
    compressedImageHolder.compressedImage = encodedImage;
    compressedImageHolder.OriginalImageDimensions = std::make_pair(static_cast<int>(image.size()), static_cast<int>(image[0].size()));
    compressedImageHolder.BLOCK_SIZE = 8;

    return compressedImageHolder;
}

std::vector<std::vector<float>> DCTCompression::DCTDecompress(CompressedImageHolder &compressedImageHolder) const
{
    DCTTransformationHandler dctTransformationHandler;

    RunLengthEnoding runLengthEncoding;
    ZigzagDCTcoefficientsOrder zigzagOrder;
    DCTEncoding dctEncoding(runLengthEncoding, zigzagOrder);


    auto decoded = dctEncoding.decodeImageBlocks(compressedImageHolder.compressedImage);

    auto ReconstructedImage = dctTransformationHandler.inverseDCTTransformImage(decoded, compressedImageHolder.quantizationTable, 
                                                                                         compressedImageHolder.OriginalImageDimensions.first, 
                                                                                         compressedImageHolder.OriginalImageDimensions.second);

    


    
    
    
    
    return ReconstructedImage;
}
