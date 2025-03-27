#include "DCTCompression.h"

DCTCompression::DCTCompression()
    : CHUNK_SIZE(8), m_imageChopper(), m_dctTransformationHandler(CHUNK_SIZE), m_runlengthEnoding(), m_zigzagDCTcoefficientsOrder()
{
}

std::vector<std::pair<float, int>> DCTCompression::processImageBlock(
    const std::vector<std::vector<float>> &imageBlock,
    const std::vector<std::vector<int>> &quantizationTable) const
{

    std::vector<std::vector<float>> quantizedBlock = m_dctTransformationHandler.Forwardblock(imageBlock, quantizationTable);
    auto zigzaggedBlock = m_zigzagDCTcoefficientsOrder.ZigzagOrder(quantizedBlock);
    return m_runlengthEnoding.RunLengthEncode(zigzaggedBlock);
}

std::vector<std::vector<std::pair<float, int>>> DCTCompression::processImageBlocks(
    const std::vector<std::vector<std::vector<float>>> &imageChunks,
    const std::vector<std::vector<int>> &quantizationTable) const
{
    size_t numThreads =std::max(std::thread::hardware_concurrency(), 1u);
    size_t totalChunks = imageChunks.size();
    size_t batchSize = (totalChunks + numThreads - 1) / numThreads;
    
    std::vector<std::vector<std::pair<float, int>>> encodedImage(totalChunks);
    std::vector<std::thread> threads;
    for (size_t t = 0; t < numThreads; ++t)
    {
        size_t start = t * batchSize;
        size_t end = std::min(start + batchSize, totalChunks);

        if (start >= totalChunks)
            break;

        threads.emplace_back([&, start, end, t]()
        {
            for (size_t i = start; i < end; ++i)
            {
                encodedImage[i] = processImageBlock(imageChunks[i], quantizationTable);
               
            }
        });
    }

    for (auto &th : threads)
    {
        th.join();
    }

    return encodedImage;
}


// std::vector<std::vector<std::pair<float, int>>> DCTCompression::processImageBlocks(
//     const std::vector<std::vector<std::vector<float>>> &imageChunks,
//     const std::vector<std::vector<int>> &quantizationTable) const
// {

//     std::vector<std::vector<std::pair<float, int>>> encodedImage(imageChunks.size());

//     for (size_t i = 0; i < imageChunks.size(); ++i)
//     {
//         encodedImage[i] = processImageBlock(imageChunks[i], quantizationTable);
//     }

//     return encodedImage;
// }

std::unique_ptr<BaseCompressedImageHolder> DCTCompression::compress(const Image &image, const CompressionLevel compressionLevel) const
{
    // set up
    const std::vector<std::vector<int>> quantizationTable = QuantizationTable::getQuantizationTable(compressionLevel);
    const std::vector<std::vector<float>> imageVector = image.getImageAsVector();
    auto imageChunks = m_imageChopper.chopImage(imageVector, CHUNK_SIZE);
 
    // execute
    auto start_time = std::chrono::high_resolution_clock::now();
    auto encodedImage = processImageBlocks(imageChunks, quantizationTable);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Execution Time: " << std::chrono::duration<double>(end_time - start_time).count()<< " seconds" << std::endl;
    return createCompressedImageHolder(encodedImage, quantizationTable, imageVector, CHUNK_SIZE);
}

std::unique_ptr<BaseCompressedImageHolder> DCTCompression::createCompressedImageHolder(
    const std::vector<std::vector<std::pair<float, int>>> &encodedImage,
    const std::vector<std::vector<int>> &quantizationTable,
    const std::vector<std::vector<float>> &imageVector,
    const int chunkSize) const
{

    auto compressedImageHolder = std::make_unique<CompressedDCTImageHolder>();
    compressedImageHolder->quantizationTable = quantizationTable;
    compressedImageHolder->compressedImage = encodedImage;
    compressedImageHolder->OriginalImageDimensions = {static_cast<int>(imageVector.size()), static_cast<int>(imageVector[0].size())};
    compressedImageHolder->BLOCK_SIZE = chunkSize;

    return compressedImageHolder;
}

Image DCTCompression::decompress(BaseCompressedImageHolder &compressedData) const
{
    // Cast to derived type, not nice :(
    const auto &compressedImageHolder = dynamic_cast<const CompressedDCTImageHolder &>(compressedData);

    // Get dimensions and quantization table
    auto quantizationTable = compressedImageHolder.quantizationTable;
    int originalHeight = compressedImageHolder.OriginalImageDimensions.first;
    int originalWidth = compressedImageHolder.OriginalImageDimensions.second;

    std::vector<std::vector<std::vector<float>>> decodedBlocks(
        compressedImageHolder.compressedImage.size());

    for (size_t i = 0; i < compressedImageHolder.compressedImage.size(); ++i)
    {
        auto runLengthDecoded = m_runlengthEnoding.RunLengthDecode(
            compressedImageHolder.compressedImage[i]);

        auto dequantizedBlock = m_zigzagDCTcoefficientsOrder.ReverseZigzagtraversal(
            runLengthDecoded);

        decodedBlocks[i] = m_dctTransformationHandler.InverseBlock(
            dequantizedBlock, quantizationTable);
    }

    auto reconstructedImage = m_imageChopper.reconstructImage(
        decodedBlocks, originalHeight, originalWidth);

    return Image(reconstructedImage);
}