#include "ImageCompressionAPI.h"

ImageCompressionAPI::ImageCompressionAPI(Method method)
{
    switch (method)
    {
    case Method::DCT:
        m_CompressionStrategy = std::make_unique<DCTCompression>();
        m_DataStoreStrategy = std::make_unique<StoreDCTData>();
        break;
    case Method::DFT:
        m_CompressionStrategy = std::make_unique<DFTCompressor>();
        m_DataStoreStrategy = std::make_unique<StoringDFTData>();
        break;
    default:
        throw std::invalid_argument("Invalid compression method");
    }
}

std::unique_ptr<BaseCompressedImageHolder> ImageCompressionAPI::compress(const Image &image, CompressionLevel level)
{
    return m_CompressionStrategy->compress(image, level);
}

Image ImageCompressionAPI::decompress(BaseCompressedImageHolder &compressedData)
{
    return m_CompressionStrategy->decompress(compressedData);
}

void ImageCompressionAPI::saveCompressed(const BaseCompressedImageHolder &compressedData, const std::string &fileName, const std::string &filePath)
{
    m_DataStoreStrategy->writeToBinary(fileName, filePath, compressedData);
}

std::unique_ptr<BaseCompressedImageHolder> ImageCompressionAPI::loadCompressed(const std::string &fileName, const std::string &filePath)
{
    return m_DataStoreStrategy->readFromBinary(fileName, filePath);
}

