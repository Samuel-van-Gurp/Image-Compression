#include "DCTCompression.h"

                                                                    
std::unique_ptr<BaseCompressedImageHolder> DCTCompression::compress(const Image &image, const CompressionLevel compressionLevel) const 
{   
    const int CHUNK_SIZE = 8;
    ImageChopper imageChopper;
    DCTTransformationHandler dctTransformationHandler(CHUNK_SIZE);
    RunLengthEnoding m_runlengthEnoding;
    ZigzagDCTcoefficientsOrder m_zigzagDCTcoefficientsOrder;
    const std::vector<std::vector<int>> quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);
    const std::vector<std::vector<float>> imageVector = image.getImageAsVector();
    auto imageChunks = imageChopper.chopImage(imageVector, CHUNK_SIZE);
    // Result will hold fully encoded blocks
    std::vector<std::vector<std::pair<float, int>>> encodedImage(imageChunks.size());

    // Complete processing of each block
    for (size_t i = 0; i < imageChunks.size(); ++i) {
        
        std::vector<std::vector<float>> quantizedBlock = dctTransformationHandler.Forwardblock(imageChunks[i], quantizationTable);

        auto zigzaggedBlock = m_zigzagDCTcoefficientsOrder.ZigzagOrder(quantizedBlock);

        encodedImage[i] = m_runlengthEnoding.RunLengthEncode(zigzaggedBlock);
    }
    return createCompressedImageHolder(encodedImage, quantizationTable, imageVector, CHUNK_SIZE);
    
}



std::unique_ptr<BaseCompressedImageHolder> DCTCompression::createCompressedImageHolder(
    const std::vector<std::vector<std::pair<float, int>>> &encodedImage,
    const std::vector<std::vector<int>> &quantizationTable,
    const std::vector<std::vector<float>> &imageVector,
    const int chunkSize) const {
    
    auto compressedImageHolder = std::make_unique<CompressedDCTImageHolder>();
    compressedImageHolder->quantizationTable = quantizationTable;
    compressedImageHolder->compressedImage = encodedImage;
    compressedImageHolder->OriginalImageDimensions = { static_cast<int>(imageVector.size()), static_cast<int>(imageVector[0].size()) };
    compressedImageHolder->BLOCK_SIZE = chunkSize;
    
    return compressedImageHolder;
}


Image DCTCompression::decompress(BaseCompressedImageHolder &compressedData) const
{
    // Cast to derived type
    const auto &compressedImageHolder = dynamic_cast<const CompressedDCTImageHolder &>(compressedData);
    
    // Create required objects with same naming convention as compress()
    const int CHUNK_SIZE = compressedImageHolder.BLOCK_SIZE;
    ImageChopper imageChopper;
    DCTTransformationHandler dctTransformationHandler(CHUNK_SIZE);
    RunLengthEnoding m_runlengthEnoding;
    ZigzagDCTcoefficientsOrder m_zigzagDCTcoefficientsOrder;
    
    // Get dimensions and quantization table
    auto quantizationTable = compressedImageHolder.quantizationTable;
    int originalHeight = compressedImageHolder.OriginalImageDimensions.first;
    int originalWidth = compressedImageHolder.OriginalImageDimensions.second;
    
    // Pre-allocate space for decompressed blocks
    std::vector<std::vector<std::vector<float>>> decodedBlocks(
        compressedImageHolder.compressedImage.size());
    
    // Process each block directly - same style as compress function
    for (size_t i = 0; i < compressedImageHolder.compressedImage.size(); ++i) {
        // Step 1: Run-length decode
        auto runLengthDecoded = m_runlengthEnoding.RunLengthDecode(
            compressedImageHolder.compressedImage[i]);
        
        // Step 2: Inverse zigzag ordering
        auto dequantizedBlock = m_zigzagDCTcoefficientsOrder.ReverseZigzagtraversal(
            runLengthDecoded);
        
        // Step 3 & 4: Dequantize and Inverse DCT (using InverseBlock)
        decodedBlocks[i] = dctTransformationHandler.InverseBlock(
            dequantizedBlock, quantizationTable);
    }
    
    // Reconstruct the full image from blocks
    auto reconstructedImage = imageChopper.reconstructImage(
        decodedBlocks, originalHeight, originalWidth);
    
    return Image(reconstructedImage);
}